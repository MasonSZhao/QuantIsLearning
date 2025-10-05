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

#define WNDMAIN_HMENU_SYS_SETDAYBAR (WM_USER + 1)
#define WNDMAIN_HMENU_SYS_SETMINUTEBAR (WM_USER + 2)
#define WNDMAIN_HMENU_SYS_SETMULTITHREAD (WM_USER + 3)
#define WNDMAIN_HMENU_SYS_COLOR_WHITE (WM_USER + 4)
#define WNDMAIN_HMENU_SYS_COLOR_BLACK (WM_USER + 5)
#define WNDMAIN_HMENU_SYS_COLOR_GRAY (WM_USER + 6)
#define WNDMAIN_HMENU_SYS_SETCOLORTHEME (WM_USER + 7)
#define WNDMAIN_HMENU_SYS_EXCONFIGFILE (WM_USER + 8)
#define WNDMAIN_HMENU_SYS_IMCONFIGFILE (WM_USER + 9)
#define WNDMAIN_HMENU_REVIEW_LIMITPERIOD300DESCRIPTION (WM_USER + 10)
#define WNDMAIN_HMENU_REVIEW_LIMITPERIOD300TIMESHARING (WM_USER + 11)
#define WNDMAIN_HMENU_REVIEW_LIMITPERIOD688DESCRIPTION (WM_USER + 12)
#define WNDMAIN_HMENU_REVIEW_LIMITPERIOD688TIMESHARING (WM_USER + 13)
#define WNDMAIN_HMENU_REVIEW_LIMITPERIODBJDESCRIPTION (WM_USER + 14)
#define WNDMAIN_HMENU_REVIEW_LIMITPERIODBJTIMESHARING (WM_USER + 15)
#define WNDMAIN_HMENU_REVIEW_LIMITPERIODSHSZDESCRIPTION (WM_USER + 16)
#define WNDMAIN_HMENU_REVIEW_LIMITPERIODSHSZTIMESHARING (WM_USER + 17)
#define WNDMAIN_HMENU_HELP_ABOUT (WM_USER + 18)
