// SearchValueDlg.cpp: 实现文件
//

#include "pch.h"
#include "DeLight.h"
#include "afxdialogex.h"
#include "List.h"
#include "SearchValueDlg.h"
#include "SearchResultDlg.h"

std::vector<int>b;

// SearchValueDlg 对话框

IMPLEMENT_DYNAMIC(SearchValueDlg, CDialogEx)

SearchValueDlg::SearchValueDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SRC_VAL, pParent)
{

}

SearchValueDlg::~SearchValueDlg()
{
}

void SearchValueDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(SearchValueDlg, CDialogEx)
	ON_BN_CLICKED(IDC_SVDLG_OK, &SearchValueDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// SearchValueDlg 消息处理程序

void SearchValueDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码2
	GetDlgItemText(IDC_SVDLG_VAL, Sousuo);
	USES_CONVERSION;
	switch (Sou2.type) {
	case 1:
	{
		std::string sou1 = W2A(Sousuo);
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
		std::string sou4 = W2A(Sousuo);
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
	b == Search(Sou2);
	EndDialog(0);
	SearchResultDlg dlg;
	dlg.DoModal();
}
