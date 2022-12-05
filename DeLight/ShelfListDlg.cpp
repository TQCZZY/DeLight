// ListDlg.cpp: 实现文件
//

#include "pch.h"
#include "DeLight.h"
#include "vector"
#include "afxdialogex.h"
#include "ShelfListDlg.h"
#include "ShelfDetailDlg.h"

// ShelfListDlg 对话框

IMPLEMENT_DYNAMIC(ShelfListDlg, CDialogEx)

ShelfListDlg::ShelfListDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SLF_LIST, pParent)
{
	shelfNo = 0;
}

ShelfListDlg::~ShelfListDlg()
{
}

void ShelfListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SFLSTDLG_LIST, T_List);
}


BEGIN_MESSAGE_MAP(ShelfListDlg, CDialogEx)
	ON_NOTIFY(NM_DBLCLK, IDC_SFLSTDLG_LIST, &ShelfListDlg::OnDblclkSlfdtldlgList)
END_MESSAGE_MAP()


// ShelfListDlg 消息处理程序

BOOL ShelfListDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	T_List.InsertColumn(0, _T("货架编号"), 0, 200/*宽度*/);

	CString sthing;
	for (int i = 1; i < 4; i++)
	{
		sthing.Format(_T("%d号货架"), i);
		T_List.InsertItem(i, sthing);
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void ShelfListDlg::OnDblclkSlfdtldlgList(NMHDR* pNMHDR, LRESULT* pResult)
{
	shelfNo = ((NM_LISTVIEW*)pNMHDR)->iItem + 1;
	ShelfDetailDlg dlg;
	dlg.DoModal(shelfNo);
	*pResult = 0;
}
