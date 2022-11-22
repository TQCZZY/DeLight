// PropertyDlg2.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "PropertyDlg2.h"


// PropertyDlg2 对话框

IMPLEMENT_DYNAMIC(PropertyDlg2, CDialogEx)

PropertyDlg2::PropertyDlg2(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG5, pParent)
{

}

PropertyDlg2::~PropertyDlg2()
{
}

void PropertyDlg2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(PropertyDlg2, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_OK, &PropertyDlg2::OnBnClickedButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_NO, &PropertyDlg2::OnBnClickedButtonNo)
END_MESSAGE_MAP()


// PropertyDlg2 消息处理程序


void PropertyDlg2::OnBnClickedButtonOk()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItemText(IDC_EDIT_TYPE, sType1);
	GetDlgItemText(IDC_EDIT_TIME, sDate1);
	GetDlgItemText(IDC_EDIT_NUM, sNumber1);//输入值
	EndDialog(0);//关闭窗口
}


void PropertyDlg2::OnBnClickedButtonNo()
{
	// TODO: 在此添加控件通知处理程序代码
	EndDialog(0);//关闭窗口
}
