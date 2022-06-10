//#include <Windows.h>
//#include<stdio.h>
//bool AesDecrypt(BYTE* pPassword, DWORD dwPasswordLength, BYTE* pData, DWORD& dwDataLength, DWORD dwBufferLength)
//{
//	// TODO: 在此处添加实现代码.
//	BOOL bRet = TRUE;
//	HCRYPTPROV hCryptProv = NULL;
//	HCRYPTHASH hCryptHash = NULL;
//	HCRYPTKEY hCryptKey = NULL;
//
//	do
//	{
//		// 获取CSP句柄
//		bRet = CryptAcquireContext(&hCryptProv, NULL, NULL, PROV_RSA_AES, CRYPT_VERIFYCONTEXT);
//		if (FALSE == bRet)
//		{
//			break;
//		}
//
//		// 创建HASH对象
//		bRet = CryptCreateHash(hCryptProv, CALG_MD5, NULL, 0, &hCryptHash);
//		if (FALSE == bRet)
//		{
//
//			break;
//		}
//
//		// 对密钥进行HASH计算
//		bRet = CryptHashData(hCryptHash, pPassword, dwPasswordLength, 0);
//		if (FALSE == bRet)
//		{
//
//			break;
//		}
//
//		// 使用HASH来生成密钥
//		bRet = CryptDeriveKey(hCryptProv, CALG_AES_128, hCryptHash, CRYPT_EXPORTABLE, &hCryptKey);
//		if (FALSE == bRet)
//		{
//
//			break;
//		}
//
//		// 解密数据
//		bRet = CryptDecrypt(hCryptKey, NULL, TRUE, 0, pData, &dwDataLength);
//		if (FALSE == bRet)
//		{
//
//			break;
//		}
//
//	} while (FALSE);
//
//	// 关闭释放
//	if (hCryptKey)
//	{
//		CryptDestroyKey(hCryptKey);
//	}
//	if (hCryptHash)
//	{
//		CryptDestroyHash(hCryptHash);
//	}
//	if (hCryptProv)
//	{
//		CryptReleaseContext(hCryptProv, 0);
//	}
//
//	return bRet;
//	return false;
//}
//
//
//int main()
//{
//	BYTE Enc[] = { 0x35,0xf8,0x84,0x29,0x96,0x4f,0x82,0x6b,0x70,0xfe,0x3a,0xff,0x47,0x2f,0x43,0x4b,0x2c,0x68,0xbd,0x16,0x27,0x30,0x82,0x50,0xa9,0x11,0x99,0xf1,0xa0,0x44,0x20,0xc2,0x40,0x18,0x6f,0x5d,0x5b,0xd8,0x4d,0x05,0x44,0x3c,0xb5,0xe7,0x2e,0x87,0x79,0xee };
//	BYTE Key[] = { 0x44,0x4f,0x8c,0xdc,0xbb,0xb7,0xcb,0x47,0x69,0x3c,0xa9,0x09,0x08,0x70,0xbc,0x40 };
//	
//	DWORD Enclen = 0x30;
//	AesDecrypt(Key, 16, Enc, Enclen, MAX_PATH);
//
//	for (int i = 0; i < Enclen; i++)
//	{
//		printf("%c", Enc[i]);
//	}
//	
//}
////D0g3{H@sh_a^d_Aes_6y_W1nCrypt!!}


#include <stdio.h>
#include <windows.h>

DWORD CallRemoteAPI(HANDLE hProcess, DWORD dwAddr, DWORD* pdwParamList, DWORD dwParamCount, DWORD* pdwReturnValue)
{
    DWORD dwThreadID = 0;
    HANDLE hThread = NULL;
    DWORD dwExitCode = 0;
    DWORD dwRtlExitUserThread = 0;
    DWORD dwExecFunctionCodeLength = 0;
    BYTE bPushParamCode[] = { 0x68, 0x00, 0x00, 0x00, 0x00 };
    BYTE bExecFunctionCode[] = { 0xB8, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xD0, 0x50, 0xB8, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xD0 };
    BYTE* pRemoteExecFunctionCode = NULL;

    // get RtlExitUserThread address
    dwRtlExitUserThread = (DWORD)GetProcAddress(GetModuleHandle("ntdll.dll"), "RtlExitUserThread");
    if (dwRtlExitUserThread == 0)
    {
        return 1;
    }

    // calculate code length:
    // push param_1
    // push param_2
    // push param_3
    // ...
    // mov eax, TargetFunction
    // call eax
    // push eax
    // mov eax, RtlExitUserThread
    // call eax
    dwExecFunctionCodeLength = (dwParamCount * sizeof(bPushParamCode)) + sizeof(bExecFunctionCode);

    // allocate memory in remote process
    pRemoteExecFunctionCode = (BYTE*)VirtualAllocEx(hProcess, NULL, dwExecFunctionCodeLength, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    if (pRemoteExecFunctionCode == NULL)
    {
        return 1;
    }

    // write function parameter values
    for (DWORD i = 0; i < dwParamCount; i++)
    {
        // set current param value
        *(DWORD*)&bPushParamCode[1] = pdwParamList[dwParamCount - 1 - i];
        if (WriteProcessMemory(hProcess, (BYTE*)(pRemoteExecFunctionCode + (i * sizeof(bPushParamCode))), (void*)bPushParamCode, sizeof(bPushParamCode), NULL) == 0)
        {
            // error
            VirtualFreeEx(hProcess, pRemoteExecFunctionCode, 0, MEM_RELEASE);

            return 1;
        }
    }

    // set target function address
    *(DWORD*)&bExecFunctionCode[1] = dwAddr;

    // set RtlExitUserThread function address
    *(DWORD*)&bExecFunctionCode[9] = dwRtlExitUserThread;

    // write function execution code
    if (WriteProcessMemory(hProcess, (BYTE*)(pRemoteExecFunctionCode + (dwParamCount * sizeof(bPushParamCode))), (void*)bExecFunctionCode, sizeof(bExecFunctionCode), NULL) == 0)
    {
        // error
        VirtualFreeEx(hProcess, pRemoteExecFunctionCode, 0, MEM_RELEASE);

        return 1;
    }

    // create a thread in the remote process
    hThread = CreateRemoteThread(hProcess, NULL, (128 * 1024), (LPTHREAD_START_ROUTINE)pRemoteExecFunctionCode, NULL, 0, &dwThreadID);
    if (hThread == NULL)
    {
        // error
        VirtualFreeEx(hProcess, pRemoteExecFunctionCode, 0, MEM_RELEASE);

        return 1;
    }

    // wait for thread to complete
    WaitForSingleObject(hThread, INFINITE);

    // get thread exit code (api return value)
    if (GetExitCodeThread(hThread, &dwExitCode) == 0)
    {
        // error
        CloseHandle(hThread);
        VirtualFreeEx(hProcess, pRemoteExecFunctionCode, 0, MEM_RELEASE);

        return 1;
    }

    // close thread handle
    CloseHandle(hThread);

    // free remote code block
    VirtualFreeEx(hProcess, pRemoteExecFunctionCode, 0, MEM_RELEASE);

    // store return value
    *pdwReturnValue = dwExitCode;

    return 0;
}