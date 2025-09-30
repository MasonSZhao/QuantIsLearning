// Copyright (c) 2025-present Mason Zhao MasonSZhao@qq.com

#include "..\include\QilD2dWndDepTimeSharing.h"

#include <string>

namespace QILD2D {

void D2dWndDepTimeSharing::WMPAINT::operator()()
{
    float widthLeft = 50;
    if (!m_hasLeft) {
        widthLeft = 0;
    }
    float widthPrVol = m_xWidth;
    float widthRight = 50;
    if (!m_hasRight) {
        widthRight = 0;
    }
    float heightPr = m_yHeight * 0.75;
    float heightVol = m_yHeight * 0.25;
    m_d2dWndDep->m_pD2D1HwndRenderTarget->DrawRectangle({ m_xStart + widthLeft + 0 /*left*/, m_yStart + 0 /*top*/, m_xStart + widthLeft + widthPrVol /*right*/, m_yStart + heightPr /*bottom*/ }, m_d2dWndDep->m_pD2DSolidColorBrushGray, 1);
    m_d2dWndDep->m_pD2D1HwndRenderTarget->DrawRectangle({ m_xStart + widthLeft + 0 /*left*/, m_yStart + heightPr /*top*/, m_xStart + widthLeft + widthPrVol /*right*/, m_yStart + heightPr + heightVol /*bottom*/ }, m_d2dWndDep->m_pD2DSolidColorBrushGray, 1);
    m_d2dWndDep->m_pD2D1HwndRenderTarget->DrawLine({ m_xStart + widthLeft + 0 /*x*/, m_yStart + heightPr * 0.25f /*y*/ }, { m_xStart + widthLeft + widthPrVol /*x*/, m_yStart + heightPr * 0.25f /*y*/ }, m_d2dWndDep->m_pD2DSolidColorBrushLightGray, 1);
    m_d2dWndDep->m_pD2D1HwndRenderTarget->DrawLine({ m_xStart + widthLeft + 0 /*x*/, m_yStart + heightPr * 0.5f /*y*/ }, { m_xStart + widthLeft + widthPrVol /*x*/, m_yStart + heightPr * 0.5f /*y*/ }, m_d2dWndDep->m_pD2DSolidColorBrushLightGray, 1);
    m_d2dWndDep->m_pD2D1HwndRenderTarget->DrawLine({ m_xStart + widthLeft + 0 /*x*/, m_yStart + heightPr * 0.75f /*y*/ }, { m_xStart + widthLeft + widthPrVol /*x*/, m_yStart + heightPr * 0.75f /*y*/ }, m_d2dWndDep->m_pD2DSolidColorBrushLightGray, 1);
    m_d2dWndDep->m_pD2D1HwndRenderTarget->DrawLine({ m_xStart + widthLeft + widthPrVol * 0.5f /*x*/, m_yStart + 0 /*y*/ }, { m_xStart + widthLeft + widthPrVol * 0.5f /*x*/, m_yStart + heightPr + heightVol /*y*/ }, m_d2dWndDep->m_pD2DSolidColorBrushLightGray, 1);
    m_d2dWndDep->m_pD2D1HwndRenderTarget->DrawLine({ m_xStart + widthLeft + widthPrVol * 0.25f /*x*/, m_yStart + 0 /*y*/ }, { m_xStart + widthLeft + widthPrVol * 0.25f /*x*/, m_yStart + heightPr + heightVol /*y*/ }, m_d2dWndDep->m_pD2DSolidColorBrushLightGray, 1);
    m_d2dWndDep->m_pD2D1HwndRenderTarget->DrawLine({ m_xStart + widthLeft + widthPrVol * 0.75f /*x*/, m_yStart + 0 /*y*/ }, { m_xStart + widthLeft + widthPrVol * 0.75f /*x*/, m_yStart + heightPr + heightVol /*y*/ }, m_d2dWndDep->m_pD2DSolidColorBrushLightGray, 1);
    if (true) {
        int32_t limitUpDnPr = m_limitUpPr - m_limitDnPr;
        {
            D2D1_POINT_2F p0 = { m_xStart + widthLeft, m_yStart + ((float)(m_limitUpPr - (*m_vecIntMinuteBar)[0].m_op) / (float)limitUpDnPr) * heightPr };
            D2D1_POINT_2F p1 = { m_xStart + widthLeft + widthPrVol / 240.f, m_yStart + ((float)(m_limitUpPr - (*m_vecIntMinuteBar)[0].m_cl) / (float)limitUpDnPr) * heightPr };
            m_d2dWndDep->m_pD2D1HwndRenderTarget->DrawLine(p0, p1, m_d2dWndDep->m_pD2DSolidColorBrushBlack, 1);
            for (size_t i { 1 }; i <= 239; ++i) {
                p0 = p1;
                p1.x += widthPrVol / 240.f;
                p1.y = m_yStart + ((float)(m_limitUpPr - (*m_vecIntMinuteBar)[i].m_cl) / (float)limitUpDnPr) * heightPr;
                m_d2dWndDep->m_pD2D1HwndRenderTarget->DrawLine(p0, p1, m_d2dWndDep->m_pD2DSolidColorBrushBlack, 1);
            }
        }
    }
    if (true) {
        D2D1_POINT_2F p0 = { m_xStart + widthLeft, m_yStart + heightPr + (1 - ((float)(*m_vecIntMinuteBar)[0].m_vol) / (float)m_volMax) * heightVol };
        D2D1_POINT_2F p1 = { m_xStart + widthLeft, m_yStart + heightPr + heightVol };
        m_d2dWndDep->m_pD2D1HwndRenderTarget->DrawLine(p0, p1, m_d2dWndDep->m_pD2DSolidColorBrushBlack, 1);
        for (size_t i { 1 }; i <= 239; ++i) {
            p0.x += widthPrVol / 240.f;
            p1.x += widthPrVol / 240.f;
            p0.y = m_yStart + heightPr + (1 - ((float)(*m_vecIntMinuteBar)[i].m_vol) / (float)m_volMax) * heightVol;
            m_d2dWndDep->m_pD2D1HwndRenderTarget->DrawLine(p0, p1, m_d2dWndDep->m_pD2DSolidColorBrushBlack, 1);
        }
    }
    if (false) {
        IDWriteTextLayout* pDWriteTextLayout0930;
        {
            std::wstring temp = L"09:30";
            QILD2D::D2dWndIndep::s_pDWriteFactory->CreateTextLayout(temp.c_str(), temp.size(), QILD2D::D2dWndIndep::s_pDWriteTextFormat14, 0 /*可使用renderTargetSize*/, 0 /*可使用renderTargetSize*/, &pDWriteTextLayout0930);
            pDWriteTextLayout0930->SetWordWrapping(DWRITE_WORD_WRAPPING_NO_WRAP); // Set the word wrapping mode to DWRITE_WORD_WRAPPING_NO_WRAP
        }
        IDWriteTextLayout* pDWriteTextLayout1030;
        {
            std::wstring temp = L"10:30";
            QILD2D::D2dWndIndep::s_pDWriteFactory->CreateTextLayout(temp.c_str(), temp.size(), QILD2D::D2dWndIndep::s_pDWriteTextFormat14, 0 /*可使用renderTargetSize*/, 0 /*可使用renderTargetSize*/, &pDWriteTextLayout1030);
            pDWriteTextLayout1030->SetWordWrapping(DWRITE_WORD_WRAPPING_NO_WRAP); // Set the word wrapping mode to DWRITE_WORD_WRAPPING_NO_WRAP
        }
        IDWriteTextLayout* pDWriteTextLayout1300;
        {
            std::wstring temp = L"13:00";
            QILD2D::D2dWndIndep::s_pDWriteFactory->CreateTextLayout(temp.c_str(), temp.size(), QILD2D::D2dWndIndep::s_pDWriteTextFormat14, 0 /*可使用renderTargetSize*/, 0 /*可使用renderTargetSize*/, &pDWriteTextLayout1300);
            pDWriteTextLayout1300->SetWordWrapping(DWRITE_WORD_WRAPPING_NO_WRAP); // Set the word wrapping mode to DWRITE_WORD_WRAPPING_NO_WRAP
        }
        IDWriteTextLayout* pDWriteTextLayout1400;
        {
            std::wstring temp = L"14:00";
            QILD2D::D2dWndIndep::s_pDWriteFactory->CreateTextLayout(temp.c_str(), temp.size(), QILD2D::D2dWndIndep::s_pDWriteTextFormat14, 0 /*可使用renderTargetSize*/, 0 /*可使用renderTargetSize*/, &pDWriteTextLayout1400);
            pDWriteTextLayout1400->SetWordWrapping(DWRITE_WORD_WRAPPING_NO_WRAP); // Set the word wrapping mode to DWRITE_WORD_WRAPPING_NO_WRAP
        }
        IDWriteTextLayout* pDWriteTextLayout1500;
        {
            std::wstring temp = L"15:00";
            QILD2D::D2dWndIndep::s_pDWriteFactory->CreateTextLayout(temp.c_str(), temp.size(), QILD2D::D2dWndIndep::s_pDWriteTextFormat14, 0 /*可使用renderTargetSize*/, 0 /*可使用renderTargetSize*/, &pDWriteTextLayout1500);
            pDWriteTextLayout1500->SetWordWrapping(DWRITE_WORD_WRAPPING_NO_WRAP); // Set the word wrapping mode to DWRITE_WORD_WRAPPING_NO_WRAP
        }
        m_d2dWndDep->m_pD2D1HwndRenderTarget->DrawTextLayout(D2D1::Point2F(m_xStart + widthLeft + 0, m_yStart + heightPr + heightVol), pDWriteTextLayout0930, m_d2dWndDep->m_pD2DSolidColorBrushBlack);
        pDWriteTextLayout0930->Release();
        m_d2dWndDep->m_pD2D1HwndRenderTarget->DrawTextLayout(D2D1::Point2F(m_xStart + widthLeft + widthPrVol * 0.25, m_yStart + heightPr + heightVol), pDWriteTextLayout1030, m_d2dWndDep->m_pD2DSolidColorBrushBlack);
        pDWriteTextLayout1030->Release();
        m_d2dWndDep->m_pD2D1HwndRenderTarget->DrawTextLayout(D2D1::Point2F(m_xStart + widthLeft + widthPrVol / 2, m_yStart + heightPr + heightVol), pDWriteTextLayout1300, m_d2dWndDep->m_pD2DSolidColorBrushBlack);
        pDWriteTextLayout1300->Release();
        m_d2dWndDep->m_pD2D1HwndRenderTarget->DrawTextLayout(D2D1::Point2F(m_xStart + widthLeft + widthPrVol * 0.75, m_yStart + heightPr + heightVol), pDWriteTextLayout1400, m_d2dWndDep->m_pD2DSolidColorBrushBlack);
        pDWriteTextLayout1400->Release();
        m_d2dWndDep->m_pD2D1HwndRenderTarget->DrawTextLayout(D2D1::Point2F(m_xStart + widthLeft + widthPrVol, m_yStart + heightPr + heightVol), pDWriteTextLayout1500, m_d2dWndDep->m_pD2DSolidColorBrushBlack);
        pDWriteTextLayout1500->Release();
    }
}

}
