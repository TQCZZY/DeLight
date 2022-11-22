#pragma once
#include "afxdialogex.h"


// ListDlg 对话框

class ListDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ListDlg)

public:
	ListDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~ListDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 这是排列货架序号的列表
	CListCtrl T_List;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonFirst();
	afx_msg void OnBnClickedButtonSecond();
	afx_msg void OnBnClickedButtonSecond2();
};
