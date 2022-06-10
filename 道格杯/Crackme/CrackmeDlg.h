
// CrackmeDlg.h: 头文件
//

#pragma once
#include <Wincrypt.h>


typedef struct
{
	BYTE Hash1[MAX_PATH];
	BYTE Hash2[MAX_PATH];
	BYTE AesEnc[MAX_PATH];
}ALLENC;


// CCrackmeDlg 对话框
class CCrackmeDlg : public CDialogEx
{
// 构造
public:
	CCrackmeDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CRACKME_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString m_flag;
	CString m_key;
	ALLENC AllEnc;
	afx_msg void OnBnClickedOk();
	
	bool CalculateHash(BYTE* pData, DWORD dwDataLength, ALG_ID algHashType, BYTE** ppHashData, DWORD* pdwHashDataLength);
	bool AesEncrypt(BYTE* pPassword, DWORD dwPasswordLength, BYTE* pData, DWORD& dwDataLength, DWORD dwBufferLength);
	void ShowWrongMessage();
	void ShowSuccessMessage();
	//bool AesDecrypt(BYTE* pPassword, DWORD dwPasswordLength, BYTE* pData, DWORD& dwDataLength, DWORD dwBufferLength);
};
