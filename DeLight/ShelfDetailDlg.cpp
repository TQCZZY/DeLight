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
#include "Excel.hpp"
#include "ExcelSettingsDlg.h"

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
	DDX_Control(pDX, IDC_SFDTLDLG_LIST, m_list);
}

BEGIN_MESSAGE_MAP(ShelfDetailDlg, CDialogEx)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_SFDTLDLG_SELALL, &ShelfDetailDlg::OnClickedSelall)
	ON_BN_CLICKED(IDC_SFDTLDLG_REVERSESEL, &ShelfDetailDlg::OnClickedReversesel)
	ON_BN_CLICKED(IDC_SFDTLDLG_IN, &ShelfDetailDlg::OnClickedInbound)
	ON_BN_CLICKED(IDC_SFDTLDLG_OUT, &ShelfDetailDlg::OnClickedOutbound)
	ON_BN_CLICKED(IDC_SFDTLDLG_EDIT, &ShelfDetailDlg::OnClickedEdit)
	ON_BN_CLICKED(IDC_SFDTLDLG_SORT_NM, &ShelfDetailDlg::OnClickedSortnm)
	ON_BN_CLICKED(IDC_SFDTLDLG_SORT_DT, &ShelfDetailDlg::OnClickedSortdt)
	ON_BN_CLICKED(IDC_SFDTLDLG_SORT_QT, &ShelfDetailDlg::OnClickedSortqt)
	ON_BN_CLICKED(IDC_SFDTLDLG_EXPORT, &ShelfDetailDlg::OnClickedSfdtldlgExport)
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
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT/*整行选中*/ | LVS_EX_CHECKBOXES/*复选框*/);//扩展样式

	m_list.InsertColumn(0, _T("商品名称"), 0, 200/*宽度*/);
	m_list.InsertColumn(1, _T("进货时间"), 0, 200);
	m_list.InsertColumn(2, _T("商品库存"), 0, 200);

	transform(true);
	indexInCom.clear();
	for (int i = 0; i < Com.size(); i++)
	{
		if (Com[i].shelfNo == shelfNumber)
		{
			m_list.InsertItem(i, L"");
			m_list.SetItemText(i, 0, Com[i].name);
			m_list.SetItemText(i, 1, Com[i].time);
			m_list.SetItemText(i, 2, Com[i].num);
			m_list.SetItemText(i, 3, Com[i].shelf);
			indexInCom.push_back(i);
		}
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void ShelfDetailDlg::OnClickedSelall()//全选
{
	// TODO: 在此添加控件通知处理程序代码
	for (int i = 0; i < m_list.GetItemCount/*获取条目的数量*/(); i++)
	{
		m_list.SetCheck/*设置选中状态*/(i, TRUE);
	}
}

void ShelfDetailDlg::OnClickedReversesel()//反选
{
	// TODO: 在此添加控件通知处理程序代码
	for (int i = 0; i < m_list.GetItemCount/*获取条目的数量*/(); i++)
	{
		m_list.SetCheck/*设置选中状态*/(i, !m_list.GetCheck(i));
	}
}

void ShelfDetailDlg::OnClickedInbound()//入库
{
	CString csName = L"";
	CString csNum = L"";
	CString csDate = L"";
	USES_CONVERSION;
ShelfDetailDlgRetryIn:
	GoodsMngmntDlg dlg;
	if (IDCANCEL == dlg.DoModal(csName, csNum, csDate, A2W(std::to_string(shelfNumber).c_str()), true) ||//点击增加，弹出子对话框
	dlg.sType.IsEmpty() || dlg.sDate.IsEmpty() || dlg.sNumber.IsEmpty())
		return;
	csName = dlg.sType;
	csNum = dlg.sNumber;
	csDate = dlg.sDate;
	Time t;
	t << W2A(dlg.sDate);
	if (t == Time{ 0, 0, 0 })
	{
		MessageBox(L"日期格式错误，请更正\n如下是一些支持的日期示例:\n2022 1 1\n2022,1,1\n2022.1.1\n2022/1/1\n2022-1-1\n20220101", L"更正日期格式", MB_ICONERROR);
		goto ShelfDetailDlgRetryIn;
	}
	int nCount = m_list.GetItemCount();
	m_list.InsertItem(nCount, L"");
	m_list.SetItemText(nCount, 0, dlg.sType);
	m_list.SetItemText(nCount, 1, dlg.sDate);
	m_list.SetItemText(nCount, 2, dlg.sNumber);
	Good_Info new_good;
	new_good.name = W2A(dlg.sType);
	new_good.time = t;

	new_good.amount = _ttoi(dlg.sNumber);
	new_good.location = shelfNumber;
	Insert(new_good);
	transform(true);
}

void ShelfDetailDlg::OnClickedOutbound()//出库
{
	size_t realIdx = 0;
	for (int i = 0; i < m_list.GetItemCount/*获取条目的数量*/(); ++i, ++realIdx)
	{
		if (m_list.GetCheck(i))
		{
			Delete(Com[realIdx].code);
			m_list.DeleteItem(i);
			i--;//若不i--则不能多项同时删除，因为当删除0栏后，1栏会为0栏，就删不掉了
		}
	}
	transform(true);
}

void ShelfDetailDlg::OnClickedEdit()//修改
{
	size_t realIdx = 0;
	for (int i = 0; i < m_list.GetItemCount/*获取条目的数量*/(); ++i, ++realIdx)
	{
		if (m_list.GetCheck(i))
		{
			CString csName = Com[indexInCom[i]].name;
			CString csNum = Com[indexInCom[i]].num;
			CString csDate = Com[indexInCom[i]].time;
		ShelfDetailDlgRetryMd:
			GoodsMngmntDlg dlg;
			if (IDCANCEL == dlg.DoModal(csName, csNum, csDate, Com[indexInCom[i]].shelf, true) ||//弹窗
				dlg.sType.IsEmpty() || dlg.sDate.IsEmpty() || dlg.sNumber.IsEmpty())
				return;
			csName = dlg.sType;
			csNum = dlg.sNumber;
			csDate = dlg.sDate;
			USES_CONVERSION;
			Time t;
			t << W2A(dlg.sDate);
			if (t == Time{ 0, 0, 0 })
			{
				MessageBox(L"日期格式错误，请更正\n如下是一些支持的日期示例:\n2022 1 1\n2022,1,1\n2022.1.1\n2022/1/1\n2022-1-1\n20220101", L"更正日期格式", MB_ICONERROR);
				goto ShelfDetailDlgRetryMd;
			}
			m_list.SetItemText(i, 0, dlg.sType);
			m_list.SetItemText(i, 1, dlg.sDate);
			m_list.SetItemText(i, 2, dlg.sNumber);
			Delete(Com[indexInCom[i]].code);
			Good_Info new_good;
			new_good.name = W2A(dlg.sType);
			new_good.time = t;

			new_good.amount = _ttoi(dlg.sNumber);
			new_good.location = _ttoi(dlg.sShelf);
			Insert(new_good, indexInCom[i]);
		}
	}
	transform(true);
}

void ShelfDetailDlg::OnClickedSortnm()//排序1
{
	for (int i = 0; i < m_list.GetItemCount/*获取条目的数量*/(); i++)
	{
		m_list.DeleteItem(i);
		i--;//若不i--则不能多项同时删除，因为当删除0栏后，1栏会为0栏，就删不掉了
	}

	Sort(1);
	transform(true);
	for (int i = 0; i < Com.size(); i++)
	{
		if (Com[i].shelfNo == shelfNumber)
		{
			m_list.InsertItem(i, Com[i].name);//第一列数据
			m_list.SetItemText(i, 1, Com[i].time);
			m_list.SetItemText(i, 2, Com[i].num);
			m_list.SetItemText(i, 3, Com[i].shelf);
		}
	}
}

void ShelfDetailDlg::OnClickedSortdt()//排序2
{
	for (int i = 0; i < m_list.GetItemCount/*获取条目的数量*/(); i++)
	{
		m_list.DeleteItem(i);
		i--;//若不i--则不能多项同时删除，因为当删除0栏后，1栏会为0栏，就删不掉了
	}

	Sort(4);
	transform(true);
	for (int i = 0; i < Com.size(); i++)
	{
		if (Com[i].shelfNo == shelfNumber)
		{
			m_list.InsertItem(i, Com[i].name);//第一列数据
			m_list.SetItemText(i, 1, Com[i].time);
			m_list.SetItemText(i, 2, Com[i].num);
			m_list.SetItemText(i, 3, Com[i].shelf);
		}
	}
}

void ShelfDetailDlg::OnClickedSortqt()//排序3
{
	for (int i = 0; i < m_list.GetItemCount/*获取条目的数量*/(); i++)
	{
		m_list.DeleteItem(i);
		i--;//若不i--则不能多项同时删除，因为当删除0栏后，1栏会为0栏，就删不掉了
	}

	Sort(2);
	transform(true);
	for (int i = 0; i < Com.size(); i++)
	{
		if (Com[i].shelfNo == shelfNumber)
		{
			m_list.InsertItem(i, Com[i].name);//第一列数据
			m_list.SetItemText(i, 1, Com[i].time);
			m_list.SetItemText(i, 2, Com[i].num);
			m_list.SetItemText(i, 3, Com[i].shelf);
		}
	}
}

INT_PTR ShelfDetailDlg::DoModal(int shelfNo)
{
	shelfNumber = shelfNo;

	return CDialogEx::DoModal();
}

void ShelfDetailDlg::OnClickedSfdtldlgExport()
{
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
		for (size_t i = 0; i < Com.size(); ++i)
		{
			if (Com[i].shelfNo == shelfNumber)
			{
				nm.push_back(W2A(Com[i].name));
				dt.push_back(W2A(Com[i].time));
				qt.push_back(W2A(Com[i].num));
				sf.push_back(W2A(Com[i].shelf));
				break;
			}
		}
		setInfo(nm, qt, dt, sf);
		ExcelSettingsDlg exstDlg;
		exstDlg.DoModal();
		shelf2Excel(dlg.GetPathName(), IDNO == MessageBox(L"导出完毕后,是否自动打开导出的图表?", L"自动启动Excel", MB_ICONQUESTION | MB_YESNO | MB_DEFBUTTON2), exstDlg.readOnly, exstDlg.m_psw, exstDlg.m_wrpsw);
	}
}
