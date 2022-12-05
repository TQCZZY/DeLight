// Huojia1.cpp: 实现文件
//

#include "pch.h"
#include "DeLight.h"
#include "afxdialogex.h"
#include <string>
#include <vector>
#include "List.h"
#include "ShelfDetailDlg.h"
#include "GoodsMngmntDlg.h"

// Huojia1 对话框

IMPLEMENT_DYNAMIC(ShelfDetailDlg, CDialogEx)

ShelfDetailDlg::ShelfDetailDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SLF_DTL, pParent)
{
	shelfNumber = -1;
}

ShelfDetailDlg::~ShelfDetailDlg()
{
}

void ShelfDetailDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SFDTLDLG_LIST, H1_List);
}


BEGIN_MESSAGE_MAP(ShelfDetailDlg, CDialogEx)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_SFDTLDLG_SELALL, &ShelfDetailDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_SFDTLDLG_REVERSESEL, &ShelfDetailDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_SFDTLDLG_ADD, &ShelfDetailDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_SFDTLDLG_DEL, &ShelfDetailDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_SFDTLDLG_EDIT, &ShelfDetailDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_SFDTLDLG_SORT_NM, &ShelfDetailDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_SFDTLDLG_SORT_DT, &ShelfDetailDlg::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_SFDTLDLG_SORT_QT, &ShelfDetailDlg::OnBnClickedButton12)
END_MESSAGE_MAP()


// Huojia1 消息处理程序


void ShelfDetailDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnClose();
}


BOOL ShelfDetailDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CString winText;
	winText.Format(_T("货架 %d 详情"), shelfNumber);
	SetWindowText(winText);
	H1_List.SetExtendedStyle(LVS_EX_FULLROWSELECT/*整行选中*/ | LVS_EX_CHECKBOXES/*复选框*/);//扩展样式

	H1_List.InsertColumn(0, _T("商品名称"), 0, 200/*宽度*/);
	H1_List.InsertColumn(1, _T("进货时间"), 0, 200);
	H1_List.InsertColumn(2, _T("商品库存"), 0, 200);

	transform(true);
	indexInCom.clear();
	for (int i = 0; i < Com.size(); i++)
	{
		if (Com[i].shelfNo == shelfNumber)
		{
			H1_List.InsertItem(i, L"");
			H1_List.SetItemText(i, 0, Com[i].name);
			H1_List.SetItemText(i, 1, Com[i].time);
			H1_List.SetItemText(i, 2, Com[i].num);
			H1_List.SetItemText(i, 3, Com[i].shelf);
			indexInCom.push_back(i);
		}
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void ShelfDetailDlg::OnBnClickedButton1()//全选
{
	// TODO: 在此添加控件通知处理程序代码
	for (int i = 0; i < H1_List.GetItemCount/*获取条目的数量*/(); i++)
	{
		H1_List.SetCheck/*设置选中状态*/(i, TRUE);
	}
}


void ShelfDetailDlg::OnBnClickedButton4()//反选
{
	// TODO: 在此添加控件通知处理程序代码
	for (int i = 0; i < H1_List.GetItemCount/*获取条目的数量*/(); i++)
	{
		H1_List.SetCheck/*设置选中状态*/(i, !H1_List.GetCheck(i));
	}
}


void ShelfDetailDlg::OnBnClickedButton3()//增添
{
	// TODO: 在此添加控件通知处理程序代码
	GoodsMngmntDlg dlg;
	if (IDCANCEL == dlg.DoModal(L"", L"", L"", L"", true) ||//点击增加，弹出子对话框2
	dlg.sType.IsEmpty() || dlg.sDate.IsEmpty() || dlg.sNumber.IsEmpty())
		return;
	int nCount = H1_List.GetItemCount();
	H1_List.InsertItem(nCount, L"");
	H1_List.SetItemText(nCount, 0, dlg.sType);
	H1_List.SetItemText(nCount, 1, dlg.sDate);
	H1_List.SetItemText(nCount, 2, dlg.sNumber);

	Good_Info new_good;
	USES_CONVERSION;
	new_good.name = W2A(dlg.sType);

	std::string sou4 = W2A(dlg.sDate);
	Time t = { 0,0,0 };
	int p = 0;
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
	new_good.time.year = t.year;
	new_good.time.month = t.month;
	new_good.time.date = t.date;

	new_good.amount = _ttoi(dlg.sNumber);
	new_good.location = shelfNumber;
	Insert(new_good);
	transform(true);
}


void ShelfDetailDlg::OnBnClickedButton7()//删除
{
	// TODO: 在此添加控件通知处理程序代码
	size_t realIdx = 0;
	for (int i = 0; i < H1_List.GetItemCount/*获取条目的数量*/(); ++i, ++realIdx)
	{
		BOOL state = H1_List.GetCheck(i);
		if (state)
		{
			Delete(Com[realIdx].code);
			H1_List.DeleteItem(i);
			i--;//若不i--则不能多项同时删除，因为当删除0栏后，1栏会为0栏，就删不掉了
		}
	}
	transform(true);
}


void ShelfDetailDlg::OnBnClickedButton8()//修改
{
	// TODO: 在此添加控件通知处理程序代码
	size_t realIdx = 0;
	for (int i = 0; i < H1_List.GetItemCount/*获取条目的数量*/(); ++i, ++realIdx)
	{
		BOOL state = H1_List.GetCheck(i);
		if (state)
		{
			GoodsMngmntDlg dlg;
			if (IDCANCEL == dlg.DoModal(Com[indexInCom[i]].name, Com[indexInCom[i]].num, Com[indexInCom[i]].time, Com[indexInCom[i]].shelf, true) ||//弹窗
				dlg.sType.IsEmpty() || dlg.sDate.IsEmpty() || dlg.sNumber.IsEmpty())
				return;
			H1_List.SetItemText(i, 0, dlg.sType);
			H1_List.SetItemText(i, 1, dlg.sDate);
			H1_List.SetItemText(i, 2, dlg.sNumber);
			Delete(Com[indexInCom[i]].code);
			Good_Info new_good;
			USES_CONVERSION;
			new_good.name = W2A(dlg.sType);

			std::string sou4 = W2A(dlg.sDate);
			Time t = { 0,0,0 };
			int p = 0;
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
			new_good.time.year = t.year;
			new_good.time.month = t.month;
			new_good.time.date = t.date;

			new_good.amount = _ttoi(dlg.sNumber);
			new_good.location = _ttoi(dlg.sShelf);
			Insert(new_good, indexInCom[i]);
		}
	}
	transform(true);
}


void ShelfDetailDlg::OnBnClickedButton2()//排序1
{
	// TODO: 在此添加控件通知处理程序代码
	for (int i = 0; i < H1_List.GetItemCount/*获取条目的数量*/(); i++)
	{
		H1_List.SetCheck/*设置选中状态*/(i, TRUE);
	}

	for (int i = 0; i < H1_List.GetItemCount/*获取条目的数量*/(); i++)
	{
		BOOL state = H1_List.GetCheck(i);
		if (state)
		{
			H1_List.DeleteItem(i);
			i--;//若不i--则不能多项同时删除，因为当删除0栏后，1栏会为0栏，就删不掉了
		}
	}

	Sort(1);
	transform(true);
	for (int i = 0; i < Com.size(); i++)
	{
		if (Com[i].shelfNo == shelfNumber)
		{
			H1_List.InsertItem(i, Com[i].name);//第一列数据
			H1_List.SetItemText(i, 1, Com[i].time);
			H1_List.SetItemText(i, 2, Com[i].num);
			H1_List.SetItemText(i, 3, Com[i].shelf);
		}
	}
}


void ShelfDetailDlg::OnBnClickedButton11()//排序2
{
	// TODO: 在此添加控件通知处理程序代码
	for (int i = 0; i < H1_List.GetItemCount/*获取条目的数量*/(); i++)
	{
		H1_List.SetCheck/*设置选中状态*/(i, TRUE);
	}

	for (int i = 0; i < H1_List.GetItemCount/*获取条目的数量*/(); i++)
	{
		BOOL state = H1_List.GetCheck(i);
		if (state)
		{
			H1_List.DeleteItem(i);
			i--;//若不i--则不能多项同时删除，因为当删除0栏后，1栏会为0栏，就删不掉了
		}
	}

	Sort(4);
	transform(true);
	for (int i = 0; i < Com.size(); i++)
	{
		if (Com[i].shelfNo == shelfNumber)
		{
			H1_List.InsertItem(i, Com[i].name);//第一列数据
			H1_List.SetItemText(i, 1, Com[i].time);
			H1_List.SetItemText(i, 2, Com[i].num);
			H1_List.SetItemText(i, 3, Com[i].shelf);
		}
	}
}


void ShelfDetailDlg::OnBnClickedButton12()//排序3
{
	// TODO: 在此添加控件通知处理程序代码
	for (int i = 0; i < H1_List.GetItemCount/*获取条目的数量*/(); i++)
	{
		H1_List.SetCheck/*设置选中状态*/(i, TRUE);
	}

	for (int i = 0; i < H1_List.GetItemCount/*获取条目的数量*/(); i++)
	{
		BOOL state = H1_List.GetCheck(i);
		if (state)
		{
			H1_List.DeleteItem(i);
			i--;//若不i--则不能多项同时删除，因为当删除0栏后，1栏会为0栏，就删不掉了
		}
	}

	Sort(2);
	transform(true);
	for (int i = 0; i < Com.size(); i++)
	{
		if (Com[i].shelfNo == shelfNumber)
		{
			H1_List.InsertItem(i, Com[i].name);//第一列数据
			H1_List.SetItemText(i, 1, Com[i].time);
			H1_List.SetItemText(i, 2, Com[i].num);
			H1_List.SetItemText(i, 3, Com[i].shelf);
		}
	}
}


INT_PTR ShelfDetailDlg::DoModal(int shelfNo)
{
	shelfNumber = shelfNo;

	return CDialogEx::DoModal();
}
