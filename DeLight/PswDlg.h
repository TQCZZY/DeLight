
// PswDlg.h: 头文件
//

#pragma once

// PswDlg 对话框
class PswDlg : public CDialogEx
{
// 构造
public:
	PswDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PSW_DIALOG };
#endif

// 实现
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonLgn();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
