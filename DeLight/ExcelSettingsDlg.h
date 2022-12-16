#pragma once
#include "afxdialogex.h"


// ExcelSettingsDlg 对话框

class ExcelSettingsDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ExcelSettingsDlg)

public:
	ExcelSettingsDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~ExcelSettingsDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EXCEL_SETTINGS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	CButton m_chkReadOnly;
	bool isConfirm;
public:
	CString m_psw;
	CString m_wrpsw;
	bool readOnly;
	afx_msg void OnClickedExstdlgOk();
	virtual INT_PTR DoModal(bool confirm = false);
	virtual BOOL OnInitDialog();
};
