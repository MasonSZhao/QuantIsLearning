// Copyright (c) 2025-present Mason Zhao MasonSZhao@qq.com

#include "..\include\QilD2dWndDepAbout.h"

namespace QILD2D {
std::wstring D2dWndDepAbout::s_softVer = L"- 软件版本\n\t0.0.1";
std::wstring D2dWndDepAbout::s_serveLic = L"- 服务协议\n\t感谢您使用本软件，本软件免费使用，您可通过访问 https://github.com/MasonSZhao/QuantIsLearning 查看软件源码。因本软件为用爱发电，如您方便请在Github上为本软件点亮Star支持。";
std::wstring D2dWndDepAbout::s_riskWarn = L"- 风险提示\n\t市场有风险，投资需谨慎。大道至简，正是因为炒股可能产生亏损，开户才不用托人找关系而轮的到你。在成年人的世界里，只有学习是最简单的事情，望诸公努力。";
std::wstring D2dWndDepAbout::s_disclaim = L"- 免责声明\n\t本软件所提供的任何信息旨在为投资者提供教育用途，均不构成投资建议；投资者使用本软件应独立进行判断并自担投资风险；因向本软件提供的公开数据和社区数据可能不同，本软件所提供的信息可能存在差异，本软件对这些数据、信息的准确性、完整性或可靠性不做任何保证，亦不对因使用本软件而引发的任何损失承担责任。";
std::wstring D2dWndDepAbout::s_pubDate = L"- 发布日期\n\t2025-10";
std::wstring D2dWndDepAbout::s_copyright = L"- 版权所有\n\tCopyright (C) 2025-present.";
std::wstring D2dWndDepAbout::s_contact = L"- 联系方式\n\tWeChat: MasonSZhao; E-mail: MasonSZhao@qq.com; QQ: 406079351.";

LRESULT CALLBACK D2dWndDepAbout::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg) {
    case WM_ERASEBKGND: {
        return true /*avoid flicker*/;
    }
    case WM_CLOSE: {
        QILD2D::D2dWndDepAbout* ptr = reinterpret_cast<QILD2D::D2dWndDepAbout*>(static_cast<LONG_PTR>(GetWindowLongPtr(hWnd, GWLP_USERDATA)));
        QILD2D::D2dWndIndep::SafeRelease(&(ptr->m_D2dWndDep.m_pD2DSolidColorBrushBlack));
        QILD2D::D2dWndIndep::SafeRelease(&(ptr->m_D2dWndDep.m_pD2D1HwndRenderTarget));
        delete ptr;
        ptr = nullptr;
        DestroyWindow(hWnd);
        return 0;
    }
    case WM_CREATE: {
        QILD2D::D2dWndDepAbout* ptr = new QILD2D::D2dWndDepAbout;
        SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(ptr));
        HRESULT hr = S_OK;
        if (SUCCEEDED(hr)) {
            RECT rc;
            GetClientRect(hWnd, &rc);
            hr = QILD2D::D2dWndIndep::s_pD2D1Factory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(hWnd, D2D1::SizeU(rc.right, rc.bottom)), &((*ptr).m_D2dWndDep.m_pD2D1HwndRenderTarget));
        }
        if (SUCCEEDED(hr)) {
            hr = (*ptr).m_D2dWndDep.m_pD2D1HwndRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &((*ptr).m_D2dWndDep.m_pD2DSolidColorBrushBlack));
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
        QILD2D::D2dWndDepAbout* ptr = reinterpret_cast<QILD2D::D2dWndDepAbout*>(static_cast<LONG_PTR>(GetWindowLongPtr(hWnd, GWLP_USERDATA)));
        ptr->m_D2dWndDep.m_pD2D1HwndRenderTarget->BeginDraw();
        // All painting occurs here, between BeginPaint and EndPaint.
        ptr->m_D2dWndDep.m_pD2D1HwndRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));

        {
            float y { 0 };
            {
                IDWriteTextLayout* pDWriteTextLayout;
                std::wstring temp { L"量化正在学习 Quant Is Learning" };
                {
                    QILD2D::D2dWndIndep::s_pDWriteFactory->CreateTextLayout(temp.c_str(), temp.size(), QILD2D::D2dWndIndep::s_pDWriteTextFormat16, rc.right, rc.bottom, &pDWriteTextLayout);
                    ptr->m_D2dWndDep.m_pD2D1HwndRenderTarget->DrawTextLayout(D2D1::Point2F(0, y), pDWriteTextLayout, ptr->m_D2dWndDep.m_pD2DSolidColorBrushBlack);
                    DWRITE_TEXT_METRICS metrics;
                    pDWriteTextLayout->GetMetrics(&metrics);
                    y += metrics.height + 10;
                    metrics.widthIncludingTrailingWhitespace;
                }
                pDWriteTextLayout->Release();
            }
            {
                IDWriteTextLayout* pDWriteTextLayout;
                {
                    QILD2D::D2dWndIndep::s_pDWriteFactory->CreateTextLayout(ptr->s_softVer.c_str(), ptr->s_softVer.size(), QILD2D::D2dWndIndep::s_pDWriteTextFormat16, rc.right, rc.bottom, &pDWriteTextLayout);
                    ptr->m_D2dWndDep.m_pD2D1HwndRenderTarget->DrawTextLayout(D2D1::Point2F(0, y), pDWriteTextLayout, ptr->m_D2dWndDep.m_pD2DSolidColorBrushBlack);
                    DWRITE_TEXT_METRICS metrics;
                    pDWriteTextLayout->GetMetrics(&metrics);
                    y += metrics.height + 10;
                    metrics.widthIncludingTrailingWhitespace;
                }
                pDWriteTextLayout->Release();
            }
            {
                IDWriteTextLayout* pDWriteTextLayout;
                {
                    QILD2D::D2dWndIndep::s_pDWriteFactory->CreateTextLayout(ptr->s_serveLic.c_str(), ptr->s_serveLic.size(), QILD2D::D2dWndIndep::s_pDWriteTextFormat16, rc.right, rc.bottom, &pDWriteTextLayout);
                    ptr->m_D2dWndDep.m_pD2D1HwndRenderTarget->DrawTextLayout(D2D1::Point2F(0, y), pDWriteTextLayout, ptr->m_D2dWndDep.m_pD2DSolidColorBrushBlack);
                    DWRITE_TEXT_METRICS metrics;
                    pDWriteTextLayout->GetMetrics(&metrics);
                    y += metrics.height + 10;
                    metrics.widthIncludingTrailingWhitespace;
                }
                pDWriteTextLayout->Release();
            }
            {
                IDWriteTextLayout* pDWriteTextLayout;
                {
                    QILD2D::D2dWndIndep::s_pDWriteFactory->CreateTextLayout(ptr->s_riskWarn.c_str(), ptr->s_riskWarn.size(), QILD2D::D2dWndIndep::s_pDWriteTextFormat16, rc.right, rc.bottom, &pDWriteTextLayout);
                    ptr->m_D2dWndDep.m_pD2D1HwndRenderTarget->DrawTextLayout(D2D1::Point2F(0, y), pDWriteTextLayout, ptr->m_D2dWndDep.m_pD2DSolidColorBrushBlack);
                    DWRITE_TEXT_METRICS metrics;
                    pDWriteTextLayout->GetMetrics(&metrics);
                    y += metrics.height + 10;
                    metrics.widthIncludingTrailingWhitespace;
                }
                pDWriteTextLayout->Release();
            }
            {
                IDWriteTextLayout* pDWriteTextLayout;
                {
                    QILD2D::D2dWndIndep::s_pDWriteFactory->CreateTextLayout(ptr->s_disclaim.c_str(), ptr->s_disclaim.size(), QILD2D::D2dWndIndep::s_pDWriteTextFormat16, rc.right, rc.bottom, &pDWriteTextLayout);
                    ptr->m_D2dWndDep.m_pD2D1HwndRenderTarget->DrawTextLayout(D2D1::Point2F(0, y), pDWriteTextLayout, ptr->m_D2dWndDep.m_pD2DSolidColorBrushBlack);
                    DWRITE_TEXT_METRICS metrics;
                    pDWriteTextLayout->GetMetrics(&metrics);
                    y += metrics.height + 10;
                    metrics.widthIncludingTrailingWhitespace;
                }
                pDWriteTextLayout->Release();
            }
            {
                IDWriteTextLayout* pDWriteTextLayout;
                {
                    QILD2D::D2dWndIndep::s_pDWriteFactory->CreateTextLayout(ptr->s_pubDate.c_str(), ptr->s_pubDate.size(), QILD2D::D2dWndIndep::s_pDWriteTextFormat16, rc.right, rc.bottom, &pDWriteTextLayout);
                    ptr->m_D2dWndDep.m_pD2D1HwndRenderTarget->DrawTextLayout(D2D1::Point2F(0, y), pDWriteTextLayout, ptr->m_D2dWndDep.m_pD2DSolidColorBrushBlack);
                    DWRITE_TEXT_METRICS metrics;
                    pDWriteTextLayout->GetMetrics(&metrics);
                    y += metrics.height + 10;
                    metrics.widthIncludingTrailingWhitespace;
                }
                pDWriteTextLayout->Release();
            }
            {
                IDWriteTextLayout* pDWriteTextLayout;
                {
                    QILD2D::D2dWndIndep::s_pDWriteFactory->CreateTextLayout(ptr->s_copyright.c_str(), ptr->s_copyright.size(), QILD2D::D2dWndIndep::s_pDWriteTextFormat16, rc.right, rc.bottom, &pDWriteTextLayout);
                    ptr->m_D2dWndDep.m_pD2D1HwndRenderTarget->DrawTextLayout(D2D1::Point2F(0, y), pDWriteTextLayout, ptr->m_D2dWndDep.m_pD2DSolidColorBrushBlack);
                    DWRITE_TEXT_METRICS metrics;
                    pDWriteTextLayout->GetMetrics(&metrics);
                    y += metrics.height + 10;
                    metrics.widthIncludingTrailingWhitespace;
                }
                pDWriteTextLayout->Release();
            }
            {
                IDWriteTextLayout* pDWriteTextLayout;
                {
                    QILD2D::D2dWndIndep::s_pDWriteFactory->CreateTextLayout(ptr->s_contact.c_str(), ptr->s_contact.size(), QILD2D::D2dWndIndep::s_pDWriteTextFormat16, rc.right, rc.bottom, &pDWriteTextLayout);
                    ptr->m_D2dWndDep.m_pD2D1HwndRenderTarget->DrawTextLayout(D2D1::Point2F(0, y), pDWriteTextLayout, ptr->m_D2dWndDep.m_pD2DSolidColorBrushBlack);
                    DWRITE_TEXT_METRICS metrics;
                    pDWriteTextLayout->GetMetrics(&metrics);
                    y += metrics.height + 10;
                    metrics.widthIncludingTrailingWhitespace;
                }
                pDWriteTextLayout->Release();
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
        QILD2D::D2dWndDepAbout* ptr = reinterpret_cast<QILD2D::D2dWndDepAbout*>(static_cast<LONG_PTR>(GetWindowLongPtr(hWnd, GWLP_USERDATA)));
        D2D1_SIZE_U size = D2D1::SizeU(LOWORD(lParam) /*width*/, HIWORD(lParam) /*height*/);
        ptr->m_D2dWndDep.m_pD2D1HwndRenderTarget->Resize(size);
        InvalidateRect(hWnd, NULL, FALSE);
        return 0;
    }
    default:
        break;
    }
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

}
