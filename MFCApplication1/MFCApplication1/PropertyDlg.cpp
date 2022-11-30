// PropertyDlg.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "PropertyDlg.h"


// PropertyDlg 对话框

IMPLEMENT_DYNAMIC(PropertyDlg, CDialogEx)

PropertyDlg::PropertyDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{

}

PropertyDlg::~PropertyDlg()
{
}

void PropertyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(PropertyDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_OK, &PropertyDlg::OnBnClickedButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_NO, &PropertyDlg::OnBnClickedButtonNo)
	ON_EN_CHANGE(IDC_EDIT_TYPE, &PropertyDlg::OnEnChangeEditType)
END_MESSAGE_MAP()


// PropertyDlg 消息处理程序


void PropertyDlg::OnBnClickedButtonOk()//增加中的确定
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItemText(IDC_EDIT_TYPE,sType);
	GetDlgItemText(IDC_EDIT_DATE, sDate);
	GetDlgItemText(IDC_EDIT_NUM, sNumber);
	GetDlgItemText(IDC_EDIT_THING, sThing);//输入值
	EndDialog(0);//关闭窗口
}


void PropertyDlg::OnBnClickedButtonNo()
{
	// TODO: 在此添加控件通知处理程序代码
	EndDialog(0);
}
