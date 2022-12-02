// SearchResultDlg.cpp: 实现文件
//

#include "pch.h"
#include "DeLight.h"
#include "afxdialogex.h"
#include "List.h"
#include "SearchResultDlg.h"
#include "SearchValueDlg.h"

// SearchResultDlg 对话框

IMPLEMENT_DYNAMIC(SearchResultDlg, CDialogEx)

SearchResultDlg::SearchResultDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SRC_RES, pParent)
{

}

SearchResultDlg::~SearchResultDlg()
{
}

void SearchResultDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SRDLG_LIST, S_List);
}


BEGIN_MESSAGE_MAP(SearchResultDlg, CDialogEx)
	ON_BN_CLICKED(IDC_SRDLG_SELALL, &SearchResultDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_SRDLG_REVERSESEL, &SearchResultDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_SRDLG_DEL, &SearchResultDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// kuang 消息处理程序

BOOL SearchResultDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	S_List.SetExtendedStyle(LVS_EX_FULLROWSELECT/*整行选中*/ | LVS_EX_CHECKBOXES/*复选框*/);//扩展样式

	S_List.InsertColumn(0, _T("商品名称"), 0, 200/*宽度*/);
	S_List.InsertColumn(1, _T("进货时间"), 0, 200);
	S_List.InsertColumn(2, _T("商品库存"), 0, 200);
	S_List.InsertColumn(3, _T("货架编号"), 0, 200);

	for (int i = 0; i < Com.size(); i++)
	{
		for(int j=0;j<b.size();j++)
			if(Com[i].code==b[j])
			{
				S_List.InsertItem(i, Com[i].name);//第一列数据
				S_List.SetItemText(i, 1, Com[i].time);
				S_List.SetItemText(i, 2, Com[i].num);
				S_List.SetItemText(i, 3, Com[i].shelf);
				break;
			}
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void SearchResultDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	for (int i = 0; i < S_List.GetItemCount/*获取条目的数量*/(); i++)
	{
		S_List.SetCheck/*设置选中状态*/(i, TRUE);
	}
}


void SearchResultDlg::OnBnClickedButton7()
{
	// TODO: 在此添加控件通知处理程序代码
	for (int i = 0; i < S_List.GetItemCount/*获取条目的数量*/(); i++)
	{
		S_List.SetCheck/*设置选中状态*/(i, !S_List.GetCheck(i));
	}
}



void SearchResultDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	for (int i = 0; i < S_List.GetItemCount/*获取条目的数量*/(); i++)
	{
		BOOL state = S_List.GetCheck(i);
		if (state)
		{
			S_List.DeleteItem(i);
			i--;//若不i--则不能多项同时删除，因为当删除0栏后，1栏会为0栏，就删不掉了
		}
	}
}
