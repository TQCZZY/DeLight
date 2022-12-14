#pragma once
#include "afxdialogex.h"
#include "vector"

// SearchValueDlg 对话框

class SearchValueDlg : public CDialogEx
{
	DECLARE_DYNAMIC(SearchValueDlg)

public:
	SearchValueDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~SearchValueDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SRC_VAL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	int searchType;
	DECLARE_MESSAGE_MAP()
public:
	CString keyword;
	afx_msg void OnBnClickedButton1();
	virtual INT_PTR DoModal(int st);
};
