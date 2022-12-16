// Sou.cpp: 实现文件
//

#include "pch.h"
#include "DeLight.h"
#include "afxdialogex.h"
#include <string>
#include <vector>
#include "List.h"
#include "SearchMethodDlg.h"
#include "SearchValueDlg.h"

// Sou 对话框

IMPLEMENT_DYNAMIC(SearchMethodDlg, CDialogEx)

SearchMethodDlg::SearchMethodDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SRC_MTD, pParent)
{

}

SearchMethodDlg::~SearchMethodDlg()
{
}

void SearchMethodDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(SearchMethodDlg, CDialogEx)
	ON_BN_CLICKED(IDC_SMDLG_NM, &SearchMethodDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_SMDLG_DT, &SearchMethodDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_SMDLG_QT, &SearchMethodDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_SMDLG_SF, &SearchMethodDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// Sou 消息处理程序


void SearchMethodDlg::OnBnClickedButton1()//名称
{
	// TODO: 在此添加控件通知处理程序代码
	Sou2.type = 1;
	SearchValueDlg dlg;
	dlg.DoModal();
}


void SearchMethodDlg::OnBnClickedButton2()//时间
{
	// TODO: 在此添加控件通知处理程序代码
	Sou2.type = 4;
	SearchValueDlg dlg;
	dlg.DoModal();
}


void SearchMethodDlg::OnBnClickedButton3()//数量
{
	// TODO: 在此添加控件通知处理程序代码
	Sou2.type = 2;
	SearchValueDlg dlg;
	dlg.DoModal();
}


void SearchMethodDlg::OnBnClickedButton4()//货架
{
	// TODO: 在此添加控件通知处理程序代码
	Sou2.type = 3;
	SearchValueDlg dlg;
	dlg.DoModal();
}
