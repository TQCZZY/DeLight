#pragma once
#include "afxdialogex.h"

// SearchResultDlg 对话框

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
	bool isOutbound;
	int searchType;
	std::vector<int> searchResult;
	CButton m_btnExport;
	DECLARE_MESSAGE_MAP()
public:
	// 这是展示搜索结果的
	CListCtrl S_List;
	virtual BOOL OnInitDialog();
	afx_msg void OnClickedSelall();
	afx_msg void OnClickedReversesel();
	afx_msg void OnClickedRmv();
	afx_msg void OnClickedSrdlgExport();
	afx_msg void OnClickedSrdlgOut();
	virtual INT_PTR DoModal(int st, std::vector<int> sr);
};
