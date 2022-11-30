#pragma once
#include "afxdialogex.h"


// kuang 对话框

class kuang : public CDialogEx
{
	DECLARE_DYNAMIC(kuang)

public:
	kuang(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~kuang();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG9 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult);
	// 这是展示搜索结果的
	CListCtrl S_List;
	afx_msg void OnClose();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton3();
	CListCtrl SOU;
	afx_msg void OnBnClickedButton2();
};
