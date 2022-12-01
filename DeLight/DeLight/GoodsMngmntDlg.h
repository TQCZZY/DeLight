#pragma once
#include "afxdialogex.h"


// GoodsMngmntDlg 对话框

class GoodsMngmntDlg : public CDialogEx
{
	DECLARE_DYNAMIC(GoodsMngmntDlg)

public:
	GoodsMngmntDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~GoodsMngmntDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD_GOODS_MNG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString sType;
	CString sDate;
	CString sNumber;
	CString sShelf;//创建成员
	afx_msg void OnBnClickedButtonOk();
	afx_msg void OnBnClickedButtonNo();
};
