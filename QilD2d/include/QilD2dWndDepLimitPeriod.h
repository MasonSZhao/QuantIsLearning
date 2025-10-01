// Copyright (c) 2025-present Mason Zhao MasonSZhao@qq.com

#pragma once

#include "QilD2dWndDep.h"
#include "QilD2dWndDepTimeSharing.h"
#include <string>
#include <vector>

namespace QILD2D {

struct D2dWndDepLimitPeriodText {
    std::vector<std::wstring> m_vecLine;
    float m_maxWidthVecPDWriteTextLayout = 0.f;
    std::vector<IDWriteTextLayout*> m_vecPDWriteTextLayout;

    D2dWndDep m_D2dWndDep;
    static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};

struct D2dWndDepLimitPeriodTimeSharing {
    int32_t m_nVert = 3; // 垂直
    int32_t m_nHorz = 4; // 水平

    std::vector<std::vector<std::vector<QILD2D::D2dWndDepTimeSharing::WMPAINT>>> m_vecVecVecD2dWndDepTimeSharing;

    D2dWndDep m_D2dWndDep;
    static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};

}
