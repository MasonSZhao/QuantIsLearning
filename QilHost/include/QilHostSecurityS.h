// Copyright (c) 2025-present Mason Zhao MasonSZhao@qq.com

#pragma once

#include "QilHostSecurity.h"

#include <array>
#include <unordered_map>
#include <vector>

namespace QILHOST {

struct VecExCode360 {
    static std::vector<std::array<char, 8>> s_vecExCode; /** @brief The exchange code. 数字代码。*/
    static std::unordered_map<const char*, size_t, QILHOST::SeqCharHash, QILHOST::SeqCharEqualTo<>>* s_lutExCode;
    static std::vector<std::array<char, 9>> s_vecName;
    static std::vector<std::array<char, 5>> s_vecSpell;
};

struct VecExCode314 {
    static std::vector<std::array<char, 8>> s_vecExCode; /** @brief The exchange code. 数字代码。*/
    static std::unordered_map<const char*, size_t, QILHOST::SeqCharHash, QILHOST::SeqCharEqualTo<>>* s_lutExCode;
    static std::vector<std::array<char, 19>> s_vecName;
    static std::vector<std::array<char, 10>> s_vecSpell;
};

}
