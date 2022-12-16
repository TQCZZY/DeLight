// ExcelSettingsDlg.cpp: 实现文件
//

#include "pch.h"
#include "DeLight.h"
#include "afxdialogex.h"
#include "ExcelSettingsDlg.h"


// ExcelSettingsDlg 对话框

IMPLEMENT_DYNAMIC(ExcelSettingsDlg, CDialogEx)

ExcelSettingsDlg::ExcelSettingsDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_EXCEL_SETTINGS, pParent)
	, m_psw(_T(""))
	, m_wrpsw(_T(""))
	, readOnly(false)
{

}

ExcelSettingsDlg::~ExcelSettingsDlg()
{
}

void ExcelSettingsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EXSTDLG_RO, m_chkReadOnly);
	DDX_Text(pDX, IDC_EXSTDLG_PSW, m_psw);
	DDX_Text(pDX, IDC_EXSTDLG_WRPSW, m_wrpsw);
}

BEGIN_MESSAGE_MAP(ExcelSettingsDlg, CDialogEx)
	ON_BN_CLICKED(IDC_EXSTDLG_OK, &ExcelSettingsDlg::OnClickedExstdlgOk)
END_MESSAGE_MAP()

// ExcelSettingsDlg 消息处理程序

void ExcelSettingsDlg::OnClickedExstdlgOk()
{
	UpdateData(true);
	readOnly = m_chkReadOnly.GetCheck();
	if (!isConfirm)
	{
		ExcelSettingsDlg dlg;
		dlg.DoModal(true);
		bool confirmSuccess = true;
		CString errMsg = L"设置的\n";
		if (readOnly != dlg.readOnly)
		{
			errMsg += L"- 只读属性\n";
			confirmSuccess = false;
		}
		if (m_psw != dlg.m_psw)
		{
			errMsg += L"- 密码\n";
			confirmSuccess = false;
		}
		if (m_wrpsw != dlg.m_wrpsw)
		{
			errMsg += L"- 写保护密码\n";
			confirmSuccess = false;
		}
		if (!confirmSuccess)
		{
			errMsg += L"与确认时的内容不一致，请留意设置的正确性";
			MessageBox(errMsg, L"检查设置", MB_ICONWARNING);
			return;
		}
	}
	CDialogEx::OnOK();
}

INT_PTR ExcelSettingsDlg::DoModal(bool confirm)
{
	isConfirm = confirm;
	return CDialogEx::DoModal();
}


BOOL ExcelSettingsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	if (isConfirm)
	{
		SetWindowText(L"确认当前设置");
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
