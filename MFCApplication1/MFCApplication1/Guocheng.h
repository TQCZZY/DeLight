#pragma once
#include "afxdialogex.h"


// Guocheng 对话框

class Guocheng : public CDialogEx
{
	DECLARE_DYNAMIC(Guocheng)

public:
	Guocheng(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Guocheng();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG10 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:CString Sousuo;
	afx_msg void OnBnClickedButton1();
};
