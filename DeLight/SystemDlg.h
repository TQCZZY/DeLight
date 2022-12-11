#pragma once
#include "QueryDlg.h"

// SystemDlg 对话框

class SystemDlg : public CDialogEx
{
	DECLARE_DYNAMIC(SystemDlg)

public:
	SystemDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~SystemDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SYSTEMDLG };
#endif

protected:
	HICON m_hIcon;
	CQueryDlg qd;

	// 生成的消息映射函数
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	// 这是显示商品数据的列表
	CListCtrl m_List;
	HACCEL m_hAcc;
	CMenu m_Menubar;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnQuit();
	afx_msg void OnInbound();
	afx_msg void OnOutbound();
	afx_msg void OnModify();
	afx_msg void OnSelall();
	afx_msg void OnRevsel();
	afx_msg void OnSortbyname();
	afx_msg void OnSortbytime();
	afx_msg void OnSortbyquantity();
	afx_msg void OnSortbyshelf();
	afx_msg void OnSearchbyname();
	afx_msg void OnSearchbytime();
	afx_msg void OnSearchbyquantity();
	afx_msg void OnSearchbyshelf();
	afx_msg void OnExport();
	afx_msg void OnDist();
	afx_msg void OnSlfdtl();
	afx_msg void OnRquery();
	afx_msg void OnLoad();
	afx_msg void OnSave();
};
