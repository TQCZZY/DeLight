#pragma once
#include "afxdialogex.h"
#include "vector"

extern std::vector<int>b;

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

	DECLARE_MESSAGE_MAP()
public:CString Sousuo;
	afx_msg void OnBnClickedButton1();
};
