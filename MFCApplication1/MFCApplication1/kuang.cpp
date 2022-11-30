// kuang.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "kuang.h"
#include "Guocheng.cpp"
#include "List.cpp"

// kuang 对话框

IMPLEMENT_DYNAMIC(kuang, CDialogEx)

kuang::kuang(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG9, pParent)
{

}

kuang::~kuang()
{
}

void kuang::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, SOU);
}


BEGIN_MESSAGE_MAP(kuang, CDialogEx)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &kuang::OnLvnItemchangedList1)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON1, &kuang::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON7, &kuang::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON3, &kuang::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON2, &kuang::OnBnClickedButton2)
END_MESSAGE_MAP()


// kuang 消息处理程序


void kuang::OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void kuang::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnClose();
}


BOOL kuang::OnInitDialog()
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
			if(Com[i].bian==b[j])
			{
				S_List.InsertItem(i, Com[i].itemName);//第一列数据
				S_List.SetItemText(i, 1, Com[i].time);
				S_List.SetItemText(i, 2, Com[i].snum);
				S_List.SetItemText(i, 3, Com[i].thing);
				break;
			}
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void kuang::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	for (int i = 0; i < S_List.GetItemCount/*获取条目的数量*/(); i++)
	{
		S_List.SetCheck/*设置选中状态*/(i, TRUE);
	}
}


void kuang::OnBnClickedButton7()
{
	// TODO: 在此添加控件通知处理程序代码
	for (int i = 0; i < S_List.GetItemCount/*获取条目的数量*/(); i++)
	{
		S_List.SetCheck/*设置选中状态*/(i, !S_List.GetCheck(i));
	}
}



void kuang::OnBnClickedButton2()
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
