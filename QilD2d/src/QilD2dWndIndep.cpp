// Copyright (c) 2025-present Mason Zhao MasonSZhao@qq.com

#include "..\include\QilD2dWndIndep.h"

namespace QILD2D {

// Factory
ID2D1Factory5* D2dWndIndep::s_pD2D1Factory = NULL;
IDWriteFactory7* D2dWndIndep::s_pDWriteFactory = NULL;
IDWriteTextFormat* D2dWndIndep::s_pDWriteTextFormat16 = NULL;
IDWriteTextFormat* D2dWndIndep::s_pDWriteTextFormat14 = NULL;

float D2dWndIndep::s_lineHeight16 = 0;
float D2dWndIndep::s_lineHeight14 = 0;

// Font
IDWriteFontCollection1* D2dWndIndep::s_pDWriteFontCollection = NULL;
IDWriteFontSetBuilder2* D2dWndIndep::s_pDWriteFontSetBuilder = NULL;
IDWriteFontSet* D2dWndIndep::s_pDWriteFontSet = NULL;
ID2D1StrokeStyle* D2dWndIndep::s_pD2D1StrokeStyle = NULL;

HANDLE D2dWndIndep::s_hCout = NULL;

}
