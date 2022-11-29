#pragma once
#include "afxdialogex.h"


// Huojia1 对话框

class Huojia1 : public CDialogEx
{
	DECLARE_DYNAMIC(Huojia1)

public:
	Huojia1(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Huojia1();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG4 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 1号货物列表
	CListCtrl H1_List;
	afx_msg void OnClose();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton11();
	afx_msg void OnBnClickedButton12();
};
