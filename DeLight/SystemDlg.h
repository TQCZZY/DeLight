#pragma once
#include "afxdialogex.h"


// SystemDlg 对话框

class SystemDlg : public CDialogEx
{
	DECLARE_DYNAMIC(SystemDlg)

public:
	SystemDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~SystemDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SYSTEMDLG };
#endif

protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	// 这是显示商品数据的列表
	CListCtrl m_List;
	HACCEL m_hAcc;
	CMenu m_Menubar;
	afx_msg void OnBnClickedSlfDtl();
	afx_msg void OnBnClickedSearch();
	afx_msg void OnBnClickedRemotequery();
	afx_msg void OnBnClickedGlbtoexcel();
	afx_msg void OnBnClickedSortnm();
	afx_msg void OnBnClickedSortdt();
	afx_msg void OnBnClickedSortqt();
	afx_msg void OnBnClickedSortsf();
	afx_msg void OnBnClickedSysdlgSeldst();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnQuit();
	afx_msg void OnInbound();
	afx_msg void OnOutbound();
	afx_msg void OnModify();
	afx_msg void OnSelall();
	afx_msg void OnRevsel();
	afx_msg void OnSortbyname();
	afx_msg void OnSortbytime();
};
