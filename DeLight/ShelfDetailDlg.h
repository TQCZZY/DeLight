#pragma once
#include "afxdialogex.h"


// Huojia1 对话框

class ShelfDetailDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ShelfDetailDlg)

public:
	ShelfDetailDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~ShelfDetailDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SLF_DTL };
#endif

protected:
	int shelfNumber;
	std::vector<int> indexInCom;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	CListCtrl m_list;
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
	virtual BOOL OnInitDialog();
	afx_msg void OnClickedSelall();
	afx_msg void OnClickedReversesel();
	afx_msg void OnClickedInbound();
	afx_msg void OnClickedOutbound();
	afx_msg void OnClickedEdit();
	afx_msg void OnClickedSortnm();
	afx_msg void OnClickedSortdt();
	afx_msg void OnClickedSortqt();
	virtual INT_PTR DoModal(int shelfNo);
	afx_msg void OnClickedSfdtldlgExport();
};
