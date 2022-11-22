#pragma once
#include "afxdialogex.h"


// PropertyDlg2 对话框

class PropertyDlg2 : public CDialogEx
{
	DECLARE_DYNAMIC(PropertyDlg2)

public:
	PropertyDlg2(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~PropertyDlg2();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG5 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString sType1;
	CString sDate1;
	CString sNumber1;//创建成员
	afx_msg void OnBnClickedButtonOk();
	afx_msg void OnBnClickedButtonNo();
};
