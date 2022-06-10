#include<stdio.h>
#include<windows.h>
#pragma warning(disable:4996)



unsigned int enc[9] = { 0xd04f9b3f,0x14e3d512,0xdb62246e,0x1290c9c0,0x7417372c,0x48478f9c,0xe58a627d,0xd2659a75 };

int checkflag(unsigned int* flag, int len)
{
	if (memcmp(flag, enc, len) == 0)
	{
		return 1;
	}
	return 0;
}

void char_to_long(unsigned char* in, unsigned int* out)
{
	int i;
	*out = 0;
	for (i = 0; i < 4; i++)
	{
		*out = (unsigned int)in[i] << (24 - 8 * i) | (*out);
	}
}

void xxteaencrypt(unsigned int* flag, unsigned int* key, unsigned int n)
{
	unsigned int next, end, sum;
	unsigned int rounds, e, delta = 0x9e3779b9;
	int i;

	rounds = 6 + 52 / n;//轮回的次数
	sum = 0;
	end = flag[n - 1];//先设置end的值为最后一个，因为加密第一个要用
	do
	{
		sum += delta;
		e = (sum >> 2) & 3;//与key的值关;
		for (i = 0; i < n - 1; i++)//加密第一个到倒数第二个
		{
			next = flag[i + 1];
			flag[i] += (((end >> 5 ^ next << 2) + (next >> 3 ^ end << 4)) ^ ((sum ^ next) + (key[(i & 3) ^ e] ^ end)));
			end = flag[i];//现在用end来保存当前数据的值，为下一个数据的加密做准备。
		}
		next = flag[0];//将第一个数据给next，为加密最后一个数据做准备，这时候end的值为倒数第二个数据。
		flag[n - 1] += (((end >> 5 ^ next << 2) + (next >> 3 ^ end << 4)) ^ ((sum ^ next) + (key[(i & 3) ^ e] ^ end)));
		end = flag[n - 1];//继续设置end的值为最后一个数据，为新一轮加密做准备。
	} while (--rounds);

}

void TRUEProc()
{


	unsigned int key[4] = { 'D','0','g','3' };
	unsigned char flag[33];
	unsigned int temp[9] = { 0 };
	unsigned int n = 0;
	int i = 0;

	scanf("%s", flag);
	for (i = 0; i < 8; i++)
	{
		char_to_long(&flag[i * 4], &temp[i]);
	}
	_asm
	{
			push eax;
			xor eax, eax;
			test eax, eax;
			jnz  LABEL1;
			jz LABEL2;
		LABEL1:
			_emit 0xE8;
		LABEL2:
			mov byte ptr[n], 0;
			call LABEL3;
			_emit 0xFF;
		LABEL3:
			add dword ptr ss : [esp] , 8;
			ret;
			__emit 0x11;
			mov byte ptr[n], 8;
			pop eax;
	}
	xxteaencrypt((unsigned int*)temp, key, n);


	if (checkflag(temp, 32) != 0)
	{
		printf("\nsuccess!");
	}
	else
	{
		printf("\nfailed!");
	}

}

BOOL CreateMyself(CHAR* szFilePath, PVOID ptr)
{
	STARTUPINFOA si;
	PROCESS_INFORMATION pi;
	CONTEXT ctx = { 0 };
	ZeroMemory(&pi, sizeof(pi));//用来将指定的内存块清零。
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);

	CreateProcessA(szFilePath, NULL, NULL, NULL, FALSE, CREATE_SUSPENDED, NULL, NULL, &si, &pi);
	ctx.ContextFlags = CONTEXT_FULL;
	GetThreadContext(pi.hThread, &ctx);
	ctx.Eip = (DWORD)ptr;

	SetThreadContext(pi.hThread, &ctx);

	ResumeThread(pi.hThread);
	WaitForSingleObject(pi.hProcess, INFINITE);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

	return TRUE;

}
//D0g3{38051cf6d6f302f23f6dbe93a3}
int main()
{
	CHAR Filename[MAX_PATH];
	PVOID ptr = TRUEProc;
	GetModuleFileNameA(0, Filename, MAX_PATH);

	printf("please input the flag:");
	
	CreateMyself(Filename, ptr);
	return 0;
}