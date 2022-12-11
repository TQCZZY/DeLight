// QueryDlg.cpp: 实现文件
//

#include "pch.h"
#include "DeLight.h"
#include <string>
#include <vector>
#include "afxdialogex.h"
#include "List.h"
#include "QueryDlg.h"


// CQueryDlg 对话框

IMPLEMENT_DYNAMIC(CQueryDlg, CDialogEx)

CQueryDlg::CQueryDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_REMOTEQUERY_DIALOG, pParent)
{
	m_toIP = _T("");
	m_message = _T("");
	m_name = _T("");
	listenThreadHandle = INVALID_HANDLE_VALUE;
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


ULONG WINAPI TimeoutThread(LPVOID p) {
	Sleep(15000);
	CQueryDlg* pDlg = (CQueryDlg*)p;
	if (!pDlg->serverRespond)
	{
		pDlg->m_enter.EnableWindow(true);
		if (pDlg->dirtyReceiveSocket)
		{
			WSACancelBlockingCall();
			//m_ReceiveSocket.Close();
			pDlg->dirtyReceiveSocket = false;
		}
		if (pDlg->listenThreadHandle != INVALID_HANDLE_VALUE)
		{
			TerminateThread(pDlg->listenThreadHandle, 0);//结束一个线程
			pDlg->listenThreadHandle = INVALID_HANDLE_VALUE;
		}
		MessageBox(pDlg->m_hWnd, L"数据中心未响应请求，请重试", L"请求失败", MB_ICONERROR);
	}
	return 0;
}

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

	CString header, respTo, data, name;

	//接收数据
	pDlg->m_ReceiveSocket.Create(6666, SOCK_DGRAM);
	pDlg->dirtyReceiveSocket = true;
	pDlg->pMsg = &pDlg->Msg;

	//发送数据的初始化
	USES_CONVERSION;
	strcpy(pDlg->Msg.ip, W2A(pDlg->m_localIP));
	strcpy(pDlg->Msg.name, W2A(pDlg->m_name));
	strcpy(pDlg->Msg.header, "event");
	strcpy(pDlg->Msg.data, "online");
	pDlg->m_ReceiveSocket.SendTo(pDlg->pMsg, sizeof(pDlg->Msg), 8888, pDlg->m_toIP);//发送登录包
	strcpy(pDlg->Msg.ip, "");
	strcpy(pDlg->Msg.name, "");
	strcpy(pDlg->Msg.header, "");
	strcpy(pDlg->Msg.data, "");
	strcpy(pDlg->Msg.respTo, "");
	pDlg->serverRespond = false;
	//CreateThread(NULL, 0, TimeoutThread, pDlg, NULL, NULL);//创建一个新线程

	while (1) {
		int n = pDlg->m_ReceiveSocket.Receive(pDlg->pMsg, sizeof(pDlg->Msg));
		if (n == 0)
			continue;

		data = pDlg->pMsg->data;
		name = pDlg->pMsg->name;
		header = pDlg->pMsg->header;
		respTo = pDlg->pMsg->respTo;
		if (data.IsEmpty() || name.IsEmpty() || (header == "event" && (name != "Data Center" && name != pDlg->m_name)) || (header == "respond" && name != pDlg->m_name && respTo != pDlg->m_name))
			continue;
		pDlg->serverRespond = true;
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
				//m_ReceiveSocket.Close();
				pDlg->dirtyReceiveSocket = false;
				return 0;
			}
		}
		else {
			pDlg->m_show.InsertString(-1, name + " " + header + "s: " + data);
			if (header == "require")
			{
				USES_CONVERSION;
				Search_Info si;
				si.name = W2A(data);
				si.type = 1;
				std::vector<int> sr = Search(si);
				if (sr.size())//search success
				{
					CSocket m_SendSocket;//构造一个套接字对象

					//发送数据的初始化
					strcpy(pDlg->Msg.ip, W2A(pDlg->m_localIP));
					strcpy(pDlg->Msg.name, W2A(pDlg->m_name));
					strcpy(pDlg->Msg.header, "respond");
					strcpy(pDlg->Msg.data, W2A(data));
					strcpy(pDlg->Msg.respTo, W2A(name));

					//数据发送
					m_SendSocket.Create(1234, SOCK_DGRAM);//创建一个套接字句柄（UDP）
					m_SendSocket.SendTo(pDlg->pMsg, sizeof(pDlg->Msg), 8888, pDlg->m_toIP);//发送数据给本地计算机
					m_SendSocket.Close();
					strcpy(pDlg->Msg.ip, "");
					strcpy(pDlg->Msg.name, "");
					strcpy(pDlg->Msg.header, "");
					strcpy(pDlg->Msg.data, "");
					strcpy(pDlg->Msg.respTo, "");
				}
			}
		}
	}
	//m_ReceiveSocket.Close();
	pDlg->dirtyReceiveSocket = false;
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
	strcpy(Msg.ip, W2A(m_localIP));
	strcpy(Msg.name, W2A(m_name));
	strcpy(Msg.header, "event");
	strcpy(Msg.data, "offline");
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
	if (dirtyReceiveSocket)
	{
		WSACancelBlockingCall();
		m_ReceiveSocket.Close();
		//fixme: unbind old thread and bind new thread
		dirtyReceiveSocket = false;
	}
	if (listenThreadHandle != INVALID_HANDLE_VALUE)
	{
		TerminateThread(listenThreadHandle, 0);//结束一个线程
		listenThreadHandle = INVALID_HANDLE_VALUE;
	}
	CDialogEx::OnOK();
}

void CQueryDlg::OnBnClickedSend()
{
	UpdateData(true);

	CSocket m_SendSocket;//构造一个套接字对象

	//发送数据的初始化
	USES_CONVERSION;
	strcpy(Msg.ip, W2A(m_localIP));
	strcpy(Msg.name, W2A(m_name));
	strcpy(Msg.header, "require");
	strcpy(Msg.data, W2A(m_message));
	strcpy(Msg.respTo, "");
	pMsg = &Msg;

	//数据发送
	m_SendSocket.Create(1234, SOCK_DGRAM);//创建一个套接字句柄（UDP）
	m_SendSocket.SendTo(pMsg, sizeof(Msg), 8888, m_toIP);//发送数据给本地计算机
	m_SendSocket.Close();
	strcpy(Msg.ip, "");
	strcpy(Msg.name, "");
	strcpy(Msg.header, "");
	strcpy(Msg.data, "");
	strcpy(Msg.respTo, "");
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
		listenThreadHandle = CreateThread(NULL, 0, LinsenThread, this, NULL, NULL);//创建一个新线程
	}
}
