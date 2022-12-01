// PropertyDlg.cpp: 实现文件
//

#include "pch.h"
#include "DeLight.h"
#include "afxdialogex.h"
#include "GoodsMngmntDlg.h"


// GoodsMngmntDlg 对话框

IMPLEMENT_DYNAMIC(GoodsMngmntDlg, CDialogEx)

GoodsMngmntDlg::GoodsMngmntDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GOODS_MNG, pParent)
{

}

GoodsMngmntDlg::~GoodsMngmntDlg()
{
}

void GoodsMngmntDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(GoodsMngmntDlg, CDialogEx)
	ON_BN_CLICKED(IDC_GDMDLG_OK, &GoodsMngmntDlg::OnBnClickedButtonOk)
	ON_BN_CLICKED(IDC_GDMDLG_NO, &GoodsMngmntDlg::OnBnClickedButtonNo)
END_MESSAGE_MAP()


// PropertyDlg 消息处理程序


void GoodsMngmntDlg::OnBnClickedButtonOk()//增加中的确定
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItemText(IDC_GDMDLG_TYPE,sType);
	GetDlgItemText(IDC_GDMDLG_DATE, sDate);
	GetDlgItemText(IDC_GDMDLG_NUM, sNumber);
	GetDlgItemText(IDC_GDMDLG_SLF, sShelf);//输入值
	EndDialog(0);//关闭窗口
}


void GoodsMngmntDlg::OnBnClickedButtonNo()
{
	// TODO: 在此添加控件通知处理程序代码
	EndDialog(0);
}
