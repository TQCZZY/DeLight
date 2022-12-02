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

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
	virtual BOOL OnInitDialog();
	// 这是显示商品数据的列表
	CListCtrl m_List;
	afx_msg void OnBnClickedSelall();
	afx_msg void OnBnClickedReversesel();
	afx_msg void OnBnClickedAdd();
	afx_msg void OnBnClickedDel();
	afx_msg void OnBnClickedEdit();
	afx_msg void OnBnClickedSlfDtl();
	afx_msg void OnBnClickedSearch();
	afx_msg void OnBnClickedRemotequery();
	afx_msg void OnBnClickedGlbtoexcel();
	afx_msg void OnBnClickedSortnm();
	afx_msg void OnBnClickedSortdt();
	afx_msg void OnBnClickedSortqt();
	afx_msg void OnBnClickedSortsf();
	afx_msg void OnBnClickedSysdlgSeldst();
};
