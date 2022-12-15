// SearchResultDlg.cpp: 实现文件
//

#include "pch.h"
#include "DeLight.h"
#include "afxdialogex.h"
#include <string>
#include <vector>
#include "List.h"
#include "SearchResultDlg.h"
#include "ExcelSettingsDlg.h"
#include "Excel.hpp"

// SearchResultDlg 对话框

IMPLEMENT_DYNAMIC(SearchResultDlg, CDialogEx)

SearchResultDlg::SearchResultDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SRC_RES, pParent)
	, isOutbound(false)
{

}

SearchResultDlg::~SearchResultDlg()
{
}

void SearchResultDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SRDLG_LIST, S_List);
	DDX_Control(pDX, IDC_SRDLG_EXPORT, m_btnExport);
}

BEGIN_MESSAGE_MAP(SearchResultDlg, CDialogEx)
	ON_BN_CLICKED(IDC_SRDLG_SELALL, &SearchResultDlg::OnClickedSelall)
	ON_BN_CLICKED(IDC_SRDLG_REVERSESEL, &SearchResultDlg::OnClickedReversesel)
	ON_BN_CLICKED(IDC_SRDLG_RMV, &SearchResultDlg::OnClickedRmv)
	ON_BN_CLICKED(IDC_SRDLG_EXPORT, &SearchResultDlg::OnClickedSrdlgExport)
	ON_BN_CLICKED(IDC_SRDLG_OUT, &SearchResultDlg::OnClickedSrdlgOut)
END_MESSAGE_MAP()

// SearchResultDlg 消息处理程序

BOOL SearchResultDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	S_List.SetExtendedStyle(LVS_EX_FULLROWSELECT/*整行选中*/ | LVS_EX_CHECKBOXES/*复选框*/);//扩展样式

	S_List.InsertColumn(0, _T("商品名称"), 0, 200/*宽度*/);
	S_List.InsertColumn(1, _T("进货时间"), 0, 200);
	S_List.InsertColumn(2, _T("商品库存"), 0, 200);
	S_List.InsertColumn(3, _T("货架编号"), 0, 200);

	for (int i = 0; i < searchResult.size(); i++)
	{
		for (int j = 0; j < Com.size(); j++)
		{
			if (Com[i].code == searchResult[j])
			{
				S_List.InsertItem(i, Com[i].name);//第一列数据
				S_List.SetItemText(i, 1, Com[i].time);
				S_List.SetItemText(i, 2, Com[i].num);
				S_List.SetItemText(i, 3, Com[i].shelf);
				break;
			}
		}
	}
	if (searchType == 2)
	{
		m_btnExport.ShowWindow(SW_HIDE);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void SearchResultDlg::OnClickedSelall()
{
	for (int i = 0; i < S_List.GetItemCount/*获取条目的数量*/(); i++)
	{
		S_List.SetCheck/*设置选中状态*/(i, TRUE);
	}
}


void SearchResultDlg::OnClickedReversesel()
{
	for (int i = 0; i < S_List.GetItemCount/*获取条目的数量*/(); i++)
	{
		S_List.SetCheck/*设置选中状态*/(i, !S_List.GetCheck(i));
	}
}

void SearchResultDlg::OnClickedRmv()
{
	if (!isOutbound)
	{
		MessageBox(L"该操作仅将勾选的条目从搜索结果中移除，相应货物并不会出库。", L"注意", MB_ICONINFORMATION);
	}
	size_t delCount = 0;
	for (int i = 0; i < S_List.GetItemCount/*获取条目的数量*/(); ++i)
	{
		if (S_List.GetCheck(i))
		{
			if (isOutbound)
			{
				Delete(searchResult[i]);
			}
			searchResult[i] = 0;
			++delCount;
		}
	}
	for (int i = 0; i < searchResult.size(); ++i)
	{
		if (searchResult[i] == 0)
		{
			for (int j = i + 1; j < searchResult.size(); ++j)
			{
				if (searchResult[j] != 0)
				{
					searchResult[i] = searchResult[j];
					searchResult[j] = 0;
					break;
				}
			}
			if (searchResult[i] == 0)
			{
				break;
			}
		}
	}
	searchResult.resize(searchResult.size() - delCount);
	for (int i = 0; i < S_List.GetItemCount/*获取条目的数量*/(); ++i)
	{
		if (S_List.GetCheck(i))
		{
			S_List.DeleteItem(i);
			i--;//若不i--则不能多项同时删除，因为当删除0栏后，1栏会为0栏，就删不掉了
		}
	}
}

void SearchResultDlg::OnClickedSrdlgOut()
{
	isOutbound = true;
	OnClickedRmv();
	isOutbound = false;
}

void SearchResultDlg::OnClickedSrdlgExport()
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
		for (size_t i = 0; i < Com.size(); i++)
		{
			for (int j = 0; j < searchResult.size(); j++)
			{
				if (Com[i].code == searchResult[j])
				{
					nm.push_back(W2A(Com[i].name));
					dt.push_back(W2A(Com[i].time));
					qt.push_back(W2A(Com[i].num));
					sf.push_back(W2A(Com[i].shelf));
					break;
				}
			}
		}
		setInfo(nm, qt, dt, sf);
		ExcelSettingsDlg exstDlg;
		exstDlg.DoModal();
		switch (searchType)
		{
		case 1:
			singleGoods2Excel(dlg.GetPathName(), IDNO == MessageBox(L"导出完毕后,是否自动打开导出的图表?", L"自动启动Excel", MB_ICONQUESTION | MB_YESNO | MB_DEFBUTTON2), exstDlg.readOnly, exstDlg.m_psw, exstDlg.m_wrpsw);
			break;
		case 3:
			shelf2Excel(dlg.GetPathName(), IDNO == MessageBox(L"导出完毕后,是否自动打开导出的图表?", L"自动启动Excel", MB_ICONQUESTION | MB_YESNO | MB_DEFBUTTON2), exstDlg.readOnly, exstDlg.m_psw, exstDlg.m_wrpsw);
			break;
		case 4:
			specDate2Excel(dlg.GetPathName(), IDNO == MessageBox(L"导出完毕后,是否自动打开导出的图表?", L"自动启动Excel", MB_ICONQUESTION | MB_YESNO | MB_DEFBUTTON2), exstDlg.readOnly, exstDlg.m_psw, exstDlg.m_wrpsw);
			break;
		default:
			break;
		}
	}
}

INT_PTR SearchResultDlg::DoModal(int st, std::vector<int> sr)
{
	searchType = st;
	searchResult = sr;
	return CDialogEx::DoModal();
}
