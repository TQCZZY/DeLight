// PropertyDlg.cpp: 实现文件
//

#include "pch.h"
#include "DeLight.h"
#include "afxdialogex.h"
#include "GoodsMngmntDlg.h"


// GoodsMngmntDlg 对话框

IMPLEMENT_DYNAMIC(GoodsMngmntDlg, CDialogEx)

GoodsMngmntDlg::GoodsMngmntDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GOODS_MNG, pParent)
	, sType(_T(""))
	, sNumber(_T(""))
	, sDate(_T(""))
	, sShelf(_T(""))
{

}

GoodsMngmntDlg::~GoodsMngmntDlg()
{
}

void GoodsMngmntDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GDMDLG_SLF, m_editShelf);
	DDX_Text(pDX, IDC_GDMDLG_DATE, sDate);
	DDX_Text(pDX, IDC_GDMDLG_SLF, sShelf);
	DDX_Text(pDX, IDC_GDMDLG_TYPE, sType);
	DDX_Text(pDX, IDC_GDMDLG_NUM, sNumber);
}


BEGIN_MESSAGE_MAP(GoodsMngmntDlg, CDialogEx)
	ON_BN_CLICKED(IDC_GDMDLG_OK, &GoodsMngmntDlg::OnBnClickedButtonOk)
	ON_BN_CLICKED(IDC_GDMDLG_NO, &GoodsMngmntDlg::OnBnClickedButtonNo)
	ON_EN_CHANGE(IDC_GDMDLG_DATE, &GoodsMngmntDlg::OnChangeGdmdlgDate)
END_MESSAGE_MAP()


// PropertyDlg 消息处理程序


void GoodsMngmntDlg::OnBnClickedButtonOk()//增加中的确定
{
	GetDlgItemText(IDC_GDMDLG_TYPE,sType);
	GetDlgItemText(IDC_GDMDLG_DATE, sDate);
	GetDlgItemText(IDC_GDMDLG_NUM, sNumber);
	GetDlgItemText(IDC_GDMDLG_SLF, sShelf);//输入值
	CDialogEx::OnOK();//关闭窗口
}


void GoodsMngmntDlg::OnBnClickedButtonNo()
{
	CDialogEx::OnCancel();
}


INT_PTR GoodsMngmntDlg::DoModal(CString name, CString count, CString date, CString shelf, bool specShelf)
{
	sType = name;
	sDate = date;
	sNumber = count;
	sShelf = shelf;
	enableShelf = !specShelf;
	return CDialogEx::DoModal();
}


BOOL GoodsMngmntDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_editShelf.EnableWindow(enableShelf);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

size_t NumericLength(CString str, size_t startAt = 0)
{
	size_t i;
	for (i = startAt; i < str.GetLength(); ++i)
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
		{
			break;
		}
	}
	return i - startAt;
}
void GoodsMngmntDlg::OnChangeGdmdlgDate()
{
	CString newValue;
	GetDlgItemText(IDC_GDMDLG_DATE, newValue);
	if (sDate.GetLength() < newValue.GetLength())
	{
		return;
	}
	size_t length = NumericLength(sDate, 0);
	if (length == 4)
	{

	}
}
