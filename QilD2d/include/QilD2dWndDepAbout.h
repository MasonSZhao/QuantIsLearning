// Copyright (c) 2025-present Mason Zhao MasonSZhao@qq.com

#pragma once

#include "QilD2dWndDep.h"
#include "QilD2dWndIndep.h"
#include <string>

namespace QILD2D {

struct D2dWndDepAbout {
    static std::wstring s_softVer; // 软件版本
    static std::wstring s_serveLic; // 服务协议
    static std::wstring s_riskWarn; // 风险提示
    static std::wstring s_disclaim; // 免责声明
    static std::wstring s_pubDate; // 发布日期
    static std::wstring s_copyright; // 版权所有
    static std::wstring s_contact; // 联系方式

    D2dWndDep m_D2dWndDep;
    static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};

}
