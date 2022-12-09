
// DeLightDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "DeLight.h"
#include "PswDlg.h"
#include "afxdialogex.h"

// PswDlg 对话框

PswDlg::PswDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PSW_DIALOG, pParent)
{
}

void PswDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(PswDlg, CDialogEx)
	ON_BN_CLICKED(IDC_PSWDLG_LGN, &PswDlg::OnBnClickedButtonLgn)
END_MESSAGE_MAP()

// PswDlg 消息处理程序

BOOL PswDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void PswDlg::OnBnClickedButtonLgn()
{
	// TODO: 在此添加控件通知处理程序代码

	CString sun, spwd;//sun为uname,spwd为password
	GetDlgItemText(IDC_PSWDLG_UNAME,sun);
	GetDlgItemText(IDC_PSWDLG_PWD,spwd);
	BOOL isSuccess = !sun.CompareNoCase(_T("admin")) && !spwd.CompareNoCase(_T("123456"));
	if (isSuccess)
	{
		CDialog::OnOK();
	}
	else
	{
		MessageBox(_T("用户名或密码不正确"),_T("登录失败"));//用户登录
	}

}
