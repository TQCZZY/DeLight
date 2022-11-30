// Guocheng.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "Guocheng.h"
#include "kuang.h"
#include "data.cpp"
#include "List.cpp"

// Guocheng 对话框

IMPLEMENT_DYNAMIC(Guocheng, CDialogEx)

Guocheng::Guocheng(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG10, pParent)
{

}

Guocheng::~Guocheng()
{
}

void Guocheng::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Guocheng, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &Guocheng::OnBnClickedButton1)
END_MESSAGE_MAP()


// Guocheng 消息处理程序
std::vector<int>middle;

void Guocheng::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码2
	GetDlgItemText(IDC_EDIT_SOU, Sousuo);
	switch (Sou2.type) {
	case 1:
	{
		std::string sou1 = Sousuo.GetBuffer();
		Sou2.name = sou1;
	}
	case 2:
	{
		int sou2;
		sou2 = _ttoi(Sousuo);
		Sou2.amount = sou2;
	}
	case 3:
	{
		int sou3;
		sou3 = _ttoi(Sousuo);
		Sou2.location = sou3;
	}
	case 4:
	{
		std::string sou4 = Sousuo.GetBuffer();
		Time t = { 0,0,0 };
		int p=0;
		while (sou4[p] != '-') {
			t.year *= 10;
			t.year += sou4[p++] - '0';
		}
		p++;
		while (sou4[p] != '-') {
			t.month *= 10;
			t.month += sou4[p++] - '0';
		}
		p++;
		while (sou4[p] != '\0') {
			t.date *= 10;
			t.date += sou4[p++] - '0';
		}
		Sou2.time.year=t.year;
		Sou2.time.month = t.month;
		Sou2.time.date = t.date;
	}
	}
	auto b = Search(Sou2);
	middle = Search_Return:b.numbers;
	EndDialog(0);
	kuang dlg;
	dlg.DoModal();
}
