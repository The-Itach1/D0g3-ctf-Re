
// CrackmeDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "Crackme.h"
#include "CrackmeDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

typedef enum _PROCESSINFOCLASS {
	ProcessBasicInformation = 0,
	ProcessQuotaLimits,
	ProcessIoCounters,
	ProcessVmCounters,
	ProcessTimes,
	ProcessBasePriority,
	ProcessRaisePriority,
	ProcessDebugPort = 7,
	ProcessExceptionPort,
	ProcessAccessToken,
	ProcessLdtInformation,
	ProcessLdtSize,
	ProcessDefaultHardErrorMode,
	ProcessIoPortHandlers,
	ProcessPooledUsageAndLimits,
	ProcessWorkingSetWatch,
	ProcessUserModeIOPL,
	ProcessEnableAlignmentFaultFixup,
	ProcessPriorityClass,
	ProcessWx86Information,
	ProcessHandleCount,
	ProcessAffinityMask,
	ProcessPriorityBoost,
	MaxProcessInfoClass,
	ProcessWow64Information = 26,
	ProcessImageFileName = 27,
	ProcessDebugObjectHandle = 30,
	ProcessDebugFlags = 31,
	SystemKernelDebuggerInformation = 35
}PROCESSINFOCLASS;

typedef NTSTATUS(WINAPI* NTQUERYINFORMATIONPROCESS)(
	HANDLE ProcessHandle,
	PROCESSINFOCLASS ProcessInformationClass,
	PVOID ProcessInformation,
	ULONG ProcessInformationLength,
	PULONG ReturnLength
	);


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框



class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCrackmeDlg 对话框



CCrackmeDlg::CCrackmeDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CRACKME_DIALOG, pParent)
	, m_flag(_T(""))
	, m_key(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	BYTE temp1[] = { 0xdf, 0xb6, 0xa2, 0x41, 0x31, 0xc, 0xfd, 0x37, 0x46, 0x33, 0x69, 0x7c, 0xe9, 0xcd, 0x56, 0x3c };
	BYTE temp2[] = { 0x70, 0xf0, 0x4d, 0xbc, 0xf0, 0x12, 0xa5, 0x76, 0x1f, 0x47, 0xc0, 0xce, 0xf5, 0x38, 0x73, 0x86, 0x9e, 0xcd, 0xc5, 0xa3 };
	BYTE temp3[] = { 0x35,0xf8,0x84,0x29,0x96,0x4f,0x82,0x6b,0x70,0xfe,0x3a,0xff,0x47,0x2f,0x43,0x4b,0x2c,0x68,0xbd,0x16,0x27,0x30,0x82,0x50,0xa9,0x11,0x99,0xf1,0xa0,0x44,0x20,0xc2,0x40,0x18,0x6f,0x5d,0x5b,0xd8,0x4d,0x05,0x44,0x3c,0xb5,0xe7,0x2e,0x87,0x79,0xee };

	memcpy(AllEnc.Hash1, temp1, 16);
	memcpy(AllEnc.Hash2, temp2, 20);
	memcpy(AllEnc.AesEnc, temp3, 0x30);
}

void CCrackmeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_FLAG, m_flag);
	DDX_Text(pDX, IDC_EDIT_KEY, m_key);
}

BEGIN_MESSAGE_MAP(CCrackmeDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CCrackmeDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CCrackmeDlg 消息处理程序

BOOL CCrackmeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	HANDLE pProcessHandle;
	BOOL bDebugFlag;
	NTQUERYINFORMATIONPROCESS myNtQueryInformationProcess;
	unsigned int str[8] = { 0x7551744E, 0x49797265, 0x726F666E, 0x6974616D, 0x72506E6F, 0x7365636F, 0x00000073 };

	myNtQueryInformationProcess = (NTQUERYINFORMATIONPROCESS)GetProcAddress(GetModuleHandle("ntdll.dll"), (LPCSTR)str);

	pProcessHandle = GetCurrentProcess();

	myNtQueryInformationProcess(pProcessHandle, ProcessDebugFlags, &bDebugFlag, sizeof(bDebugFlag), NULL);
	//printf("ProcessDebugFlags：%x\n", bDebugFlag);

	if (bDebugFlag != 0)
	{
		int i;


		for (i = 0; i < 16; i++)
		{
			AllEnc.Hash1[i] ^= i;

		}
		for (i = 0; i < 20; i++)
		{
			AllEnc.Hash2[i] ^= i;

		}
	}

	
	

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CCrackmeDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCrackmeDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CCrackmeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//D0g3{H@sh_a^d_Aes_6y_W1nCrypt!!}
//key:THE_ITACH1
void CCrackmeDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码

	UpdateData(TRUE);
	BYTE KeyDate[MAX_PATH] = {0};
	BYTE FlagDate[MAX_PATH] = { 0 };

	DWORD key_len=m_key.GetLength();
	DWORD flag_len = m_flag.GetLength();
	PBYTE HashOut[3];
	PBYTE AesOut= NULL;
	DWORD HashOutLen[3] = {0};
	DWORD AesOutLen=NULL;
	
	DWORD dwret;


	memcpy(KeyDate, m_key.GetBuffer(key_len), key_len);
	memcpy(FlagDate, m_flag.GetBuffer(flag_len), flag_len);

	if (key_len != 10 && flag_len!=32)
	{
		ShowWrongMessage();
		
	}
	else
	{
		CalculateHash(KeyDate, key_len / 2, CALG_MD5, &HashOut[0], &HashOutLen[0]);
		CalculateHash(&KeyDate[5], key_len / 2, CALG_SHA1, &HashOut[1], &HashOutLen[1]);

		CalculateHash(KeyDate, key_len, CALG_MD5, &HashOut[2], &HashOutLen[2]);

		dwret = memcmp(HashOut[0], AllEnc.Hash1, HashOutLen[0]);
		dwret = memcmp(HashOut[1], AllEnc.Hash2, HashOutLen[1]);

		if (dwret == 0)
		{
			AesEncrypt(HashOut[2], HashOutLen[2], FlagDate, flag_len, MAX_PATH);
			
			//AesDecrypt(HashOut[2], HashOutLen[2], FlagDate, flag_len, MAX_PATH);
			if (memcmp(FlagDate, AllEnc.AesEnc, flag_len) == 0)
			{
				ShowSuccessMessage();
			}
			else
			{
				ShowWrongMessage();
			}

		}
		else
		{
			ShowWrongMessage();
		}
	}
	
	//CDialogEx::OnOK();
}


bool CCrackmeDlg::CalculateHash(BYTE* pData, DWORD dwDataLength, ALG_ID algHashType, BYTE** ppHashData, DWORD* pdwHashDataLength)
{
	// TODO: 在此处添加实现代码.
	HCRYPTPROV hCryptProv = NULL;
	HCRYPTHASH hCryptHash = NULL;
	BYTE* pHashData = NULL;
	DWORD dwHashDataLength = 0;
	DWORD dwTemp = 0;
	BOOL bRet = FALSE;


	do
	{
		// 获得指定CSP的密钥容器的句柄
		bRet = ::CryptAcquireContext(&hCryptProv, NULL, NULL, PROV_RSA_AES, CRYPT_VERIFYCONTEXT);
		if (FALSE == bRet)
		{
			break;
		}

		// 创建一个HASH对象, 指定HASH算法
		bRet = ::CryptCreateHash(hCryptProv, algHashType, NULL, NULL, &hCryptHash);
		if (FALSE == bRet)
		{
			break;
		}

		// 计算HASH数据
		bRet = ::CryptHashData(hCryptHash, pData, dwDataLength, 0);
		if (FALSE == bRet)
		{
			break;
		}

		// 获取HASH结果的大小
		dwTemp = sizeof(dwHashDataLength);
		bRet = ::CryptGetHashParam(hCryptHash, HP_HASHSIZE, (BYTE*)(&dwHashDataLength), &dwTemp, 0);
		if (FALSE == bRet)
		{
			break;
		}

		// 申请内存
		pHashData = new BYTE[dwHashDataLength];
		if (NULL == pHashData)
		{
			bRet = FALSE;
			break;
		}
		::RtlZeroMemory(pHashData, dwHashDataLength);

		// 获取HASH结果数据
		bRet = ::CryptGetHashParam(hCryptHash, HP_HASHVAL, pHashData, &dwHashDataLength, 0);
		if (FALSE == bRet)
		{
			break;
		}

		// 返回数据
		*ppHashData = pHashData;
		*pdwHashDataLength = dwHashDataLength;

	} while (FALSE);

	// 释放关闭
	if (FALSE == bRet)
	{
		if (pHashData)
		{
			delete[]pHashData;
			pHashData = NULL;
		}
	}
	if (hCryptHash)
	{
		::CryptDestroyHash(hCryptHash);
	}
	if (hCryptProv)
	{
		::CryptReleaseContext(hCryptProv, 0);
	}

	return bRet;

}




bool CCrackmeDlg::AesEncrypt(BYTE* pPassword, DWORD dwPasswordLength, BYTE* pData, DWORD& dwDataLength, DWORD dwBufferLength)
{
	BOOL bRet = TRUE;
	HCRYPTPROV hCryptProv = NULL;
	HCRYPTHASH hCryptHash = NULL;
	HCRYPTKEY hCryptKey = NULL;

	do
	{
		// 获取CSP句柄
		bRet = ::CryptAcquireContext(&hCryptProv, NULL, NULL, PROV_RSA_AES, CRYPT_VERIFYCONTEXT);
		if (FALSE == bRet)
		{
			break;
		}

		// 创建HASH对象
		bRet = ::CryptCreateHash(hCryptProv, CALG_MD5, NULL, 0, &hCryptHash);
		if (FALSE == bRet)
		{
			break;
		}

		// 对密钥进行HASH计算
		bRet = ::CryptHashData(hCryptHash, pPassword, dwPasswordLength, 0);
		if (FALSE == bRet)
		{
			break;
		}

		// 使用HASH来生成密钥
		bRet = ::CryptDeriveKey(hCryptProv, CALG_AES_128, hCryptHash, CRYPT_EXPORTABLE, &hCryptKey);
		if (FALSE == bRet)
		{
			break;
		}

		// 加密数据
		bRet = ::CryptEncrypt(hCryptKey, NULL, TRUE, 0, pData, &dwDataLength, dwBufferLength);
		if (FALSE == bRet)
		{
			break;
		}

	} while (FALSE);

	// 关闭释放
	if (hCryptKey)
	{
		::CryptDestroyKey(hCryptKey);
	}
	if (hCryptHash)
	{
		::CryptDestroyHash(hCryptHash);
	}
	if (hCryptProv)
	{
		::CryptReleaseContext(hCryptProv, 0);
	}

	return bRet;
}


void CCrackmeDlg::ShowWrongMessage()
{
	// TODO: 在此处添加实现代码.
	MessageBox("Wrong!!!");
}

void CCrackmeDlg::ShowSuccessMessage()
{
	// TODO: 在此处添加实现代码.
	MessageBox("Success!!!");
}


//bool CCrackmeDlg::AesDecrypt(BYTE* pPassword, DWORD dwPasswordLength, BYTE* pData, DWORD& dwDataLength, DWORD dwBufferLength)
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
//		bRet = ::CryptAcquireContext(&hCryptProv, NULL, NULL, PROV_RSA_AES, CRYPT_VERIFYCONTEXT);
//		if (FALSE == bRet)
//		{
//			break;
//		}
//
//		// 创建HASH对象
//		bRet = ::CryptCreateHash(hCryptProv, CALG_MD5, NULL, 0, &hCryptHash);
//		if (FALSE == bRet)
//		{
//
//			break;
//		}
//
//		// 对密钥进行HASH计算
//		bRet = ::CryptHashData(hCryptHash, pPassword, dwPasswordLength, 0);
//		if (FALSE == bRet)
//		{
//
//			break;
//		}
//
//		// 使用HASH来生成密钥
//		bRet = ::CryptDeriveKey(hCryptProv, CALG_AES_128, hCryptHash, CRYPT_EXPORTABLE, &hCryptKey);
//		if (FALSE == bRet)
//		{
//
//			break;
//		}
//
//		// 解密数据
//		bRet = ::CryptDecrypt(hCryptKey, NULL, TRUE, 0, pData, &dwDataLength);
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
//		::CryptDestroyKey(hCryptKey);
//	}
//	if (hCryptHash)
//	{
//		::CryptDestroyHash(hCryptHash);
//	}
//	if (hCryptProv)
//	{
//		::CryptReleaseContext(hCryptProv, 0);
//	}
//
//	return bRet;
//	return false;
//}
