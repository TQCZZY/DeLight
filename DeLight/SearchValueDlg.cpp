// SearchValueDlg.cpp: 实现文件
//

#include "pch.h"
#include "DeLight.h"
#include "afxdialogex.h"
#include <string>
#include <vector>
#include "List.h"
#include "SearchValueDlg.h"
#include "SearchResultDlg.h"

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
	GetDlgItemText(IDC_SVDLG_VAL, keyword);
	USES_CONVERSION;
	Search_Info si;
	si.type = searchType;
	switch (searchType) {
	case 1:
	{
		si.name = W2A(keyword);
	}
	break;
	case 2:
	{
		si.amount = _ttoi(keyword);
	}
	break;
	case 3:
	{
		si.location = _ttoi(keyword);
	}
	break;
	case 4:
	{
		Time t = { 0,0,0 };
		t << W2A(keyword);
		if (t == Time{ 0, 0, 0 })
		{
			MessageBox(L"日期格式错误，请更正\n如下是一些支持的日期示例:\n2022 1 1\n2022,1,1\n2022.1.1\n2022/1/1\n2022-1-1\n20220101", L"更正日期格式", MB_ICONERROR);
			return;
		}
		si.time = t;
	}	
	break;
	}
	EndDialog(0);
	SearchResultDlg dlg;
	dlg.DoModal(searchType, Search(si));
}

INT_PTR SearchValueDlg::DoModal(int st)
{
	searchType = st;
	return CDialogEx::DoModal();
}
