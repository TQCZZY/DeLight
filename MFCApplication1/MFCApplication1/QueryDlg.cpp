// QueryDlg.cpp : implementation file
//

#include "pch.h"
#include "Query.h"
#include "QueryDlg.h"
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
// CQueryDlg dialog

CQueryDlg::CQueryDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CQueryDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CQueryDlg)
	m_toIP = _T("");
	m_message = _T("");
	m_name = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CQueryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CQueryDlg)
	DDX_Control(pDX, IDC_ENTER, m_enter);
	DDX_Control(pDX, IDC_LIST, m_show);
	DDX_Text(pDX, IDC_IP, m_toIP);
	DDX_Text(pDX, IDC_MESSAGE, m_message);
	DDX_Text(pDX, IDC_NAME, m_name);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CQueryDlg, CDialog)
	//{{AFX_MSG_MAP(CQueryDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_ENTER, OnEnter)
	ON_BN_CLICKED(IDC_SEND, OnSend)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CQueryDlg::OnBnClickedOk)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CQueryDlg message handlers

BOOL CQueryDlg::OnInitDialog()
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

void CQueryDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CQueryDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM)dc.GetSafeHdc(), 0);

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
HCURSOR CQueryDlg::OnQueryDragIcon()
{
	return (HCURSOR)m_hIcon;
}

void CQueryDlg::OnEnter()
{
	UpdateData(true);
	char HostName[128];
	if (gethostname(HostName, 128) != 0)
		return;
	struct hostent* pHost;
	pHost = gethostbyname(HostName);
	LPCSTR lpIP = inet_ntoa(*(struct in_addr*)pHost->h_addr_list[0]);
	m_localIP = lpIP;

	m_enter.EnableWindow(false);
	CreateThread(NULL, 0, LinsenThread, this, NULL, NULL);//创建一个新线程

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

/*-----------------------------------------------
线程函数名：LinsenThread
属性：全局函数
功能：接收服务器发来的信息，并显示到列表框中
参数p--指向界面对话框的指针
-------------------------------------------------*/
ULONG WINAPI LinsenThread(LPVOID p) {
	//发送数据对象的定义

	//获取指向界面对话框的指针，通过该指针可以调用界面上的控件
	CQueryDlg* pDlg = (CQueryDlg*)p;
	CSocket m_ReceiveSocket;//构造一个套接字对象

	CString header, respTo, data, name;

	//接收数据
	m_ReceiveSocket.Create(6666, SOCK_DGRAM);
	pMsg = &Msg;

	//发送数据的初始化
	USES_CONVERSION;
	Msg.ip = W2A(pDlg->m_localIP);
	Msg.name = W2A(pDlg->m_name);
	Msg.header = "event";
	Msg.data = "online";
	m_ReceiveSocket.SendTo(pMsg, sizeof(Msg), 8888, pDlg->m_toIP);//发送登录包
	Msg.ip = "";
	Msg.name = "";
	Msg.header = "";
	Msg.data = "";
	Msg.respTo = "";

	while (1) {
		int n = m_ReceiveSocket.Receive(pMsg, sizeof(Msg));
		if (n == 0)
			continue;

		data = pMsg->data.c_str();
		name = pMsg->name.c_str();
		header = pMsg->header.c_str();
		respTo = pMsg->respTo.c_str();
		if (data.IsEmpty() || name.IsEmpty() || (header == "event" && (name != "Data Center" || name != pDlg->m_name)) || (header == "respond" && name != pDlg->m_name && respTo != pDlg->m_name))
			continue;
		if (header == "event")
		{
			pDlg->m_show.InsertString(-1, header + " from " + name + ": " + data);
			if (name == "Data Center" && data == "close")
			{
				pDlg->m_show.InsertString(-1, header + " from " + pDlg->m_name + ": offline");
				AfxMessageBox(L"数据中心已关闭。");
				pDlg->m_enter.EnableWindow(true);
				pDlg->m_toIP = "";
				pDlg->UpdateData(false);
				return 0;
			}
		} else {
			pDlg->m_show.InsertString(-1, name + " " + header + "s: " + data);
			if (header == "require")
			{
				//search
				if (true)//search success
				{
					CSocket m_SendSocket;//构造一个套接字对象

					//发送数据的初始化
					USES_CONVERSION;
					Msg.ip = W2A(pDlg->m_localIP);
					Msg.name = W2A(pDlg->m_name);
					Msg.header = "respond";
					Msg.data = W2A(data);
					Msg.respTo = W2A(name);

					//数据发送
					m_SendSocket.Create(1234, SOCK_DGRAM);//创建一个套接字句柄（UDP）
					m_SendSocket.SendTo(pMsg, sizeof(Msg), 8888, pDlg->m_toIP);//发送数据给本地计算机
					m_SendSocket.Close();
					Msg.ip = "";
					Msg.name = "";
					Msg.header = "";
					Msg.data = "";
					Msg.respTo = "";
				}
			}
		}
	}
	m_ReceiveSocket.Close();
	return 0;
}

void CQueryDlg::OnSend()
{
	UpdateData(true);

	CSocket m_SendSocket;//构造一个套接字对象

	//发送数据的初始化
	USES_CONVERSION;
	Msg.ip = W2A(m_localIP);
	Msg.name = W2A(m_name);
	Msg.header = "require";
	Msg.data = W2A(m_message);
	Msg.respTo = "";
	pMsg = &Msg;

	//数据发送
	m_SendSocket.Create(1234, SOCK_DGRAM);//创建一个套接字句柄（UDP）
	m_SendSocket.SendTo(pMsg, sizeof(Msg), 8888, m_toIP);//发送数据给本地计算机
	m_SendSocket.Close();
	Msg.ip = "";
	Msg.name = "";
	Msg.header = "";
	Msg.data = "";
	Msg.respTo = "";
	m_message = "";
	UpdateData(false);
}

void CQueryDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CSocket m_SendSocket;//构造一个套接字对象

	CString header, respTo, data, name;

	//接收数据
	m_SendSocket.Create(1234, SOCK_DGRAM);
	pMsg = &Msg;

	//发送数据的初始化
	USES_CONVERSION;
	Msg.ip = W2A(m_localIP);
	Msg.name = W2A(m_name);
	Msg.header = "event";
	Msg.data = "offline";
	m_SendSocket.SendTo(pMsg, sizeof(Msg), 8888, m_toIP);//发送退登包
	m_SendSocket.Close();
	CDialog::OnOK();
}
