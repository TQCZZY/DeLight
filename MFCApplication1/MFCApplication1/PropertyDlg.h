#pragma once
#include "afxdialogex.h"


// PropertyDlg 对话框

class PropertyDlg : public CDialogEx
{
	DECLARE_DYNAMIC(PropertyDlg)

public:
	PropertyDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~PropertyDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString sType;
	CString sDate;
	CString sNumber;//创建成员
	afx_msg void OnBnClickedButtonOk();
	afx_msg void OnBnClickedButtonNo();
};
