// Huojia1.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "Huojia1.h"
#include "PropertyDlg2.h"


// Huojia1 对话框

IMPLEMENT_DYNAMIC(Huojia1, CDialogEx)

Huojia1::Huojia1(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG4, pParent)
{

}

Huojia1::~Huojia1()
{
}

void Huojia1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, H1_List);
}


BEGIN_MESSAGE_MAP(Huojia1, CDialogEx)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON1, &Huojia1::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON4, &Huojia1::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON3, &Huojia1::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON7, &Huojia1::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &Huojia1::OnBnClickedButton8)
END_MESSAGE_MAP()


// Huojia1 消息处理程序


void Huojia1::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnClose();
}


BOOL Huojia1::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	H1_List.SetExtendedStyle(LVS_EX_FULLROWSELECT/*整行选中*/ | LVS_EX_CHECKBOXES/*复选框*/);//扩展样式

	H1_List.InsertColumn(0, _T("商品名称"), 0, 200/*宽度*/);
	H1_List.InsertColumn(1, _T("进货时间"), 0, 200);
	H1_List.InsertColumn(2, _T("商品库存"), 0, 200);

	CString itemName, snum, time, thing;
	for (int i = 0; i < 10; i++)
	{
		itemName.Format(_T("%d"), i);
		time.Format(_T("%d"), i);
		snum.Format(_T("%d"), i);
		H1_List.InsertItem(i, itemName);//第一列数据
		H1_List.SetItemText(i, 1, time);
		H1_List.SetItemText(i, 2, snum);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void Huojia1::OnBnClickedButton1()//全选
{
	// TODO: 在此添加控件通知处理程序代码
	for (int i = 0; i < H1_List.GetItemCount/*获取条目的数量*/(); i++)
	{
		H1_List.SetCheck/*设置选中状态*/(i, TRUE);
	}
}


void Huojia1::OnBnClickedButton4()//反选
{
	// TODO: 在此添加控件通知处理程序代码
	for (int i = 0; i < H1_List.GetItemCount/*获取条目的数量*/(); i++)
	{
		H1_List.SetCheck/*设置选中状态*/(i, !H1_List.GetCheck(i));
	}
}


void Huojia1::OnBnClickedButton3()//增添
{
	// TODO: 在此添加控件通知处理程序代码
	PropertyDlg2 dlg;
	dlg.DoModal();//点击增加，弹出子对话框2
	int nCount = H1_List.GetItemCount();
	if (dlg.sType1.IsEmpty() || dlg.sDate1.IsEmpty() || dlg.sNumber1.IsEmpty())
		return;
	H1_List.InsertItem(nCount, dlg.sType1);//新建类型
	H1_List.SetItemText(nCount, 1, dlg.sDate1);
	H1_List.SetItemText(nCount, 2, dlg.sNumber1);
}


void Huojia1::OnBnClickedButton7()//删除
{
	// TODO: 在此添加控件通知处理程序代码
	for (int i = 0; i < H1_List.GetItemCount/*获取条目的数量*/(); i++)
	{
		BOOL state = H1_List.GetCheck(i);
		if (state)
		{
			H1_List.DeleteItem(i);
			i--;//若不i--则不能多项同时删除，因为当删除0栏后，1栏会为0栏，就删不掉了
		}
	}
}


void Huojia1::OnBnClickedButton8()//修改
{
	// TODO: 在此添加控件通知处理程序代码
	for (int i = 0; i < H1_List.GetItemCount/*获取条目的数量*/(); i++)
	{
		BOOL state = H1_List.GetCheck(i);
		if (state)
		{
			PropertyDlg2 dlg;
			dlg.DoModal();//弹窗
			if (dlg.sType1.IsEmpty() || dlg.sDate1.IsEmpty() || dlg.sNumber1.IsEmpty())
				return;
			H1_List.SetItemText(i, 0, dlg.sType1);
			H1_List.SetItemText(i, 1, dlg.sDate1);
			H1_List.SetItemText(i, 2, dlg.sNumber1);

		}

	}
}
