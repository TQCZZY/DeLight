// DataCenterDlg.cpp : implementation file
//

#include "pch.h"
#include "DataCenter.h"
#include "DataCenterDlg.h"
#include <string>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About


class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDataCenterDlg dialog

CDataCenterDlg::CDataCenterDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDataCenterDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDataCenterDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDataCenterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDataCenterDlg)
	DDX_Control(pDX, IDC_LIST, m_show);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDataCenterDlg, CDialog)
	//{{AFX_MSG_MAP(CDataCenterDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SERVER, OnServer)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDCANCEL, &CDataCenterDlg::OnBnClickedCancel)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDataCenterDlg message handlers

BOOL CDataCenterDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDataCenterDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDataCenterDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDataCenterDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CDataCenterDlg::OnServer() 
{
	char HostName[128];
	if (gethostname(HostName, 128) != 0)
		return;
	struct hostent* pHost;
	pHost = gethostbyname(HostName);
	LPCSTR lpIP = inet_ntoa(*(struct in_addr*)pHost->h_addr_list[0]);
	CString svrMsg = L"Data Center ";
	svrMsg += lpIP;
	svrMsg += ": online";
	m_show.InsertString(-1, svrMsg);
	CreateThread(NULL,0,LinsenThread,this,NULL,NULL);//创建一个新线程
}

struct SocMsg
{
	std::string ip;
	std::string name;
	std::string header;
	std::string respTo;
	std::string data;
};
SocMsg Msg;
SocMsg* pMsg;

CStringArray m_chater;

/*-------------------------------------------------------------------
线程函数名：LinsenThread
属性：全局函数
功能：接收对方聊天者发来的聊天信息，转发给所有聊天者，并显示到列表框中
参数p--指向界面对话框的指针
---------------------------------------------------------------------*/

ULONG WINAPI LinsenThread(LPVOID p){
	//获取指向界面对话框的指针，通过该指针可以调用界面上的控件
	CDataCenterDlg *pDlg=(CDataCenterDlg *)p;

	CSocket m_ReceiveSocket;//构造一个套接字对象

	CString respTo, header, data, name, chatIP;

	m_ReceiveSocket.Create(8888,SOCK_DGRAM);	
	pMsg = &Msg;

	while(1){
		m_ReceiveSocket.Receive(pMsg, sizeof(Msg));
		
		data = pMsg->data.c_str();
		name = pMsg->name.c_str();
		header = pMsg->header.c_str();
		respTo = pMsg->respTo.c_str();
		if(data.IsEmpty() || name.IsEmpty())
			continue;
		if (header == "require") {
			data = name + " " + header + "s: " + data;
		}
		else if (header == "respond") {
			data = name + " " + header + "s to " + respTo + ": " + data;
		}
		else {
			data = header + " from " + name + ": " + data;
		}
		pDlg->m_show.InsertString(-1,data);

		//判断发来信息的聊天者IP是否已存入聊天者列表
		chatIP = pMsg->ip.c_str();
		CString listIP;
		bool flag = 0;
		int len = m_chater.GetSize();
		if (header == "event")
		{
			//判断列表中是否已存在该客户
			int i = 0;
			for (i = 0; i < len; i++) {
				if (chatIP == m_chater.GetAt(i)) {
					flag = 1;//列表中已存在该IP，则设为1
					break;
				}
			}
			if (pMsg->data == "online")
			{
				if (!flag)
					m_chater.Add(chatIP);//如果不存在则添加到列表中
			}
			else if (pMsg->data == "offline")
			{
				m_chater.RemoveAt(i);
			}
		}

		//把信息发送给列表中的每个客户
		len=m_chater.GetSize();
		for(int k=0; k<len; k++){                  
			listIP = m_chater.GetAt(k);			
			m_ReceiveSocket.SendTo( pMsg, sizeof(Msg),6666,listIP);//转发数据给其他聊天者
		}
	}
	m_ReceiveSocket.Close();
	return 0;
}

void CDataCenterDlg::OnBnClickedCancel()
{
	CSocket m_SendSocket;//构造一个套接字对象
	m_SendSocket.Create(1234, SOCK_DGRAM);

	pMsg->data = "close";
	pMsg->name = "Data Center";
	pMsg->header = "event";
	pMsg->respTo = "";
	//把信息发送给列表中的每个客户
	CString listIP;
	int len = m_chater.GetSize();
	for (int k = 0; k < len; k++) {
		listIP = m_chater.GetAt(k);
		m_SendSocket.SendTo(pMsg, sizeof(Msg), 6666, listIP);//转发数据给其他聊天者
	}
	m_SendSocket.Close();
	CDialog::OnCancel();
}
