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
#include <fstream>
#include <atlconv.h>

#define MAX_LOADSTRING 100
#define GET_X_LPARAM(lp)                        ((int)(short)LOWORD(lp))

#define GET_Y_LPARAM(lp)                        ((int)(short)HIWORD(lp))

// 全局变量:
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];   // 主窗口类名
HWND hWnd;
std::vector<RECT> MapRects;
std::vector<std::string> MapRectsDesc;
std::vector<std::pair<int, int> > points; //存放点
std::vector<std::pair<int, int> > RcvPoints;//接收返回点
bool confirmedSel = false;

bool IsInRect(int LX, int LY, int RX, int RY, int x, int y)
{
    if (LX <= x && RX >= x && LY <= y && RY >= y) {
        return true;
    }
    else {
        return false;
    }
}

void FilterPoint(int X, int Y)
{
    for (size_t i = 0; i < MapRects.size(); ++i)
    {
        if (IsInRect(MapRects[i].left, MapRects[i].top, MapRects[i].right, MapRects[i].bottom, X, Y)) {
            return;
        }
    }
    points.push_back(std::pair<int, int>(X, Y));
    RECT r;
    GetClientRect(hWnd, &r);
    InvalidateRect(hWnd, &r, TRUE);
    return;
}

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

void LoadMap()
{
    std::fstream fs("map.txt", std::ios::in);
    float x1, y1, x2, y2;
    for (int i = 0; i < 23; i++)
    {
        std::string desc;
        fs >> x1 >> y1 >> x2 >> y2 >> desc;
        if (desc == "#")
        {
            desc = "";
        }
        MapRectsDesc.push_back(desc);
        RECT ls;
        ls.left = x1;
        ls.top = y1;
        ls.right = x2;
        ls.bottom = y2;
        MapRects.push_back(ls);
    }
    fs.close();
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

    LoadMap();

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
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
            if (!RcvPoints.size())
            {
                confirmedSel = true;
                ModifyMenu(GetMenu(hWnd), IDM_CMPLTSEL, MF_BYCOMMAND | MF_STRING, IDM_CMPLTSEL, L"重置地图(&R)");
            }
            else
            {
                MapRects.resize(0);
                MapRectsDesc.resize(0);
                points.resize(0); //存放点
                RcvPoints.resize(0);//接收返回点
                ModifyMenu(GetMenu(hWnd), IDM_CMPLTSEL, MF_BYCOMMAND | MF_STRING, IDM_CMPLTSEL, L"完成选择(&F)");
                LoadMap();
                RECT r;
                GetClientRect(hWnd, &r);
                InvalidateRect(hWnd, &r, TRUE);
            }
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
        RECT rect;
        GetClientRect(hWnd, &rect);
        DrawText(hdc, TEXT("请点击您想要配送的位置"), -1, &rect, DT_CENTER | DT_VCENTER);

        for (size_t i = 0; i < MapRects.size(); ++i)
        {
            Rectangle(hdc, MapRects[i].left, MapRects[i].top, MapRects[i].right, MapRects[i].bottom);
        }

        USES_CONVERSION;
        for (size_t i = 0; i < MapRects.size(); ++i)
        {
            DrawText(hdc, A2W(MapRectsDesc[i].c_str()), -1, &MapRects[i], DT_CENTER | DT_VCENTER);
        }

        for (size_t i = 0; i < points.size(); ++i)
        {
            Rectangle(hdc, points[i].first - 5, points[i].second - 5, points[i].first + 5, points[i].second + 5);
        }
        
        for (int i = 0; RcvPoints.size() != 0 && i < RcvPoints.size() - 1; ++i) {
            MoveToEx(hdc, RcvPoints[i].first, RcvPoints[i].second, NULL); //设定起始点,不保存当前点坐标
            LineTo(hdc, RcvPoints[i + 1].first, RcvPoints[i + 1].second);
        }
        EndPaint(hWnd, &ps);
        return 0;
    }
    break;
    case WM_LBUTTONDOWN:
    {
        int x = GET_X_LPARAM(lParam);
        int y = GET_Y_LPARAM(lParam);
        FilterPoint(x, y);
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

__declspec(dllexport)int CreateMapWindow(int nCmdShow)
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
    MapRects.resize(0);
    MapRectsDesc.resize(0);
    points.resize(0); //存放点
    RcvPoints.resize(0);//接收返回点
    DestroyWindow(hWnd);
    return 0;
}//接口输出

__declspec(dllexport)std::vector<std::pair<int, int> > SendPoints()
{
    while (!confirmedSel)
    {
    }
    confirmedSel = false;
    return points;
}//接口输出

__declspec(dllexport)void ReceivePoints(std::vector<std::pair<int, int> >Re)
{
    if (Re.size() == 0)
    {
        MessageBox(hWnd, L"所选目的地不在配送范围", L"无法配送", MB_ICONERROR);
    }
    RcvPoints = Re;
    RECT r;
    GetClientRect(hWnd, &r);
    InvalidateRect(hWnd, &r, TRUE);
}
