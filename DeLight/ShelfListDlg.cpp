// ListDlg.cpp: 实现文件
//

#include "pch.h"
#include "DeLight.h"
#include "vector"
#include "afxdialogex.h"
#include "List.h"
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

	bool isDuplicate;
	csShelf.clear();
	for (int i = 0; i < Com.size(); ++i)
	{
		isDuplicate = false;
		for (int j = 0; j < csShelf.size(); ++j)
		{
			if (Com[i].shelf == csShelf[j])
			{
				isDuplicate = true;
				break;
			}
		}
		if (!isDuplicate)
		{
			csShelf.push_back(Com[i].shelf);
		}
	}
	for (int i = 1; i <= csShelf.size(); ++i)
	{
		T_List.InsertItem(i, csShelf[i - 1] + "号货架");
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void ShelfListDlg::OnDblclkSlfdtldlgList(NMHDR* pNMHDR, LRESULT* pResult)
{
	shelfNo = _ttoi(csShelf[((NM_LISTVIEW*)pNMHDR)->iItem]);
	ShelfDetailDlg dlg;
	dlg.DoModal(shelfNo);
	*pResult = 0;
}
