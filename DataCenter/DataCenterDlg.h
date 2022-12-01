// DataCenterDlg.h : header file
//

#if !defined(AFX_TEAMCHATDLG_H__C8AB1CF2_E1A2_474E_A957_4DC009ACADA3__INCLUDED_)
#define AFX_TEAMCHATDLG_H__C8AB1CF2_E1A2_474E_A957_4DC009ACADA3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDataCenterDlg dialog
ULONG WINAPI LinsenThread(LPVOID p);



class CDataCenterDlg : public CDialog
{
// Construction
public:
	CDataCenterDlg(CWnd* pParent = NULL);	// standard constructor

	

// Dialog Data
	//{{AFX_DATA(CDataCenterDlg)
	enum { IDD = IDD_TEAMCHAT_DIALOG };
	CListBox	m_show;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDataCenterDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDataCenterDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnServer();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEAMCHATDLG_H__C8AB1CF2_E1A2_474E_A957_4DC009ACADA3__INCLUDED_)
