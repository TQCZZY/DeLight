// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"

HINSTANCE hInst;                                // 当前实例

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        hInst = hModule;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

#include "framework.h"
#include "Resource.h"
#include <windows.h>
#include <vector>

#define MAX_LOADSTRING 100
#define GET_X_LPARAM(lp)                        ((int)(short)LOWORD(lp))

#define GET_Y_LPARAM(lp)                        ((int)(short)HIWORD(lp))

// 全局变量:
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];   // 主窗口类名
std::vector<std::pair<int, int> > points; //存放点
std::vector<std::pair<int, int> > cornerpoints;//
std::vector<std::pair<int, int> > Recepoints;//接收返回点
int iclick = 0;    //鼠标点击次数
HWND hWnd;
RECT rect;
bool confirmedSel = false;

void cornerpointsbegin() {
    cornerpoints.push_back(std::pair<int, int>(50, 50));
    cornerpoints.push_back(std::pair<int, int>(200, 50));
    cornerpoints.push_back(std::pair<int, int>(200, 150));
    cornerpoints.push_back(std::pair<int, int>(50, 150));
    cornerpoints.push_back(std::pair<int, int>(320, 50));
    cornerpoints.push_back(std::pair<int, int>(420, 50));
    cornerpoints.push_back(std::pair<int, int>(420, 100));
    cornerpoints.push_back(std::pair<int, int>(320, 100));
    cornerpoints.push_back(std::pair<int, int>(440, 50));
    cornerpoints.push_back(std::pair<int, int>(590, 50));
    cornerpoints.push_back(std::pair<int, int>(590, 100));
    cornerpoints.push_back(std::pair<int, int>(440, 100));
    cornerpoints.push_back(std::pair<int, int>(640, 50));
    cornerpoints.push_back(std::pair<int, int>(740, 50));
    cornerpoints.push_back(std::pair<int, int>(740, 100));
    cornerpoints.push_back(std::pair<int, int>(640, 100));
    cornerpoints.push_back(std::pair<int, int>(790, 50));
    cornerpoints.push_back(std::pair<int, int>(890, 50));
    cornerpoints.push_back(std::pair<int, int>(890, 100));
    cornerpoints.push_back(std::pair<int, int>(790, 100));
    cornerpoints.push_back(std::pair<int, int>(940, 50));
    cornerpoints.push_back(std::pair<int, int>(1090, 50));
    cornerpoints.push_back(std::pair<int, int>(1090, 100));
    cornerpoints.push_back(std::pair<int, int>(940, 100));
    cornerpoints.push_back(std::pair<int, int>(1110, 50));
    cornerpoints.push_back(std::pair<int, int>(1260, 50));
    cornerpoints.push_back(std::pair<int, int>(1260, 100));
    cornerpoints.push_back(std::pair<int, int>(1110, 100));
    cornerpoints.push_back(std::pair<int, int>(320, 120));
    cornerpoints.push_back(std::pair<int, int>(420, 120));
    cornerpoints.push_back(std::pair<int, int>(420, 170));
    cornerpoints.push_back(std::pair<int, int>(320, 170));
    cornerpoints.push_back(std::pair<int, int>(440, 120));
    cornerpoints.push_back(std::pair<int, int>(590, 120));
    cornerpoints.push_back(std::pair<int, int>(590, 170));
    cornerpoints.push_back(std::pair<int, int>(440, 170));
    cornerpoints.push_back(std::pair<int, int>(640, 120));
    cornerpoints.push_back(std::pair<int, int>(740, 120));
    cornerpoints.push_back(std::pair<int, int>(740, 170));
    cornerpoints.push_back(std::pair<int, int>(640, 170));
    cornerpoints.push_back(std::pair<int, int>(790, 120));
    cornerpoints.push_back(std::pair<int, int>(890, 120));
    cornerpoints.push_back(std::pair<int, int>(890, 170));
    cornerpoints.push_back(std::pair<int, int>(790, 170));
    cornerpoints.push_back(std::pair<int, int>(150, 200));
    cornerpoints.push_back(std::pair<int, int>(600, 200));
    cornerpoints.push_back(std::pair<int, int>(600, 500));
    cornerpoints.push_back(std::pair<int, int>(150, 500));
    cornerpoints.push_back(std::pair<int, int>(640, 190));
    cornerpoints.push_back(std::pair<int, int>(700, 190));
    cornerpoints.push_back(std::pair<int, int>(700, 240));
    cornerpoints.push_back(std::pair<int, int>(640, 240));
    cornerpoints.push_back(std::pair<int, int>(700, 210));
    cornerpoints.push_back(std::pair<int, int>(760, 210));
    cornerpoints.push_back(std::pair<int, int>(760, 240));
    cornerpoints.push_back(std::pair<int, int>(700, 240));
    cornerpoints.push_back(std::pair<int, int>(790, 190));
    cornerpoints.push_back(std::pair<int, int>(890, 190));
    cornerpoints.push_back(std::pair<int, int>(890, 240));
    cornerpoints.push_back(std::pair<int, int>(790, 240));
    cornerpoints.push_back(std::pair<int, int>(1050, 360));
    cornerpoints.push_back(std::pair<int, int>(1260, 360));
    cornerpoints.push_back(std::pair<int, int>(1260, 410));
    cornerpoints.push_back(std::pair<int, int>(1050, 410));
    cornerpoints.push_back(std::pair<int, int>(800, 400));
    cornerpoints.push_back(std::pair<int, int>(900, 400));
    cornerpoints.push_back(std::pair<int, int>(800, 500));
    cornerpoints.push_back(std::pair<int, int>(800, 500));
    cornerpoints.push_back(std::pair<int, int>(1050, 460));
    cornerpoints.push_back(std::pair<int, int>(1260, 510));
    cornerpoints.push_back(std::pair<int, int>(1260, 510));
    cornerpoints.push_back(std::pair<int, int>(1050, 460));
    cornerpoints.push_back(std::pair<int, int>(300, 560));
    cornerpoints.push_back(std::pair<int, int>(750, 560));
    cornerpoints.push_back(std::pair<int, int>(750, 760));
    cornerpoints.push_back(std::pair<int, int>(300, 760));
    cornerpoints.push_back(std::pair<int, int>(940, 160));
    cornerpoints.push_back(std::pair<int, int>(1090, 160));
    cornerpoints.push_back(std::pair<int, int>(1090, 310));
    cornerpoints.push_back(std::pair<int, int>(940, 310));
    return;
}

int IsInRect(int LX, int LY, int RX, int RY, int x, int y)
{
    if (LX <= x && RX >= x && LY <= y && RY >= y) {
        return 1;
    }
    else { return 0; }
}

void judgecorner(int X, int Y)
{
    int num = cornerpoints.size();
    int i = 0;

    while (i < num) {
        int LX = cornerpoints[i].first - 8;
        int LY = cornerpoints[i].second - 8;
        int RX = cornerpoints[i].first + 8;
        int RY = cornerpoints[i].second + 8;

        if (IsInRect(LX, LY, RX, RY, X, Y)) {
            points.push_back(std::pair<int, int>(cornerpoints[i].first, cornerpoints[i].second));
            return;
        }
        i++;
    }
    return;
}//判断四个顶点

// 此代码模块中包含的函数的前向声明:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

//
//  函数: MyRegisterClass()
//
//  目标: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MAP));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_MAP);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目标: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(int nCmdShow)
{
    hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInst, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    cornerpointsbegin();//初始化

    return TRUE;
}


//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目标: 处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // 分析菜单选择:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        case IDM_CMPLTSEL:
            confirmedSel = true;
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: 在此处添加使用 hdc 的任何绘图代码...
        const int length0 = 50;
        const int length1 = 100;
        const int length2 = 120;
        const int length3 = 170;
        const int length4 = 190;
        const int length5 = 240;

        Rectangle(hdc, 50, length0, 200, 150);
        Rectangle(hdc, 220, length0, 300, length1);
        Rectangle(hdc, 320, length0, 420, length1);
        Rectangle(hdc, 440, length0, 590, length1);
        Rectangle(hdc, 640, length0, 740, length1);
        Rectangle(hdc, 790, length0, 890, length1);
        Rectangle(hdc, 940, length0, 1090, length1);
        Rectangle(hdc, 1110, length0, 1260, length1);
        Rectangle(hdc, 320, length2, 420, length3);
        Rectangle(hdc, 440, length2, 590, length3);
        Rectangle(hdc, 640, length2, 740, length3);
        Rectangle(hdc, 790, length2, 890, length3);
        Rectangle(hdc, 640, length4, 700, length5);
        Rectangle(hdc, 700, 210, 760, length5);
        Rectangle(hdc, 150, 200, 600, 500);
        Rectangle(hdc, 790, length4, 890, length5);
        Rectangle(hdc, 940, 160, 1090, 190);
        Rectangle(hdc, 1000, 190, 1030, 280);
        Rectangle(hdc, 940, 280, 1090, 310);
        Rectangle(hdc, 1050, 360, 1260, 410);
        Rectangle(hdc, 1050, 460, 1260, 510);
        Rectangle(hdc, 800, 400, 900, 500);
        //校区

        Rectangle(hdc, 300, 560, 750, 760);
        //欣苑

        GetClientRect(hWnd, &rect);
        DrawText(hdc, TEXT("请点击您想要配送的地址"), -1, &rect, DT_CENTER | DT_VCENTER);

        RECT aa{ 50 , length0,200 ,150 };
        DrawText(hdc, TEXT("女生宿舍1"), -1, &aa, DT_CENTER | DT_VCENTER);
        RECT ab{ 220, length0,300 , length1 };
        DrawText(hdc, TEXT("仓库"), -1, &ab, DT_CENTER | DT_VCENTER);
        RECT ac{ 320, length0,420 , length1 };
        DrawText(hdc, TEXT("女生宿舍2"), -1, &ac, DT_CENTER | DT_VCENTER);
        RECT ad{ 440, length0,590 , length1 };
        DrawText(hdc, TEXT("餐厅1"), -1, &ad, DT_CENTER | DT_VCENTER);
        RECT ae{ 640, length0,740 , length1 };
        DrawText(hdc, TEXT("信息中心"), -1, &ae, DT_CENTER | DT_VCENTER);
        RECT af{ 790, length0,890 , length1 };
        DrawText(hdc, TEXT("三教"), -1, &af, DT_CENTER | DT_VCENTER);
        RECT ag{ 940, length0,1090 , length1 };
        DrawText(hdc, TEXT("二教"), -1, &ag, DT_CENTER | DT_VCENTER);
        RECT ah{ 1110, length0,1260 ,length1 };
        DrawText(hdc, TEXT("一教"), -1, &ah, DT_CENTER | DT_VCENTER);

        RECT ba{ 320, length2,420 , length3 };
        DrawText(hdc, TEXT("停车场1"), -1, &ba, DT_CENTER | DT_VCENTER);
        RECT bb{ 440, length2,590 , length3 };
        DrawText(hdc, TEXT("餐厅2"), -1, &bb, DT_CENTER | DT_VCENTER);
        RECT bc{ 640, length2,740 , length3 };
        DrawText(hdc, TEXT("通信大楼"), -1, &bc, DT_CENTER | DT_VCENTER);
        RECT bd{ 790, length2,890 , length3 };
        DrawText(hdc, TEXT("光电楼"), -1, &bd, DT_CENTER | DT_VCENTER);
        RECT be{ 940 ,160 ,1090 ,190 };
        DrawText(hdc, TEXT("主楼"), -1, &be, DT_CENTER | DT_VCENTER);

        RECT ca{ 150,200 ,600 ,500 };
        DrawText(hdc, TEXT("    操场    "), -1, &ca, DT_CENTER | DT_VCENTER);
        RECT cb{ 640, length4,700 , length5 };
        DrawText(hdc, TEXT("实验大楼"), -1, &cb, DT_CENTER | DT_VCENTER);
        RECT cc{ 700,    210 ,760 , length5 };
        DrawText(hdc, TEXT("四教"), -1, &cc, DT_CENTER | DT_VCENTER);
        RECT cd{ 790,length4 , 890, length5 };
        DrawText(hdc, TEXT("微固楼"), -1, &cd, DT_CENTER | DT_VCENTER);

        RECT da{ 1050,360 ,1260 ,410 };
        DrawText(hdc, TEXT("图书馆"), -1, &da, DT_CENTER | DT_VCENTER);

        RECT ea{ 800,400 ,900 ,500 };
        DrawText(hdc, TEXT("停车场2"), -1, &ea, DT_CENTER | DT_VCENTER);
        RECT eb{ 1050,460 ,1260 ,510 };
        DrawText(hdc, TEXT("电子大厦"), -1, &eb, DT_CENTER | DT_VCENTER);

        RECT fa{ 300 ,560 ,750 ,760 };
        DrawText(hdc, TEXT("  欣苑  "), -1, &fa, DT_CENTER | DT_VCENTER);

        int i = 0;
        if (i < Recepoints.size()) {
            int x1 = 0;
            int y1 = 0;
            int x2 = 0;
            int y2 = 0;

            x1 = Recepoints[i].first;
            y1 = Recepoints[i].second;
            x2 = Recepoints[i + 1].first;
            y2 = Recepoints[i + 1].second;
            MoveToEx(hdc, x1, y1, NULL); //设定起始点,不保存当前点坐标
            LineTo(hdc, x2, y2);
            i++;
        }
        EndPaint(hWnd, &ps);
        return 0;
    }
    break;
    case WM_LBUTTONDOWN:
    {
        int x = GET_X_LPARAM(lParam);
        int y = GET_Y_LPARAM(lParam);
        judgecorner(x, y);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

__declspec(dllexport)int itfCreateWindow(int nCmdShow)
{
    // 初始化全局字符串
    LoadStringW(hInst, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInst, IDC_MAP, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInst);

    // 执行应用程序初始化:
    if (!InitInstance(nCmdShow))
    {
        return 1;
    }

    HACCEL hAccelTable = LoadAccelerators(hInst, MAKEINTRESOURCE(IDC_MAP));

    MSG msg;

    // 主消息循环:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    return 0;
}//接口输出

__declspec(dllexport)std::vector<std::pair<int, int> > Sentpoints()
{
    while (!confirmedSel)
    {
    }
    return points;
}//接口输出

__declspec(dllexport)void receive(std::vector<std::pair<int, int> >Re)
{
    Recepoints = Re;
    LPRECT r = NULL;
    GetClientRect(hWnd, r);
    InvalidateRect(hWnd, r, TRUE);
}
