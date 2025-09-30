// Copyright (c) 2025-present Mason Zhao MasonSZhao@qq.com

#pragma once

#include <d2d1_3.h>
#pragma comment(lib, "d2d1.lib")
#include <dwrite_3.h>
#pragma comment(lib, "dwrite.lib")

namespace QILD2D {

struct D2dWndDep {
    ID2D1HwndRenderTarget* m_pD2D1HwndRenderTarget = NULL;

    ID2D1SolidColorBrush* m_pD2DSolidColorBrushBlack = NULL;
    ID2D1SolidColorBrush* m_pD2DSolidColorBrushLightGray = NULL;
    ID2D1SolidColorBrush* m_pD2DSolidColorBrushGray = NULL;
    ID2D1SolidColorBrush* m_pD2DSolidColorBrushRed = NULL;
    ID2D1SolidColorBrush* m_pD2DSolidColorBrushGreen = NULL;
};

}
