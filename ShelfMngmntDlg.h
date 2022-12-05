#pragma once
#include "afxdialogex.h"


// ShelfMngmntDlg 对话框

class ShelfMngmntDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ShelfMngmntDlg)

public:
	ShelfMngmntDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~ShelfMngmntDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SLF_MNG };
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
