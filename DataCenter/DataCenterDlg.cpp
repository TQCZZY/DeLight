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

HANDLE hListenThread = INVALID_HANDLE_VALUE;
void CDataCenterDlg::OnServer() 
{
	if (hListenThread != INVALID_HANDLE_VALUE)
	{
		return;
	}
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
	hListenThread = CreateThread(NULL,0,LinsenThread,this,NULL,NULL);//创建一个新线程
}

struct SocMsg
{
	char ip[21];
	char name[31];
	char header[11];
	char respTo[31];
	char data[101];
};
SocMsg Msg;
SocMsg* pMsg;

CStringArray m_client;

size_t attackCount = 0;

void sendEvent(std::string event)
{
	CSocket m_SendSocket;//构造一个套接字对象
	m_SendSocket.Create(1234, SOCK_DGRAM);

	strcpy(pMsg->data, event.c_str());
	strcpy(pMsg->name, "Data Center");
	strcpy(pMsg->header, "event");
	strcpy(pMsg->respTo, "");
	//把信息发送给列表中的每个客户端
	CString listIP;
	int len = m_client.GetSize();
	for (int k = 0; k < len; k++) {
		listIP = m_client.GetAt(k);
		m_SendSocket.SendTo(pMsg, sizeof(Msg), 6666, listIP);//群发数据给客户端
	}
	m_SendSocket.Close();
}

/*-------------------------------------------------------------------
线程函数名：LinsenThread
属性：全局函数
功能：接收客户端发来的信息，转发给所有客户端，并显示到列表框中
参数p--指向界面对话框的指针
---------------------------------------------------------------------*/

ULONG WINAPI LinsenThread(LPVOID p){
	//获取指向界面对话框的指针，通过该指针可以调用界面上的控件
	CDataCenterDlg *pDlg=(CDataCenterDlg *)p;

	CSocket m_ReceiveSocket;//构造一个套接字对象

	CString respTo, header, data, name, clientIP;

	m_ReceiveSocket.Create(8888,SOCK_DGRAM);	
	pMsg = &Msg;

	while(1){
		m_ReceiveSocket.Receive(pMsg, sizeof(Msg));
		
		//判断列表中是否已存在该客户
		clientIP = pMsg->ip;
		CString listIP;
		bool flag = 0;
		int len = m_client.GetSize();
		int i = 0;
		for (i = 0; i < len; i++) {
			if (clientIP == m_client.GetAt(i)) {
				flag = 1;//列表中已存在该IP，则设为1
				break;
			}
		}
		data = pMsg->data;
		header = pMsg->header;
		if (flag)
		{
			name = pMsg->name;
			respTo = pMsg->respTo;
			if (data.IsEmpty() || name.IsEmpty())
				continue;
			CString displayContent;
			if (header == "require") {
				displayContent = name + " " + header + "s: " + data;
			}
			else if (header == "respond") {
				displayContent = name + " " + header + "s to " + respTo + ": " + data;
			}
			else {
				displayContent = header + " from " + name + ": " + data;
			}
			pDlg->m_show.InsertString(-1, displayContent);

			if (header == "event" && data == "offline")
			{
				m_client.RemoveAt(i);
			}
		}
		else
		{
			if (header == "event" && data == "online")
			{
				name = pMsg->name;
				CString displayContent;
				displayContent = header + " from " + name + ": " + data;
				pDlg->m_show.InsertString(-1, displayContent);
				m_client.Add(clientIP);//如果不存在则添加到列表中
			}
			else
			{
				++attackCount;
				if (attackCount >= 100)
				{
					pDlg->m_show.InsertString(-1, L"Warning: Cyber attack threshold reached. Data Center may under cyber attack.");
					m_ReceiveSocket.Close();
					sendEvent("protect");
					pDlg->m_show.InsertString(-1, L"Data Center has shut down automatically as a means of protection.");
				}
				else
				{
					pDlg->m_show.InsertString(-1, L"Warning: Received data from unknown source.");
				}
				continue;
			}
		}

		//把信息发送给列表中的每个客户
		len= m_client.GetSize();
		for(int k=0; k<len; k++){                  
			listIP = m_client.GetAt(k);
			m_ReceiveSocket.SendTo( pMsg, sizeof(Msg),6666,listIP);//转发数据给其他客户端
		}
	}
	m_ReceiveSocket.Close();
	return 0;
}

void CDataCenterDlg::OnBnClickedCancel()
{
	TerminateThread(hListenThread, 0);
	sendEvent("close");
	CDialog::OnCancel();
}
