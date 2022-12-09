// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"
#include <vector>
#include <fstream>
#include <Windows.h>
#include "Lines.h"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

std::vector<std::pair<int, int> > points;

std::vector<RECT> mapRects;

bool isLineIntersectRectangle(RECT R, POINT A, POINT B)
{
    float linePointX1 = A.x;
    float linePointY1 = A.y;
    float linePointX2 = B.x;
    float linePointY2 = B.y;
    float rectangleLeftTopX = R.left;
    float rectangleLeftTopY = R.top;
    float rectangleRightBottomX = R.right;
    float rectangleRightBottomY = R.bottom;
    float lineHeight = linePointY1 - linePointY2;
    float lineWidth = linePointX2 - linePointX1;  // 计算叉乘 
    float c = linePointX1 * linePointY2 - linePointX2 * linePointY1;
    if ((lineHeight * rectangleLeftTopX + lineWidth * rectangleLeftTopY + c >= 0 && lineHeight * rectangleRightBottomX + lineWidth * rectangleRightBottomY + c <= 0)
        || (lineHeight * rectangleLeftTopX + lineWidth * rectangleLeftTopY + c <= 0 && lineHeight * rectangleRightBottomX + lineWidth * rectangleRightBottomY + c >= 0)
        || (lineHeight * rectangleLeftTopX + lineWidth * rectangleRightBottomY + c >= 0 && lineHeight * rectangleRightBottomX + lineWidth * rectangleLeftTopY + c <= 0)
        || (lineHeight * rectangleLeftTopX + lineWidth * rectangleRightBottomY + c <= 0 && lineHeight * rectangleRightBottomX + lineWidth * rectangleLeftTopY + c >= 0))
    {

        if (rectangleLeftTopX > rectangleRightBottomX)
        {
            float temp = rectangleLeftTopX;
            rectangleLeftTopX = rectangleRightBottomX;
            rectangleRightBottomX = temp;
        }
        if (rectangleLeftTopY < rectangleRightBottomY)
        {
            float temp1 = rectangleLeftTopY;
            rectangleLeftTopY = rectangleRightBottomY;
            rectangleRightBottomY = temp1;
        }
        if ((linePointX1 < rectangleLeftTopX && linePointX2 < rectangleLeftTopX)
            || (linePointX1 > rectangleRightBottomX && linePointX2 > rectangleRightBottomX)
            || (linePointY1 > rectangleLeftTopY && linePointY2 > rectangleLeftTopY)
            || (linePointY1 < rectangleRightBottomY && linePointY2 < rectangleRightBottomY))
        {
            return false;
        }
        else
        {
            return true;
        }
    }
    else
    {
        return false;
    }
}

int IsRouteValid(POINT End1, POINT End2)
{
    for (size_t i = 0; i < mapRects.size(); ++i)
    {
        if (/*RSIntersection*/isLineIntersectRectangle(mapRects[i], End1, End2))
        {
            return false;
        }
    }
    return true;
}

__declspec(dllexport) std::vector<std::pair<int, int> >
GetRoute(std::vector<std::pair<int, int> > dst)
{
    points = { {310,110},{430,110},{615,110},{765,110},{915,110},{1110,110},{260,130},{260,180},{430,180},{615,180},{765,180},{915,180},{700,350},{1155,435},{850,320},{975,435},{625,530} };
    std::fstream fs("map.txt", std::ios::in);
    float x1, y1, x2, y2;
    for (int i = 0; i < 23; i++)
    {
        RECT ls;
        std::string desc;
        fs >> x1 >> y1 >> x2 >> y2 >> desc;
        ls.left = x1;
        ls.right = x2;
        ls.bottom = y2;
        ls.top = y1;
        mapRects.push_back(ls);
    }

    points.push_back(std::pair<int, int>((mapRects[0].left + mapRects[0].right)/2, mapRects[0].bottom + 1));
    int srcCode = points.size() - 1;
    std::vector<int>dstCode;
    for (size_t i = 0; i < dst.size(); i++)
    {
        points.push_back(dst[i]);
        dstCode.push_back(points.size() - 1);
    }

    bool hasUnreachable;
    std::vector<std::vector<float> > distance(points.size(), std::vector<float>(points.size()));
    for (size_t i = 0; i < points.size(); ++i)
    {
        hasUnreachable = true;
        for (size_t j = 0; j < points.size(); ++j)
        {
            if (i != j)
            {
                if (IsRouteValid(POINT{ points[i].first, points[i].second }, POINT{ points[j].first, points[j].second }))
                {
                    distance[i][j] = sqrt(pow(points[i].first - points[j].first, 2) + pow(points[i].second - points[j].second, 2));
                    hasUnreachable = false;
                }
                else
                {
                    distance[i][j] = INF;
                }
            }
        }
        if (hasUnreachable)
        {
            return std::vector<std::pair<int, int> >{};
        }
    }
    dstCode = Get_Order(srcCode, dstCode, distance);
    std::vector<std::pair<int, int> > path;
    for (size_t i = 0; i < dstCode.size(); i++)
    {
        path.push_back(std::pair<int, int>(points[dstCode[i]].first, points[dstCode[i]].second));
    }
    points.clear();
    mapRects.clear();
    return path;
}


