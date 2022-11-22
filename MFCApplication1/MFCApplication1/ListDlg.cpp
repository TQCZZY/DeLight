// ListDlg.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "ListDlg.h"
#include "Huojia1.h"
#include "Huojia2.h"
#include "Huojia3.h"


// ListDlg 对话框

IMPLEMENT_DYNAMIC(ListDlg, CDialogEx)

ListDlg::ListDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG3, pParent)
{

}

ListDlg::~ListDlg()
{
}

void ListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, T_List);
}


BEGIN_MESSAGE_MAP(ListDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_FIRST, &ListDlg::OnBnClickedButtonFirst)
	ON_BN_CLICKED(IDC_BUTTON_SECOND, &ListDlg::OnBnClickedButtonSecond)
	ON_BN_CLICKED(IDC_BUTTON_SECOND2, &ListDlg::OnBnClickedButtonSecond2)
END_MESSAGE_MAP()


// ListDlg 消息处理程序


BOOL ListDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	T_List.InsertColumn(0, _T("货架编号"), 0, 200/*宽度*/);

	CString sthing;
	for (int i = 1; i < 4; i++)
	{
		sthing.Format(_T("%d号货架"), i);
		T_List.InsertItem(i, sthing);
	}
	

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void ListDlg::OnBnClickedButtonFirst()//1号货架
{
	// TODO: 在此添加控件通知处理程序代码
	Huojia1 dlg;
	dlg.DoModal();
}


void ListDlg::OnBnClickedButtonSecond()//2号货架
{
	// TODO: 在此添加控件通知处理程序代码
	Huojia2 dlg;
	dlg.DoModal();
}


void ListDlg::OnBnClickedButtonSecond2()//3号货架
{
	// TODO: 在此添加控件通知处理程序代码
	Huojia3 dlg;
	dlg.DoModal();
}
