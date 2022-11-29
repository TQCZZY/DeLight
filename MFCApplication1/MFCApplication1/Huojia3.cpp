// Huojia3.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "Huojia3.h"
#include "PropertyDlg2.h"

// Huojia3 对话框

IMPLEMENT_DYNAMIC(Huojia3, CDialogEx)

Huojia3::Huojia3(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG7, pParent)
{

}

Huojia3::~Huojia3()
{
}

void Huojia3::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, H3_List);
}


BEGIN_MESSAGE_MAP(Huojia3, CDialogEx)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &Huojia3::OnLvnItemchangedList1)
	ON_BN_CLICKED(IDC_BUTTON1, &Huojia3::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON4, &Huojia3::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON7, &Huojia3::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON3, &Huojia3::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON6, &Huojia3::OnBnClickedButton6)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// Huojia3 消息处理程序


void Huojia3::OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void Huojia3::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnClose();
}


BOOL Huojia3::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	H3_List.SetExtendedStyle(LVS_EX_FULLROWSELECT/*整行选中*/ | LVS_EX_CHECKBOXES/*复选框*/);//扩展样式

	H3_List.InsertColumn(0, _T("商品名称"), 0, 200/*宽度*/);
	H3_List.InsertColumn(1, _T("进货时间"), 0, 200);
	H3_List.InsertColumn(2, _T("商品库存"), 0, 200);

	CString itemName, snum, time, thing;
	for (int i = 0; i < 10; i++)
	{
		itemName.Format(_T("%d"), i);
		time.Format(_T("%d"), i);
		snum.Format(_T("%d"), i);
		H3_List.InsertItem(i, itemName);//第一列数据
		H3_List.SetItemText(i, 1, time);
		H3_List.SetItemText(i, 2, snum);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void Huojia3::OnBnClickedButton1()//全选
{
	// TODO: 在此添加控件通知处理程序代码
	for (int i = 0; i < H3_List.GetItemCount/*获取条目的数量*/(); i++)
	{
		H3_List.SetCheck/*设置选中状态*/(i, TRUE);
	}
}


void Huojia3::OnBnClickedButton7()//反选
{
	// TODO: 在此添加控件通知处理程序代码
	for (int i = 0; i < H3_List.GetItemCount/*获取条目的数量*/(); i++)
	{
		H3_List.SetCheck/*设置选中状态*/(i, !H3_List.GetCheck(i));
	}
}


void Huojia3::OnBnClickedButton3()//增添
{
	// TODO: 在此添加控件通知处理程序代码
	PropertyDlg2 dlg;
	dlg.DoModal();//点击增加，弹出子对话框2
	int nCount = H3_List.GetItemCount();
	if (dlg.sType1.IsEmpty() || dlg.sDate1.IsEmpty() || dlg.sNumber1.IsEmpty())
		return;
	H3_List.InsertItem(nCount, dlg.sType1);//新建类型
	H3_List.SetItemText(nCount, 1, dlg.sDate1);
	H3_List.SetItemText(nCount, 2, dlg.sNumber1);
}


void Huojia3::OnBnClickedButton4()//删除
{
	// TODO: 在此添加控件通知处理程序代码
	for (int i = 0; i < H3_List.GetItemCount/*获取条目的数量*/(); i++)
	{
		BOOL state = H3_List.GetCheck(i);
		if (state)
		{
			H3_List.DeleteItem(i);
			i--;//若不i--则不能多项同时删除，因为当删除0栏后，1栏会为0栏，就删不掉了
		}
	}
}


void Huojia3::OnBnClickedButton6()//修改
{
	// TODO: 在此添加控件通知处理程序代码
	for (int i = 0; i < H3_List.GetItemCount/*获取条目的数量*/(); i++)
	{
		BOOL state = H3_List.GetCheck(i);
		if (state)
		{
			PropertyDlg2 dlg;
			dlg.DoModal();//弹窗
			if (dlg.sType1.IsEmpty() || dlg.sDate1.IsEmpty() || dlg.sNumber1.IsEmpty())
				return;
			H3_List.SetItemText(i, 0, dlg.sType1);
			H3_List.SetItemText(i, 1, dlg.sDate1);
			H3_List.SetItemText(i, 2, dlg.sNumber1);

		}

	}
}


