// Copyright (c) 2025-present Mason Zhao MasonSZhao@qq.com

#include "..\include\QilHostSecurityS.h"

namespace QILHOST {

std::vector<std::array<char, 8>> VecExCode360::s_vecExCode;
std::unordered_map<const char*, size_t, QILHOST::SeqCharHash, QILHOST::SeqCharEqualTo<>>* VecExCode360::s_lutExCode;
std::vector<std::array<char, 9>> VecExCode360::s_vecName;
std::vector<std::array<char, 5>> VecExCode360::s_vecSpell;

std::vector<std::array<char, 8>> VecExCode314::s_vecExCode;
std::unordered_map<const char*, size_t, QILHOST::SeqCharHash, QILHOST::SeqCharEqualTo<>>* VecExCode314::s_lutExCode;
std::vector<std::array<char, 19>> VecExCode314::s_vecName;
std::vector<std::array<char, 10>> VecExCode314::s_vecSpell;

std::vector<std::vector<QILHOST::IntDateBar>> CrossSectorTimeSeries::s_vecVecIntDayBar;

std::vector<int32_t> TimeSeriesCrossSector::s_vecDate;

std::vector<std::vector<QILHOST::IntLimitUpDn>> TimeSeriesCrossSector::s_vecVecIntLimitUp;

int32_t TimeSeriesCrossSector::s_maxCount;

}
