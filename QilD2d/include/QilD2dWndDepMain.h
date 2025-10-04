// Copyright (c) 2025-present Mason Zhao MasonSZhao@qq.com

#pragma once

#include "..\..\QilHost\include\QilHostSecurity.h"
#include "QilD2dWndDep.h"
#include "QilD2dWndDepAbout.h"
#include "QilD2dWndDepLimitPeriod.h"
#include "QilD2dWndDepTimeSharing.h"
#include "QilD2dWndIndep.h"
#include <vector>

namespace QILD2D {

struct D2dWndDepMain {
    bool m_madeLeftInitDisplayDisclaimer = false;

    D2dWndDep m_D2dWndDep;
    D2dWndDepTimeSharing::WMPAINT m_D2dWndDepTimeSharingWMPAINT1999999;
    static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};

}
