#pragma once
#include "afxdialogex.h"


// kuang 对话框

class SearchResultDlg : public CDialogEx
{
	DECLARE_DYNAMIC(SearchResultDlg)

public:
	SearchResultDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~SearchResultDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SRC_RES };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 这是展示搜索结果的
	CListCtrl S_List;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton2();
	CListCtrl SOU;
};
