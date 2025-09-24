// Copyright (c) 2025-present Mason Zhao MasonSZhao@qq.com

// QilD2d.h : Include file for standard system include files, or project specific include files.

#pragma once

#include <windows.h> // <windows.h> should be in front of <commctrl.h>
#include <windowsx.h>

#include <commctrl.h>

#include <d2d1_3.h>
#pragma comment(lib, "d2d1.lib")
#include <dwrite_3.h>
#pragma comment(lib, "dwrite.lib")

#include "..\..\QilHost\include\QilHostFileTd.h"
#include "..\..\QilHost\include\QilHostSecurity.h"
#include "..\..\QilHost\include\QilHostSecurityS.h"
#include "..\..\QilHost\include\QilHostTech.h"

#include <iostream>
#include <thread>
#include <vector>

namespace QILD2D {

struct D2dWndIndep {
    // Factory
    static ID2D1Factory5* s_pD2D1Factory;
    static IDWriteFactory7* s_pDWriteFactory;
    static IDWriteTextFormat* s_pDWriteTextFormat16;
    static IDWriteTextFormat* s_pDWriteTextFormat14;

    // Font
    static IDWriteFontCollection1* s_pDWriteFontCollection;
    static IDWriteFontSetBuilder2* s_pDWriteFontSetBuilder;
    static IDWriteFontSet* s_pDWriteFontSet;
    static ID2D1StrokeStyle* s_pD2D1StrokeStyle;

    // Helper
    template <class Interface>
    static inline void SafeRelease(Interface** ppInterfaceToRelease)
    {
        if (*ppInterfaceToRelease != NULL) {
            (*ppInterfaceToRelease)->Release();
            (*ppInterfaceToRelease) = NULL;
        }
    }

    // Cout
    static HANDLE s_hCout;
};

struct D2dWndDep {
    ID2D1HwndRenderTarget* m_pD2D1HwndRenderTarget = NULL;

    ID2D1SolidColorBrush* m_pD2DSolidColorBrushBlack = NULL;
    ID2D1SolidColorBrush* m_pD2DSolidColorBrushLightGray = NULL;
    ID2D1SolidColorBrush* m_pD2DSolidColorBrushGray = NULL;
    ID2D1SolidColorBrush* m_pD2DSolidColorBrushRed = NULL;
    ID2D1SolidColorBrush* m_pD2DSolidColorBrushGreen = NULL;
};

struct D2dWndDepMain {
    D2dWndDep m_D2dWndDep;
    struct {
        std::vector<QILHOST::IntMinuteBar> m_vecMinuteBar;
        int32_t m_preCl;
        int32_t m_limitUpPr;
        int32_t m_limitDnPr;
        int64_t m_volMax;
    } m_D2dWndDepMinuteBar1999999;
    static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};

struct D2dWndDepTimeSharing {
    struct WMPAINT {
        D2dWndDep* m_d2dWndDep;
        int32_t m_preCl;
        int32_t m_limitUpPr;
        int32_t m_limitDnPr;
        int64_t m_volMax;
        std::vector<QILHOST::IntMinuteBar>* m_vecIntMinuteBar;
        float m_xStart;
        float m_yStart;
        float m_xWidth;
        float m_yHeight;
        bool m_hasTop { false };
        bool m_hasLeft { false };
        bool m_hasRight { false };
        bool m_hasBottom { false };
        void operator()();
    };
};

}
