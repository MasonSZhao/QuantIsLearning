// Copyright (c) 2025-present Mason Zhao MasonSZhao@qq.com

#include "..\include\QilD2dWndDepMain.h"

#include "..\..\QilHost\include\QilHostFileTd.h"
#include "..\include\QilD2dWndIndep.h"
#include <mutex>
#include <thread>

namespace QILD2D {

LRESULT CALLBACK D2dWndDepMain::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg) {
    case WM_ERASEBKGND: {
        return true /*avoid flicker*/;
    }
    case WM_NCDESTROY: {
        QILD2D::D2dWndDepMain* ptr = reinterpret_cast<QILD2D::D2dWndDepMain*>(static_cast<LONG_PTR>(GetWindowLongPtr(hWnd, GWLP_USERDATA)));
        QILD2D::D2dWndIndep::SafeRelease(&(ptr->m_D2dWndDep.m_pD2DSolidColorBrushGreen));
        QILD2D::D2dWndIndep::SafeRelease(&(ptr->m_D2dWndDep.m_pD2DSolidColorBrushRed));
        QILD2D::D2dWndIndep::SafeRelease(&(ptr->m_D2dWndDep.m_pD2DSolidColorBrushGray));
        QILD2D::D2dWndIndep::SafeRelease(&(ptr->m_D2dWndDep.m_pD2DSolidColorBrushLightGray));
        QILD2D::D2dWndIndep::SafeRelease(&(ptr->m_D2dWndDep.m_pD2DSolidColorBrushBlack));
        QILD2D::D2dWndIndep::SafeRelease(&(ptr->m_D2dWndDep.m_pD2D1HwndRenderTarget));
        delete ptr;
        ptr = nullptr;
        PostQuitMessage(0);
        return 0;
    }
    case WM_CREATE: {
        QILD2D::D2dWndDepMain* ptr = new QILD2D::D2dWndDepMain;
        SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(ptr));
        HRESULT hr = S_OK;
        if (SUCCEEDED(hr)) {
            RECT rc;
            GetClientRect(hWnd, &rc);
            hr = QILD2D::D2dWndIndep::s_pD2D1Factory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(hWnd, D2D1::SizeU(rc.right, rc.bottom)), &((*ptr).m_D2dWndDep.m_pD2D1HwndRenderTarget));
        }
        if (SUCCEEDED(hr)) {
            hr = (*ptr).m_D2dWndDep.m_pD2D1HwndRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &((*ptr).m_D2dWndDep.m_pD2DSolidColorBrushBlack));
            hr = (*ptr).m_D2dWndDep.m_pD2D1HwndRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::LightGray), &((*ptr).m_D2dWndDep.m_pD2DSolidColorBrushLightGray));
            hr = (*ptr).m_D2dWndDep.m_pD2D1HwndRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Gray), &((*ptr).m_D2dWndDep.m_pD2DSolidColorBrushGray));
            hr = (*ptr).m_D2dWndDep.m_pD2D1HwndRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Red), &((*ptr).m_D2dWndDep.m_pD2DSolidColorBrushRed));
            hr = (*ptr).m_D2dWndDep.m_pD2D1HwndRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Green), &((*ptr).m_D2dWndDep.m_pD2DSolidColorBrushGreen));
        }
        if (!SUCCEEDED(hr)) {
            delete ptr;
            ptr = nullptr;
        }
        // 并行线程
        if (SUCCEEDED(hr)) {
            std::vector<std::jthread> vecThread;
            // 并行线程 上证指数分时数据
            vecThread.emplace_back([&]() {
                std::vector<QILHOST::IntMinuteBar> des { QILHOST::TD::FileVecMinuteBar::int3264("1999999", 241, true) };
                {
                    ptr->m_D2dWndDepTimeSharingWMPAINT1999999.m_vecIntMinuteBar.reserve(240);
                    ptr->m_D2dWndDepTimeSharingWMPAINT1999999.m_preCl = des[0].m_cl;
                    ptr->m_D2dWndDepTimeSharingWMPAINT1999999.m_limitUpPr = des[1].m_cl;
                    ptr->m_D2dWndDepTimeSharingWMPAINT1999999.m_limitDnPr = des[1].m_cl;
                    ptr->m_D2dWndDepTimeSharingWMPAINT1999999.m_volMax = des[0].m_vol;
                    for (auto i { 1 }; i <= 240; ++i) {
                        ptr->m_D2dWndDepTimeSharingWMPAINT1999999.m_vecIntMinuteBar.push_back(des[i]);
                        if (des[i].m_vol > ptr->m_D2dWndDepTimeSharingWMPAINT1999999.m_volMax)
                            ptr->m_D2dWndDepTimeSharingWMPAINT1999999.m_volMax = des[i].m_vol;
                        if (des[i].m_cl > ptr->m_D2dWndDepTimeSharingWMPAINT1999999.m_limitUpPr)
                            ptr->m_D2dWndDepTimeSharingWMPAINT1999999.m_limitUpPr = des[i].m_cl;
                        if (des[i].m_cl < ptr->m_D2dWndDepTimeSharingWMPAINT1999999.m_limitDnPr)
                            ptr->m_D2dWndDepTimeSharingWMPAINT1999999.m_limitDnPr = des[i].m_cl;
                    }
                    int32_t temp = ptr->m_D2dWndDepTimeSharingWMPAINT1999999.m_limitUpPr - des[0].m_cl;
                    if ((des[0].m_cl - ptr->m_D2dWndDepTimeSharingWMPAINT1999999.m_limitDnPr) > temp) {
                        temp = des[0].m_cl - ptr->m_D2dWndDepTimeSharingWMPAINT1999999.m_limitDnPr;
                    }
                    temp += 100;
                    ptr->m_D2dWndDepTimeSharingWMPAINT1999999.m_limitUpPr = ptr->m_D2dWndDepTimeSharingWMPAINT1999999.m_preCl + temp;
                    ptr->m_D2dWndDepTimeSharingWMPAINT1999999.m_limitDnPr = ptr->m_D2dWndDepTimeSharingWMPAINT1999999.m_preCl - temp;
                    ptr->m_D2dWndDepTimeSharingWMPAINT1999999.m_volMax += 0.1 * ptr->m_D2dWndDepTimeSharingWMPAINT1999999.m_volMax;
                    ptr->m_D2dWndDepTimeSharingWMPAINT1999999.m_vecIntMinuteBar.swap(des);
                    ptr->m_D2dWndDepTimeSharingWMPAINT1999999.m_d2dWndDep = &(ptr->m_D2dWndDep);
                }
            });
        }
        return 1;
    }
    case WM_PAINT: {
        // PAINTSTRUCT ps;
        // HDC hDC = BeginPaint(hWnd, &ps);
        // SetBkMode(hDC, TRANSPARENT);
        RECT rc;
        GetClientRect(hWnd, &rc);
        QILD2D::D2dWndDepMain* ptr = reinterpret_cast<QILD2D::D2dWndDepMain*>(static_cast<LONG_PTR>(GetWindowLongPtr(hWnd, GWLP_USERDATA)));
        ptr->m_D2dWndDep.m_pD2D1HwndRenderTarget->BeginDraw();
        // All painting occurs here, between BeginPaint and EndPaint.
        ptr->m_D2dWndDep.m_pD2D1HwndRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));
        if (false) {
            ptr->m_D2dWndDepTimeSharingWMPAINT1999999.m_xStart = 0;
            ptr->m_D2dWndDepTimeSharingWMPAINT1999999.m_yStart = 0;
            ptr->m_D2dWndDepTimeSharingWMPAINT1999999.m_xWidth = (rc.right - rc.left);
            ptr->m_D2dWndDepTimeSharingWMPAINT1999999.m_yHeight = (rc.bottom - rc.top);
            ptr->m_D2dWndDepTimeSharingWMPAINT1999999.operator()();
        } else {
            int32_t nVert = 3; // 垂直
            int32_t nHorz = 4; // 水平
            for (int32_t i { 0 }; i < nHorz; ++i) {
                for (int32_t j { 0 }; j < nVert; ++j) {
                    ptr->m_D2dWndDepTimeSharingWMPAINT1999999.m_xStart = 0 + i * (rc.right - rc.left) / nHorz;
                    ptr->m_D2dWndDepTimeSharingWMPAINT1999999.m_yStart = 0 + j * (rc.bottom - rc.top) / nVert;
                    ptr->m_D2dWndDepTimeSharingWMPAINT1999999.m_xWidth = (rc.right - rc.left) / nHorz;
                    ptr->m_D2dWndDepTimeSharingWMPAINT1999999.m_yHeight = (rc.bottom - rc.top) / nVert;
                    ptr->m_D2dWndDepTimeSharingWMPAINT1999999.operator()();
                }
            }
        }
        // FillRect(hDC, &ps.rcPaint, //(HBRUSH)GetStockObject(WHITE_BRUSH));
        //     CreateSolidBrush(RGB((rand() % (255 + 1)), (rand() % (255 + 1)), (rand() % (255 + 1)))));
        ptr->m_D2dWndDep.m_pD2D1HwndRenderTarget->EndDraw();
        // EndPaint(hWnd, &ps);
        ValidateRect(hWnd, NULL);
        return 0;
    }
    case WM_SIZE: {
        QILD2D::D2dWndDepMain* ptr = reinterpret_cast<QILD2D::D2dWndDepMain*>(static_cast<LONG_PTR>(GetWindowLongPtr(hWnd, GWLP_USERDATA)));
        D2D1_SIZE_U size = D2D1::SizeU(LOWORD(lParam), HIWORD(lParam));
        ptr->m_D2dWndDep.m_pD2D1HwndRenderTarget->Resize(size);
        InvalidateRect(hWnd, NULL, FALSE);
        return 0;
    }
    case WM_COMMAND: {
        auto hWndCtrl = lParam; // 发送WM_COMMAND的子窗口句柄
        auto wNotifyCode = HIWORD(wParam); // 菜单消息的通知码为0，加速键消息的通知码为1。
        auto wID = LOWORD(wParam);
        switch (wID) {
        case WNDMAIN_HMENU_FEATURE_LIMITPERIOD300DESCRIPTION: {
            HWND hWndLimitPeriodText = CreateWindow(
                TEXT("WndLimitPeriodText"), // 窗口类注册名称
                TEXT("创业板周期"), // 窗口标题
                WS_VISIBLE | WS_OVERLAPPEDWINDOW, // 标准交互
                CW_USEDEFAULT, // 初始x坐标
                CW_USEDEFAULT, // 初始y坐标
                CW_USEDEFAULT, // 初始x方向尺寸
                CW_USEDEFAULT, // 初始y方向尺寸
                hWnd, // 父窗口句柄
                NULL /* Must be NULL! */, // 主窗口菜单句柄、子窗口窗口标识（整形、父窗口内唯一）
                GetModuleHandle(NULL), // 程序实例句柄
                NULL // 窗口创建参数
            );
            QILD2D::D2dWndDepLimitPeriodText* ptr = reinterpret_cast<QILD2D::D2dWndDepLimitPeriodText*>(static_cast<LONG_PTR>(GetWindowLongPtr(hWnd, GWLP_USERDATA)));
            break;
        }
        case WNDMAIN_HMENU_FEATURE_LIMITPERIOD300TIMESHARING: {
            HWND hWndLimitPeriodText = CreateWindow(
                TEXT("WndLimitPeriodTimeSharing"), // 窗口类注册名称
                TEXT("创业板周期"), // 窗口标题
                WS_VISIBLE | WS_OVERLAPPEDWINDOW, // 标准交互
                CW_USEDEFAULT, // 初始x坐标
                CW_USEDEFAULT, // 初始y坐标
                CW_USEDEFAULT, // 初始x方向尺寸
                CW_USEDEFAULT, // 初始y方向尺寸
                hWnd, // 父窗口句柄
                NULL /* Must be NULL! */, // 主窗口菜单句柄、子窗口窗口标识（整形、父窗口内唯一）
                GetModuleHandle(NULL), // 程序实例句柄
                NULL // 窗口创建参数
            );
            QILD2D::D2dWndDepLimitPeriodTimeSharing* ptr = reinterpret_cast<QILD2D::D2dWndDepLimitPeriodTimeSharing*>(static_cast<LONG_PTR>(GetWindowLongPtr(hWnd, GWLP_USERDATA)));
            break;
        }
        case WNDMAIN_HMENU_HELP_ABOUT: {
            HWND hWndAbout = CreateWindow(
                TEXT("WndAbout"), // 窗口类注册名称
                TEXT("关于"), // 窗口标题
                WS_VISIBLE | WS_OVERLAPPEDWINDOW, // 标准交互
                CW_USEDEFAULT, // 初始x坐标
                CW_USEDEFAULT, // 初始y坐标
                CW_USEDEFAULT, // 初始x方向尺寸
                CW_USEDEFAULT, // 初始y方向尺寸
                hWnd, // 父窗口句柄
                NULL /* Must be NULL! */, // 主窗口菜单句柄、子窗口窗口标识（整形、父窗口内唯一）
                GetModuleHandle(NULL), // 程序实例句柄
                NULL // 窗口创建参数
            );
            QILD2D::D2dWndDepAbout* ptr = reinterpret_cast<QILD2D::D2dWndDepAbout*>(static_cast<LONG_PTR>(GetWindowLongPtr(hWnd, GWLP_USERDATA)));
            break;
        }
        default:
            break;
        }
        return 0;
    }
    default:
        break;
    }
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

}
