// Copyright (c) 2025-present Mason Zhao MasonSZhao@qq.com

#include "..\include\QilD2dWndDepLimitPeriod.h"

#include "..\..\QilHost\include\QilHostFileTd.h"
#include "..\..\QilHost\include\QilHostSecurityS.h"
#include "..\..\QilHost\include\QilHostTech.h"
#include "..\include\QilD2dWndIndep.h"
#include <algorithm>
#include <atlconv.h> // USES_CONVERSION, W2A, A2W
#include <deque>
#include <mutex>
#include <sstream>
#include <thread>
#include <vector>

namespace QILD2D {

LRESULT CALLBACK D2dWndDepLimitPeriodText::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg) {
    case WM_ERASEBKGND: {
        return true /*avoid flicker*/;
    }
    case WM_CLOSE: {
        QILD2D::D2dWndDepLimitPeriodText* ptr = reinterpret_cast<QILD2D::D2dWndDepLimitPeriodText*>(static_cast<LONG_PTR>(GetWindowLongPtr(hWnd, GWLP_USERDATA)));
        for (auto& e : ptr->m_vecPDWriteTextLayout)
            e->Release();
        QILD2D::D2dWndIndep::SafeRelease(&(ptr->m_D2dWndDep.m_pD2DSolidColorBrushGreen));
        QILD2D::D2dWndIndep::SafeRelease(&(ptr->m_D2dWndDep.m_pD2DSolidColorBrushRed));
        QILD2D::D2dWndIndep::SafeRelease(&(ptr->m_D2dWndDep.m_pD2DSolidColorBrushGray));
        QILD2D::D2dWndIndep::SafeRelease(&(ptr->m_D2dWndDep.m_pD2DSolidColorBrushLightGray));
        QILD2D::D2dWndIndep::SafeRelease(&(ptr->m_D2dWndDep.m_pD2DSolidColorBrushBlack));
        QILD2D::D2dWndIndep::SafeRelease(&(ptr->m_D2dWndDep.m_pD2D1HwndRenderTarget));
        delete ptr;
        ptr = nullptr;
        DestroyWindow(hWnd);
        return 0;
    }
    case WM_CREATE: {
        QILD2D::D2dWndDepLimitPeriodText* ptr = new QILD2D::D2dWndDepLimitPeriodText;
        SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(ptr));
        // 并行线程
        if (true) {
            std::vector<std::jthread> vecThread;
            // 并行线程
            vecThread.emplace_back([&]() {
                {
                    int32_t startDate;
                    {
                        std::vector<QILHOST::IntMinuteBar> vecIntMinuteBar { QILHOST::TD::FileVecMinuteBar::int3264("1999999", 1, false) };
                        startDate = vecIntMinuteBar[0].m_date;
                    }
                    {
                        time_t time_tTime = time(nullptr);
                        tm tmTime;
                        localtime_s(&tmTime, &time_tTime);
                        std::vector<QILHOST::TD::FltDayBar> vecFltDayBar { QILHOST::TD::FileVecDayBar::flt("1999999", (tmTime.tm_year + 1900 - startDate / 10000 + 1) * 365, true) };
                        for (auto& e : vecFltDayBar) {
                            if (e.m_date >= startDate) {
                                QILHOST::TimeSeriesCrossSector::s_vecDate.push_back(e.m_date);
                            }
                        }
                    }
                    QILHOST::TimeSeriesCrossSector::s_vecVecIntLimitUp.resize(QILHOST::TimeSeriesCrossSector::s_vecDate.size());
                }
                QILHOST::TD::FileVecExCode360::sz(false, true);
                {
                    QILHOST::CrossSectorTimeSeries::s_vecVecIntDayBar.resize(QILHOST::VecExCode360::s_vecExCode.size());
                }
                {
                    size_t idxPara { 0 };
                    std::mutex mutIdx;
                    std::vector<std::jthread> vecThread;
                    for (auto idxThread { 0 }; idxThread < std::thread::hardware_concurrency() / 2; ++idxThread) {
                        vecThread.emplace_back([&]() {
                            std::vector<std::vector<QILHOST::IntLimitUpDn>> vecVecIntLimitUp;
                            vecVecIntLimitUp.resize(QILHOST::TimeSeriesCrossSector::s_vecDate.size());
                            while (true) {
                                size_t idxLocal;
                                {
                                    std::unique_lock<std::mutex> lk(mutIdx);
                                    idxLocal = idxPara;
                                    if (!(idxLocal < QILHOST::VecExCode360::s_vecExCode.size())) {
                                        break;
                                    }
                                    // std::cout << idxPara << std::endl;
                                    ++idxPara;
                                }
                                {
                                    std::vector<QILHOST::IntDateBar> vecIntDayBar { QILHOST::TD::FileVecDayBar::int3264(QILHOST::VecExCode360::s_vecExCode[idxLocal].data(), QILHOST::TimeSeriesCrossSector::s_vecDate.size() + 30, true) };
                                    std::deque<QILHOST::IntLimitUpDn> deqLimit;
                                    std::deque<int32_t> deqDate;
                                    for (size_t idxVecIntDayBar { 1 }; idxVecIntDayBar < vecIntDayBar.size(); ++idxVecIntDayBar) {
                                        auto uplimitType = 100 + QILHOST::TechLimitType0::int32(QILHOST::VecExCode360::s_vecExCode[idxLocal].data());
                                        if (QILHOST::TechLimitCur1::int32(vecIntDayBar[idxVecIntDayBar - 1].m_cl, uplimitType) == vecIntDayBar[idxVecIntDayBar].m_cl) {
                                            QILHOST::IntLimitUpDn temp;
                                            temp.m_idxVecExCode = idxLocal;
                                            temp.m_idxVecIntDayBar = idxVecIntDayBar;
                                            if (deqLimit.empty()) {
                                                temp.m_count = 1;
                                            } else {
                                                if (deqLimit.back().m_idxVecIntDayBar + 1 == idxVecIntDayBar) {
                                                    temp.m_count = deqLimit.back().m_count + 1;
                                                } else {
                                                    temp.m_count = 1;
                                                }
                                            }
                                            deqLimit.push_back(temp);
                                            deqDate.push_back(vecIntDayBar[idxVecIntDayBar].m_date);
                                        }
                                    }
                                    while (!deqDate.empty()) {
                                        if (deqDate.front() < QILHOST::TimeSeriesCrossSector::s_vecDate.front()) {
                                            deqDate.pop_front();
                                            deqLimit.pop_front();
                                        } else {
                                            break;
                                        }
                                    }
                                    for (size_t idxVecDate { 0 }; idxVecDate < QILHOST::TimeSeriesCrossSector::s_vecDate.size(); ++idxVecDate) {
                                        if (deqDate.empty()) {
                                            break;
                                        } else {
                                            if (deqDate.front() == QILHOST::TimeSeriesCrossSector::s_vecDate[idxVecDate]) {
                                                vecVecIntLimitUp[idxVecDate].push_back(deqLimit.front());
                                                deqLimit.pop_front();
                                                deqDate.pop_front();
                                            } else {
                                                continue;
                                            }
                                        }
                                    }
                                }
                            }
                            {
                                std::unique_lock<std::mutex> lk(mutIdx);
                                for (size_t idxVecVecIntLimitUp { 0 }; idxVecVecIntLimitUp < vecVecIntLimitUp.size(); ++idxVecVecIntLimitUp) {
                                    for (const auto& e : vecVecIntLimitUp[idxVecVecIntLimitUp]) {
                                        QILHOST::TimeSeriesCrossSector::s_vecVecIntLimitUp[idxVecVecIntLimitUp].push_back(e);
                                    }
                                }
                            }
                        });
                    }
                }
                for (auto& e : QILHOST::TimeSeriesCrossSector::s_vecVecIntLimitUp) {
                    std::sort(e.begin(), e.end(), [](const QILHOST::IntLimitUpDn& a, const QILHOST::IntLimitUpDn& b) {
                        return a.m_count > b.m_count;
                    });
                }
                if (true) {
                    std::string empty { "          " };
                    for (size_t idxTimeSeries { 0 }; idxTimeSeries < QILHOST::TimeSeriesCrossSector::s_vecDate.size(); ++idxTimeSeries) {
                        std::stringstream ss;
                        ss << QILHOST::TimeSeriesCrossSector::s_vecDate[idxTimeSeries];
                        for (const auto& e : QILHOST::TimeSeriesCrossSector::s_vecVecIntLimitUp[idxTimeSeries]) {
                            for (int32_t idxCount { 0 }; idxCount < e.m_count; ++idxCount)
                                ss << empty;
                            ss << QILHOST::VecExCode360::s_vecName[e.m_idxVecExCode].data() << '_' << e.m_count;
                        }
                        std::string str = ss.str();
                        USES_CONVERSION;
                        std::wstring temp = A2W(str.c_str());
                        ptr->m_vecPDWriteTextLayout.resize(ptr->m_vecPDWriteTextLayout.size() + 1);
                        // D2D1_SIZE_F renderTargetSize = ptr->m_D2dWndDep.m_pD2D1HwndRenderTarget->GetSize();
                        QILD2D::D2dWndIndep::s_pDWriteFactory->CreateTextLayout(temp.c_str(), temp.size(), QILD2D::D2dWndIndep::s_pDWriteTextFormat16, 0 /*可使用renderTargetSize*/, 0 /*可使用renderTargetSize*/, &ptr->m_vecPDWriteTextLayout.back());
                        ptr->m_vecPDWriteTextLayout.back()->SetWordWrapping(DWRITE_WORD_WRAPPING_NO_WRAP); // Set the word wrapping mode to DWRITE_WORD_WRAPPING_NO_WRAP
                        DWRITE_TEXT_METRICS textMetrics;
                        ptr->m_vecPDWriteTextLayout.back()->GetMetrics(&textMetrics);
                        float width = textMetrics.widthIncludingTrailingWhitespace;
                        if (width > ptr->m_maxWidthVecPDWriteTextLayout) {
                            ptr->m_maxWidthVecPDWriteTextLayout = width;
                        }
                    }
                }
            });
        }
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
        return 1;
    }
    case WM_PAINT: {
        // PAINTSTRUCT ps;
        // HDC hDC = BeginPaint(hWnd, &ps);
        // SetBkMode(hDC, TRANSPARENT);
        RECT rc;
        GetClientRect(hWnd, &rc);
        QILD2D::D2dWndDepLimitPeriodText* ptr = reinterpret_cast<QILD2D::D2dWndDepLimitPeriodText*>(static_cast<LONG_PTR>(GetWindowLongPtr(hWnd, GWLP_USERDATA)));
        ptr->m_D2dWndDep.m_pD2D1HwndRenderTarget->BeginDraw();
        // All painting occurs here, between BeginPaint and EndPaint.
        ptr->m_D2dWndDep.m_pD2D1HwndRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));
        auto idxVScroll = GetScrollPos(hWnd, SB_VERT); // 垂直
        auto idxHScroll = GetScrollPos(hWnd, SB_HORZ); // 水平
        if (true) {
            IDWriteTextLayout* pDWriteTextLayoutTemp;
            int32_t lineCount = std::ceil((rc.bottom - rc.top) / QILD2D::D2dWndIndep::s_lineHeight16);
            for (size_t i = 0; i < lineCount; ++i) {
                if (i + idxVScroll < ptr->m_vecPDWriteTextLayout.size()) {
                    ptr->m_D2dWndDep.m_pD2D1HwndRenderTarget->DrawTextLayout(D2D1::Point2F(0 - idxHScroll, i * QILD2D::D2dWndIndep::s_lineHeight16), ptr->m_vecPDWriteTextLayout[i + idxVScroll], ptr->m_D2dWndDep.m_pD2DSolidColorBrushBlack);
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
    // https://learn.microsoft.com/en-us/windows/win32/controls/scroll-text-in-scroll-bars
    case WM_SIZE: {
        QILD2D::D2dWndDepLimitPeriodText* ptr = reinterpret_cast<QILD2D::D2dWndDepLimitPeriodText*>(static_cast<LONG_PTR>(GetWindowLongPtr(hWnd, GWLP_USERDATA)));
        //  Set the vertical scrolling range and page size
        {
            SCROLLINFO si;
            si.cbSize = sizeof(si);
            si.fMask = SIF_RANGE | SIF_PAGE;
            si.nMin = 0;
            si.nMax = ptr->m_vecPDWriteTextLayout.size();
            si.nPage = std::ceil(HIWORD(lParam) /*height*/ / QILD2D::D2dWndIndep::s_lineHeight16);
            SetScrollInfo(hWnd, SB_VERT, &si, TRUE);
        }
        // Set the horizontal scrolling range and page size.
        {
            SCROLLINFO si;
            si.cbSize = sizeof(si);
            si.fMask = SIF_RANGE | SIF_PAGE;
            si.nMin = 0;
            si.nMax = ptr->m_maxWidthVecPDWriteTextLayout;
            si.nPage = LOWORD(lParam);
            SetScrollInfo(hWnd, SB_HORZ, &si, TRUE);
        }
        D2D1_SIZE_U size = D2D1::SizeU(LOWORD(lParam) /*width*/, HIWORD(lParam) /*height*/);
        ptr->m_D2dWndDep.m_pD2D1HwndRenderTarget->Resize(size);
        // InvalidateRect(hWnd, NULL, FALSE);
        return 0;
    }
    // https://learn.microsoft.com/en-us/windows/win32/controls/scroll-text-in-scroll-bars
    case WM_VSCROLL: {
        SCROLLINFO si;
        // Get all the vertial scroll bar information.
        si.cbSize = sizeof(si);
        si.fMask = SIF_ALL;
        GetScrollInfo(hWnd, SB_VERT, &si);
        switch (LOWORD(wParam)) {
        case SB_TOP:
            si.nPos = si.nMin;
            break; // User clicked the HOME keyboard key.
        case SB_BOTTOM:
            si.nPos = si.nMax;
            break; // User clicked the END keyboard key.
        case SB_LINEUP:
            si.nPos -= 1;
            break; // User clicked the top arrow.
        case SB_LINEDOWN:
            si.nPos += 1;
            break; // User clicked the bottom arrow.
        case SB_PAGEUP:
            si.nPos -= si.nPage;
            break; // User clicked the scroll bar shaft above the scroll box.
        case SB_PAGEDOWN:
            si.nPos += si.nPage;
            break; // User clicked the scroll bar shaft below the scroll box.
        case SB_THUMBTRACK:
            si.nPos = si.nTrackPos;
            break; // User dragged the scroll box.
        default:
            break;
        }
        // Set the position and then retrieve it.  Due to adjustments by Windows it may not be the same as the value set.
        si.fMask = SIF_POS;
        SetScrollInfo(hWnd, SB_VERT, &si, TRUE);
        GetScrollInfo(hWnd, SB_VERT, &si);
        InvalidateRect(hWnd, NULL, FALSE);
        return 0;
    }
    // https://learn.microsoft.com/en-us/windows/win32/controls/scroll-text-in-scroll-bars
    case WM_HSCROLL: {
        SCROLLINFO si;
        // Get all the horizontal scroll bar information.
        si.cbSize = sizeof(si);
        si.fMask = SIF_ALL;
        GetScrollInfo(hWnd, SB_HORZ, &si);
        switch (LOWORD(wParam)) {
        case SB_TOP:
            si.nPos = si.nMin;
            break; // User clicked the HOME keyboard key.
        case SB_BOTTOM:
            si.nPos = si.nMax;
            break; // User clicked the END keyboard key.
        case SB_LINEUP:
            si.nPos -= 1;
            break; // User clicked the top arrow.
        case SB_LINEDOWN:
            si.nPos += 1;
            break; // User clicked the bottom arrow.
        case SB_PAGEUP:
            si.nPos -= si.nPage;
            break; // User clicked the scroll bar shaft above the scroll box.
        case SB_PAGEDOWN:
            si.nPos += si.nPage;
            break; // User clicked the scroll bar shaft below the scroll box.
        case SB_THUMBTRACK:
            si.nPos = si.nTrackPos;
            break; // User dragged the scroll box.
        default:
            break;
        }
        // Set the position and then retrieve it.  Due to adjustments by Windows it may not be the same as the value set.
        si.fMask = SIF_POS;
        SetScrollInfo(hWnd, SB_HORZ, &si, TRUE);
        GetScrollInfo(hWnd, SB_HORZ, &si);
        InvalidateRect(hWnd, NULL, FALSE);
        return 0;
    }
    // https://learn.microsoft.com/en-us/windows/win32/controls/scroll-text-in-scroll-bars
    case WM_KEYDOWN: {
        // vertical
        {
            WORD wScrollNotify = 0xFFFF;
            switch (wParam) {
            case VK_UP:
                wScrollNotify = SB_LINEUP;
                break;
            case VK_PRIOR:
                wScrollNotify = SB_PAGEUP;
                break;
            case VK_NEXT:
                wScrollNotify = SB_PAGEDOWN;
                break;
            case VK_DOWN:
                wScrollNotify = SB_LINEDOWN;
                break;
            case VK_HOME:
                wScrollNotify = SB_TOP;
                break;
            case VK_END:
                wScrollNotify = SB_BOTTOM;
                break;
            }
            if (wScrollNotify != -1)
                SendMessage(hWnd, WM_VSCROLL, MAKELONG(wScrollNotify, 0), 0L);
        }
        // horizontal
        {
            WORD wScrollNotify = 0xFFFF;
            switch (wParam) {
            case VK_LEFT:
                wScrollNotify = SB_LINELEFT;
                break;
            case VK_RIGHT:
                wScrollNotify = SB_LINERIGHT;
                break;
            }
            if (wScrollNotify != -1)
                SendMessage(hWnd, WM_HSCROLL, MAKELONG(wScrollNotify, 0), 0L);
        }
        return 0;
    }
    case WM_MOUSEWHEEL: {
        SCROLLINFO si;
        // Get all the vertial scroll bar information.
        si.cbSize = sizeof(si);
        si.fMask = SIF_ALL;
        GetScrollInfo(hWnd, SB_VERT, &si);
        si.nPos -= GET_WHEEL_DELTA_WPARAM(wParam);
        // Set the position and then retrieve it.  Due to adjustment by Windows it may not be the same as the value set.
        si.fMask = SIF_POS;
        SetScrollInfo(hWnd, SB_VERT, &si, TRUE);
        GetScrollInfo(hWnd, SB_VERT, &si);
        InvalidateRect(hWnd, NULL, FALSE);
        return 0;
    }
    default:
        break;
    }
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

}
