// SystemDlg.cpp: 实现文件
//

#include "pch.h"
#include "afxdialogex.h"
#include "resource.h"
#include <string>
#include <vector>
#include "List.h"
#include "SystemDlg.h"
#include "PswDlg.h"
#include "GoodsMngmntDlg.h"
#include "ShelfListDlg.h"
#include "QueryDlg.h"
#include "SearchMethodDlg.h"
#include "map.hpp"
#include "Lines.hpp"
#include "Excel.hpp"


// SystemDlg 对话框

IMPLEMENT_DYNAMIC(SystemDlg, CDialogEx)

SystemDlg::SystemDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SYSTEMDLG, pParent)
{
}

SystemDlg::~SystemDlg()
{
}

void SystemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SYSDLG_LIST, m_List);
}


BEGIN_MESSAGE_MAP(SystemDlg, CDialogEx)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_SYSDLG_SELALL, &SystemDlg::OnBnClickedSelall)
	ON_BN_CLICKED(IDC_SYSDLG_REVERSESEL, &SystemDlg::OnBnClickedReversesel)
	ON_BN_CLICKED(IDC_SYSDLG_ADD, &SystemDlg::OnBnClickedAdd)
	ON_BN_CLICKED(IDC_SYSDLG_DEL, &SystemDlg::OnBnClickedDel)
	ON_BN_CLICKED(IDC_SYSDLG_EDIT, &SystemDlg::OnBnClickedEdit)
	ON_BN_CLICKED(IDC_SYSDLG_SLFDTL, &SystemDlg::OnBnClickedSlfDtl)
	ON_BN_CLICKED(IDC_SYSDLG_SEARCH, &SystemDlg::OnBnClickedSearch)
	ON_BN_CLICKED(IDC_REMOTEQUERY, &SystemDlg::OnBnClickedRemotequery)
	ON_BN_CLICKED(IDC_GLBTOEXCEL, &SystemDlg::OnBnClickedGlbtoexcel)
	ON_BN_CLICKED(IDC_SYSDLG_SORT_NM, &SystemDlg::OnBnClickedSortnm)
	ON_BN_CLICKED(IDC_SYSDLG_SORT_DT, &SystemDlg::OnBnClickedSortdt)
	ON_BN_CLICKED(IDC_SYSDLG_SORT_QT, &SystemDlg::OnBnClickedSortqt)
	ON_BN_CLICKED(IDC_SYSDLG_SORT_SF, &SystemDlg::OnBnClickedSortsf)
	ON_BN_CLICKED(IDC_SYSDLG_SELDST, &SystemDlg::OnBnClickedSysdlgSeldst)
END_MESSAGE_MAP()


// SystemDlg 消息处理程序


void SystemDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CDialog* pdlg = (CDialog*)AfxGetMainWnd();//pdlg为主窗口的的指针
	pdlg->DestroyWindow();
	CDialogEx::OnClose();//关闭主窗口的方式
}


BOOL SystemDlg::OnInitDialog()
{
	PswDlg d;
	d.DoModal();
	CDialogEx::OnInitDialog();

	head->next = NULL;
	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT/*整行选中*/ | LVS_EX_CHECKBOXES/*复选框*/);//扩展样式

	m_List.InsertColumn(0, _T("商品名称"),0,200/*宽度*/);
	m_List.InsertColumn(1, _T("进货时间"),0,200);
	m_List.InsertColumn(2, _T("商品库存"),0,200);
	m_List.InsertColumn(3, _T("货架编号"), 0, 200);

	//CString itemName,snum,time,thing;
	for(int i=0;i<Com.size(); i++)
	{
		m_List.InsertItem(i,Com[i].name);//第一列数据
		m_List.SetItemText(i, 1, Com[i].time);
		m_List.SetItemText(i, 2, Com[i].num);
		m_List.SetItemText(i, 3, Com[i].shelf);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
}


void SystemDlg::OnBnClickedSelall()//全选
{
	for (int i = 0; i < m_List.GetItemCount/*获取条目的数量*/(); i++)
	{
		m_List.SetCheck/*设置选中状态*/(i,TRUE);
	}
}


void SystemDlg::OnBnClickedReversesel()//反选
{
	for (int i = 0; i < m_List.GetItemCount/*获取条目的数量*/(); i++)
	{
		m_List.SetCheck/*设置选中状态*/(i, !m_List.GetCheck(i));
	}
}


void SystemDlg::OnBnClickedAdd()//增加
{
	GoodsMngmntDlg dlg;
	if (IDCANCEL == dlg.DoModal(L"", L"", L"", L"", false) ||//点击增加，弹出子对话框2
		dlg.sType.IsEmpty() || dlg.sDate.IsEmpty() || dlg.sNumber.IsEmpty() || dlg.sShelf.IsEmpty())
		return;
	int nCount = m_List.GetItemCount();
	m_List.InsertItem(nCount,dlg.sType);//新建类型
	m_List.SetItemText(nCount, 1, dlg.sDate);
	m_List.SetItemText(nCount, 2, dlg.sNumber);
	m_List.SetItemText(nCount, 3, dlg.sShelf);
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
	new_good.location= _ttoi(dlg.sShelf);
	Insert(new_good);
	transform(true);
}


void SystemDlg::OnBnClickedDel()//删除
{
	for (int i = 0; i < m_List.GetItemCount/*获取条目的数量*/(); i++)
	{
		BOOL state = m_List.GetCheck(i);
		if (state)
		{
			m_List.DeleteItem(i);
			Delete(Com[i].code);
			i--;//若不i--则不能多项同时删除，因为当删除0栏后，1栏会为0栏，就删不掉了
		}
	}
	transform(true);
}


void SystemDlg::OnBnClickedEdit()//修改
{
	for (int i = 0; i < m_List.GetItemCount/*获取条目的数量*/(); i++)
	{
		BOOL state = m_List.GetCheck(i);
		if (state)
		{
			GoodsMngmntDlg dlg;
			if (IDCANCEL == dlg.DoModal(Com[i].name, Com[i].num, Com[i].time, Com[i].shelf, false) ||//弹窗
				dlg.sType.IsEmpty() || dlg.sDate.IsEmpty() || dlg.sNumber.IsEmpty() || dlg.sShelf.IsEmpty())
				return;
			m_List.SetItemText(i, 0, dlg.sType);
			m_List.SetItemText(i, 1, dlg.sDate);
			m_List.SetItemText(i, 2, dlg.sNumber);
			m_List.SetItemText(i, 3, dlg.sShelf);
			Delete(Com[i].code);
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
			Insert(new_good, i);
		}
	}
	transform(true);
}


void SystemDlg::OnBnClickedSlfDtl()//货架详情
{
	// TODO: 在此添加控件通知处理程序代码
	ShelfListDlg dlg;
	dlg.DoModal();
}


void SystemDlg::OnBnClickedSortnm()//排序1
{
	for (int i = 0; i < m_List.GetItemCount/*获取条目的数量*/(); i++)
	{
		m_List.SetCheck/*设置选中状态*/(i, TRUE);
	}

	for (int i = 0; i < m_List.GetItemCount/*获取条目的数量*/(); i++)
	{
		BOOL state = m_List.GetCheck(i);
		if (state)
		{
			m_List.DeleteItem(i);
			i--;//若不i--则不能多项同时删除，因为当删除0栏后，1栏会为0栏，就删不掉了
		}
	}
	Sort(1);
	transform(true);
	for (int i = 0; i < Com.size(); i++)
	{
		m_List.InsertItem(i, Com[i].name);//第一列数据
		m_List.SetItemText(i, 1, Com[i].time);
		m_List.SetItemText(i, 2, Com[i].num);
		m_List.SetItemText(i, 3, Com[i].shelf);
	}
}


void SystemDlg::OnBnClickedSortdt()//排序2
{
	for (int i = 0; i < m_List.GetItemCount/*获取条目的数量*/(); i++)
	{
		m_List.SetCheck/*设置选中状态*/(i, TRUE);
	}

	for (int i = 0; i < m_List.GetItemCount/*获取条目的数量*/(); i++)
	{
		BOOL state = m_List.GetCheck(i);
		if (state)
		{
			m_List.DeleteItem(i);
			i--;//若不i--则不能多项同时删除，因为当删除0栏后，1栏会为0栏，就删不掉了
		}
	}

	Sort(4);
	transform(true);
	for (int i = 0; i < Com.size(); i++)
	{
		m_List.InsertItem(i, Com[i].name);//第一列数据
		m_List.SetItemText(i, 1, Com[i].time);
		m_List.SetItemText(i, 2, Com[i].num);
		m_List.SetItemText(i, 3, Com[i].shelf);
	}
}


void SystemDlg::OnBnClickedSortqt()//排序3
{
	// TODO: 在此添加控件通知处理程序代码
	for (int i = 0; i < m_List.GetItemCount/*获取条目的数量*/(); i++)
	{
		m_List.SetCheck/*设置选中状态*/(i, TRUE);
	}

	for (int i = 0; i < m_List.GetItemCount/*获取条目的数量*/(); i++)
	{
		BOOL state = m_List.GetCheck(i);
		if (state)
		{
			m_List.DeleteItem(i);
			i--;//若不i--则不能多项同时删除，因为当删除0栏后，1栏会为0栏，就删不掉了
		}
	}

	Sort(2);
	transform(true);
	for (int i = 0; i < Com.size(); i++)
	{
		m_List.InsertItem(i, Com[i].name);//第一列数据
		m_List.SetItemText(i, 1, Com[i].time);
		m_List.SetItemText(i, 2, Com[i].num);
		m_List.SetItemText(i, 3, Com[i].shelf);
	}
}


void SystemDlg::OnBnClickedSortsf()//排序4
{
	for (int i = 0; i < m_List.GetItemCount/*获取条目的数量*/(); i++)
	{
		m_List.SetCheck/*设置选中状态*/(i, TRUE);
	}

	for (int i = 0; i < m_List.GetItemCount/*获取条目的数量*/(); i++)
	{
		BOOL state = m_List.GetCheck(i);
		if (state)
		{
			m_List.DeleteItem(i);
			i--;//若不i--则不能多项同时删除，因为当删除0栏后，1栏会为0栏，就删不掉了
		}
	}

	Sort(3);
	transform(true);
	for (int i = 0; i < Com.size(); i++)
	{
		m_List.InsertItem(i, Com[i].name);//第一列数据
		m_List.SetItemText(i, 1, Com[i].time);
		m_List.SetItemText(i, 2, Com[i].num);
		m_List.SetItemText(i, 3, Com[i].shelf);
	}
}

void SystemDlg::OnBnClickedSearch()
{
	SearchMethodDlg dlg;
	dlg.DoModal();
}

CQueryDlg qd;
void SystemDlg::OnBnClickedRemotequery()
{
	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return;
	}
	if (!qd.m_hWnd)
	{
		qd.Create(IDD_REMOTEQUERY_DIALOG, this);
	}
	qd.ShowWindow(SW_SHOW);
}

void SystemDlg::OnBnClickedGlbtoexcel()
{
	int item;
	item = MessageBox(L"导出完毕后,是否自动打开导出的图表?", L"自动启动Excel", MB_ICONQUESTION | MB_YESNO | MB_DEFBUTTON2);
	MessageBox(L"你可以在你选择的目录下新建受支持格式的文档;或者你也可以从存在的文档中选择一个,但是这可能会导致原有的数据因被覆盖而丢失.", L"当心数据丢失", MB_ICONINFORMATION);
	CString Filters = L"Excel 工作簿(*.xlsx)|*.xlsx|Excel 97-2003工作簿(*.xls)|*.xls|文本文档(含有制表符)(*.txt)|*.txt||";
	CFileDialog dlg(TRUE, NULL, NULL, OFN_CREATEPROMPT | OFN_HIDEREADONLY, Filters);
	dlg.m_ofn.lpstrTitle = L"打开Excel文档";
	if (dlg.DoModal() == IDOK)
	{
		std::vector<std::string> nm;
		std::vector<std::string> qt;
		std::vector<std::string> dt;
		std::vector<std::string> sf;
		USES_CONVERSION;
		transform(true);
		for (size_t i = 0; i < Com.size(); i++)
		{
			nm.push_back(W2A(Com[i].name));
			qt.push_back(W2A(Com[i].num));
			dt.push_back(W2A(Com[i].time));
			sf.push_back(W2A(Com[i].shelf));
		}
		setInfo(nm, qt, dt, sf);
		global2Excel(dlg.GetPathName());
	}
}

ULONG WINAPI GetRoute(LPVOID p) {
	ReceivePoints(GetRoute(SendPoints()));
	return 0;
}

void SystemDlg::OnBnClickedSysdlgSeldst()
{
	CreateMapWindow(SW_SHOW);
	CreateThread(NULL, 0, GetRoute, NULL, NULL, NULL);//创建一个新线程
}
