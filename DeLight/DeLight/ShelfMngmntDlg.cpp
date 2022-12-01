// PropertyDlg2.cpp: 实现文件
//

#include "pch.h"
#include "DeLight.h"
#include "afxdialogex.h"
#include "ShelfMngmntDlg.h"


// ShelfMngmntDlg 对话框

IMPLEMENT_DYNAMIC(ShelfMngmntDlg, CDialogEx)

ShelfMngmntDlg::ShelfMngmntDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SLF_MNG, pParent)
{

}

ShelfMngmntDlg::~ShelfMngmntDlg()
{
}

void ShelfMngmntDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ShelfMngmntDlg, CDialogEx)
	ON_BN_CLICKED(IDC_SFMDLG_OK, &ShelfMngmntDlg::OnBnClickedButtonOk)
	ON_BN_CLICKED(IDC_SFMDLG_NO, &ShelfMngmntDlg::OnBnClickedButtonNo)
END_MESSAGE_MAP()


// ShelfMngmntDlg 消息处理程序

void ShelfMngmntDlg::OnBnClickedButtonOk()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItemText(IDC_SFMDLG_TYPE, sType1);
	GetDlgItemText(IDC_SFMDLG_TIME, sDate1);
	GetDlgItemText(IDC_SFMDLG_NUM, sNumber1);//输入值
	EndDialog(0);//关闭窗口
}


void ShelfMngmntDlg::OnBnClickedButtonNo()
{
	// TODO: 在此添加控件通知处理程序代码
	EndDialog(0);//关闭窗口
}
