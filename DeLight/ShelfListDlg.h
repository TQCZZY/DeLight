#pragma once
#include "afxdialogex.h"

// ShelfListDlg 对话框

class ShelfListDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ShelfListDlg)

public:
	ShelfListDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~ShelfListDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SLF_LIST };
#endif

protected:
	int shelfNo;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 这是排列货架序号的列表
	CListCtrl T_List;
	virtual BOOL OnInitDialog();
	afx_msg void OnDblclkSlfdtldlgList(NMHDR* pNMHDR, LRESULT* pResult);
};
