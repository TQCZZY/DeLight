// QueryDlg.cpp: 实现文件
//

#include "pch.h"
#include "DeLight.h"
#include <string>
#include "afxdialogex.h"
#include "QueryDlg.h"


// CQueryDlg 对话框

IMPLEMENT_DYNAMIC(CQueryDlg, CDialogEx)

CQueryDlg::CQueryDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_REMOTEQUERY_DIALOG, pParent)
{
	m_toIP = _T("");
	m_message = _T("");
	m_name = _T("");
}

CQueryDlg::~CQueryDlg()
{
}

void CQueryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CQueryDlg)
	DDX_Control(pDX, IDC_RMQDLG_ENTER, m_enter);
	DDX_Control(pDX, IDC_RMQDLG_LIST, m_show);
	DDX_Text(pDX, IDC_RMQDLG_IP, m_toIP);
	DDX_Text(pDX, IDC_RMQDLG_MESSAGE, m_message);
	DDX_Text(pDX, IDC_RMQDLG_WHNAME, m_name);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CQueryDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CQueryDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_RMQDLG_SEND, &CQueryDlg::OnBnClickedSend)
	ON_BN_CLICKED(IDC_RMQDLG_ENTER, &CQueryDlg::OnBnClickedEnter)
END_MESSAGE_MAP()


// CQueryDlg 消息处理程序

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
HANDLE listenThreadHandle = INVALID_HANDLE_VALUE;

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
		}
		else {
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

void CQueryDlg::OnBnClickedOk()
{
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
	size_t i = m_show.GetCount();
	for (; i > 0; i--)
	{
		m_show.DeleteString(i - 1);
	}
	m_enter.EnableWindow(true);
	m_localIP = "";
	m_toIP = "";
	m_message = "";
	m_name = "";
	UpdateData(false);
	if (listenThreadHandle != INVALID_HANDLE_VALUE)
	{
		TerminateThread(listenThreadHandle, 0);//结束一个线程
	}
	CDialogEx::OnOK();
}

void CQueryDlg::OnBnClickedSend()
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


void CQueryDlg::OnBnClickedEnter()
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
	if (listenThreadHandle == INVALID_HANDLE_VALUE)
	{
		CreateThread(NULL, 0, LinsenThread, this, NULL, NULL);//创建一个新线程
	}
}
