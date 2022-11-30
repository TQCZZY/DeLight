// QueryDlg.h : header file
//

#if !defined(AFX_CHATDLG_H__FE4995C3_3B09_4226_8F50_08B1F482C034__INCLUDED_)
#define AFX_CHATDLG_H__FE4995C3_3B09_4226_8F50_08B1F482C034__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CQueryDlg dialog
ULONG WINAPI LinsenThread(LPVOID p);

class CQueryDlg : public CDialog
{
// Construction
public:
	CQueryDlg(CWnd* pParent = NULL);	// standard constructor
	CString m_localIP;
// Dialog Data
	//{{AFX_DATA(CQueryDlg)
	enum { IDD = IDD_CHAT_DIALOG };
	CButton	m_enter;
	CListBox	m_show;
	CString	m_toIP;
	CString	m_message;
	CString	m_name;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQueryDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CQueryDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnEnter();
	afx_msg void OnSend();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHATDLG_H__FE4995C3_3B09_4226_8F50_08B1F482C034__INCLUDED_)
