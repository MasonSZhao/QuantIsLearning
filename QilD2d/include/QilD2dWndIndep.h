// Copyright (c) 2025-present Mason Zhao MasonSZhao@qq.com

#pragma once

#include <d2d1_3.h>
#pragma comment(lib, "d2d1.lib")
#include <dwrite_3.h>
#pragma comment(lib, "dwrite.lib")

namespace QILD2D {

struct D2dWndIndep {
    // Factory
    static ID2D1Factory5* s_pD2D1Factory;
    static IDWriteFactory7* s_pDWriteFactory;
    static IDWriteTextFormat* s_pDWriteTextFormat16;
    static IDWriteTextFormat* s_pDWriteTextFormat14;

    static float s_lineHeight16;
    static float s_lineHeight14;

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

}

#define WNDMAIN_HMENU_FEATURE_LIMITPERIOD300DESCRIPTION (WM_USER + 1)
#define WNDMAIN_HMENU_FEATURE_LIMITPERIOD300TIMESHARING (WM_USER + 2)
#define WNDMAIN_HMENU_FEATURE_LIMITPERIOD688DESCRIPTION (WM_USER + 3)
#define WNDMAIN_HMENU_FEATURE_LIMITPERIOD688TIMESHARING (WM_USER + 4)
#define WNDMAIN_HMENU_FEATURE_LIMITPERIODBJDESCRIPTION (WM_USER + 5)
#define WNDMAIN_HMENU_FEATURE_LIMITPERIODBJTIMESHARING (WM_USER + 6)
