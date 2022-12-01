#pragma once
#include "afxdialogex.h"


// Sou 对话框

class SearchMethodDlg : public CDialogEx
{
	DECLARE_DYNAMIC(SearchMethodDlg)

public:
	SearchMethodDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~SearchMethodDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SRC_MTD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
};
