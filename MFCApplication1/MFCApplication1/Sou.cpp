// Sou.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "Sou.h"
#include "Guocheng.h"
#include "List.cpp"
#include<vector>
#include "data.cpp"

// Sou 对话框

IMPLEMENT_DYNAMIC(Sou, CDialogEx)

Sou::Sou(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG8, pParent)
{

}

Sou::~Sou()
{
}

void Sou::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Sou, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &Sou::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &Sou::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &Sou::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &Sou::OnBnClickedButton4)
END_MESSAGE_MAP()


// Sou 消息处理程序


void Sou::OnBnClickedButton1()//名称
{
	// TODO: 在此添加控件通知处理程序代码
	Guocheng dlg;
	dlg.DoModal();
	Sou2.type = 1;
}


void Sou::OnBnClickedButton2()//时间
{
	// TODO: 在此添加控件通知处理程序代码
	Guocheng dlg;
	dlg.DoModal();
	Sou2.type = 4;
}


void Sou::OnBnClickedButton3()//数量
{
	// TODO: 在此添加控件通知处理程序代码
	Guocheng dlg;
	dlg.DoModal();
	Sou2.type = 2;
}


void Sou::OnBnClickedButton4()//货架
{
	// TODO: 在此添加控件通知处理程序代码
	Guocheng dlg;
	dlg.DoModal();
	Sou2.type = 3;
}
