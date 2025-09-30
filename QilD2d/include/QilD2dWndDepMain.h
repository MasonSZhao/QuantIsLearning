// Copyright (c) 2025-present Mason Zhao MasonSZhao@qq.com

#pragma once

#include "..\..\QilHost\include\QilHostSecurity.h"
#include "QilD2dWndDep.h"
#include "QilD2dWndDepLimitPeriod.h"
#include "QilD2dWndDepTimeSharing.h"
#include "QilD2dWndIndep.h"
#include <vector>

namespace QILD2D {

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

}
