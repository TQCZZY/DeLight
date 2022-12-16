#pragma once
#include "afxdialogex.h"

struct SocMsg
{
	char ip[21];
	char name[31];
	char header[11];
	char respTo[31];
	char data[101];
};

// CQueryDlg 对话框
ULONG WINAPI LinsenThread(LPVOID p);

class CQueryDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CQueryDlg)

public:
	CString m_localIP;
	CButton	m_enter;
	CListBox m_show;
	CString	m_toIP;
	CString	m_message;
	CString	m_name;
	CQueryDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CQueryDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_REMOTEQUERY_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	SocMsg Msg;
	SocMsg* pMsg;
	HANDLE listenThreadHandle;
	CSocket m_ReceiveSocket;//构造一个套接字对象
	bool dirtyReceiveSocket;
	bool serverRespond;

	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedSend();
	afx_msg void OnBnClickedEnter();
};
