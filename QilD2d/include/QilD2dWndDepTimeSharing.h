// Copyright (c) 2025-present Mason Zhao MasonSZhao@qq.com

#pragma once

#include "..\..\QilHost\include\QilHostSecurity.h"
#include "QilD2dWndDep.h"
#include "QilD2dWndIndep.h"
#include <stdint.h>
#include <vector>

namespace QILD2D {

struct D2dWndDepTimeSharing {
    struct WMPAINT {
        D2dWndDep* m_d2dWndDep;
        int32_t m_preCl;
        int32_t m_limitUpPr;
        int32_t m_limitDnPr;
        int64_t m_volMax;
        std::vector<QILHOST::IntMinuteBar> m_vecIntMinuteBar;
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
