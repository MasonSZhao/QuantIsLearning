// Copyright (c) 2025-present Mason Zhao MasonSZhao@qq.com

#include "..\include\QilHostFileTd.h"
#include "..\include\QilHostSecurity.h"
#include "..\include\QilHostSecurityS.h"
#include "..\include\QilHostTech.h"

#include <algorithm>
#include <deque>
#include <iostream>
#include <mutex>

/*
 * @details
 *     https://github.com/catchorg/Catch2/blob/devel/docs/own-main.md
 */
#include <catch2/catch_test_macros.hpp>

#include <stdexcept>

SCENARIO("TechLimit", "[TechLimit]")
{
    GIVEN("Function TechLimitCur1")
    {
        GIVEN("sz300313Cl")
        {
            std::vector<double> sz300313Cl {
                5.83 /* 0*/,
                6.41 /* 1*/,
                7.05 /* 2*/,
                7.76 /* 3*/,
                9.31 /* 4*/,
                11.17 /* 5*/,
                13.40 /* 6*/,
                16.08 /* 7*/,
                19.30 /* 8*/,
                23.16 /* 9*/,
                24.07 /*10*/,
                28.88 /*11*/,
                34.66 /*12*/,
                27.73 /*13*/,
                24.25 /*14*/
            };
            std::vector<double> post {
                std::numeric_limits<double>::quiet_NaN(), // 0
                std::numeric_limits<double>::infinity(), // 1
                std::numeric_limits<double>::infinity(), // 2
                std::numeric_limits<double>::infinity(), // 3
                std::numeric_limits<double>::infinity(), // 4
                std::numeric_limits<double>::infinity(), // 5
                std::numeric_limits<double>::infinity(), // 6
                std::numeric_limits<double>::infinity(), // 7
                std::numeric_limits<double>::infinity(), // 8
                std::numeric_limits<double>::infinity(), // 9
                0.0392919, // 10 // (24.07 - 23.16) / 23.16
                std::numeric_limits<double>::infinity(), // 11
                std::numeric_limits<double>::infinity(), // 12
                -std::numeric_limits<double>::infinity(), // 13
                -0.125496, // 14 (24.25 - 27.73) / 27.73
            };
            WHEN("Calcualtes.")
            {
                THEN("The results should match.")
                {
                    if (true) {
                        for (size_t i { 0 }; i < 3; ++i) {
                            CHECK(QILHOST::TechLimitCur1::dbl(sz300313Cl[i], 1.1) == sz300313Cl[i + 1]);
                        }
                        for (size_t i { 3 }; i < 9; ++i) {
                            CHECK(QILHOST::TechLimitCur1::dbl(sz300313Cl[i], 1.2) == sz300313Cl[i + 1]);
                        }
                        CHECK(13.40 == QILHOST::TechLimitCur1::dbl(11.17, 1.2));
                    }
                }
            }
        }
    }
}

SCENARIO("Seq Calc Limit", "[Seq Calc Limit]")
{
    if (true) {
        std::array<char, 8> exCode { "1600376" };
        std::vector<QILHOST::IntDateBar> vecIntDateBar { QILHOST::TD::FileVecDayBar::int3264(exCode.data(), 50, true) };
        std::cout << std::boolalpha;
        for (size_t i { 1 }; i < vecIntDateBar.size(); ++i) {
            auto uplimitType = 100 + QILHOST::TechLimitType0::int32(exCode.data());
            std::cout
                << vecIntDateBar[i].m_date
                << '\t' << (QILHOST::TechLimitCur1::int32(vecIntDateBar[i - 1].m_cl, uplimitType) == vecIntDateBar[i].m_cl)
                << '\t' << QILHOST::TechLimitCur1::int32(vecIntDateBar[i - 1].m_cl, uplimitType)
                << '\t' << vecIntDateBar[i].m_cl << std::endl;
        }
    }
}

SCENARIO("Limit Period 300", "[Limit Period 300]")
{
    {
        int32_t startDate;
        {
            std::vector<QILHOST::IntMinuteBar> vecIntMinuteBar { QILHOST::TD::FileVecMinuteBar::int3264("1999999", 1, false) };
            startDate = vecIntMinuteBar[0].m_date;
        }
        {
            time_t time_tTime = time(nullptr);
            tm tmTime;
            localtime_s(&tmTime, &time_tTime);
            std::vector<QILHOST::TD::FltDayBar> vecFltDayBar { QILHOST::TD::FileVecDayBar::flt("1999999", (tmTime.tm_year + 1900 - startDate / 10000 + 1) * 365, true) };
            for (auto& e : vecFltDayBar) {
                if (e.m_date >= startDate) {
                    QILHOST::TimeSeriesCrossSector::s_vecDate.push_back(e.m_date);
                }
            }
        }
        QILHOST::TimeSeriesCrossSector::s_vecVecIntLimitUp.resize(QILHOST::TimeSeriesCrossSector::s_vecDate.size());
    }
    QILHOST::TD::FileVecExCode360::sz(false, true);
    {
        QILHOST::CrossSectorTimeSeries::s_vecVecIntDayBar.resize(QILHOST::VecExCode360::s_vecExCode.size());
    }
    {
        size_t idxPara { 0 };
        std::mutex mutIdx;
        std::vector<std::jthread> vecThread;
        for (auto idxThread { 0 }; idxThread < std::thread::hardware_concurrency() / 2; ++idxThread) {
            vecThread.emplace_back([&]() {
                std::vector<std::vector<QILHOST::IntLimitUpDn>> vecVecIntLimitUp;
                vecVecIntLimitUp.resize(QILHOST::TimeSeriesCrossSector::s_vecDate.size());
                while (true) {
                    size_t idxLocal;
                    {
                        std::unique_lock<std::mutex> lk(mutIdx);
                        idxLocal = idxPara;
                        if (!(idxLocal < QILHOST::VecExCode360::s_vecExCode.size())) {
                            break;
                        }
                        // std::cout << idxPara << std::endl;
                        ++idxPara;
                    }
                    {
                        std::vector<QILHOST::IntDateBar> vecIntDayBar { QILHOST::TD::FileVecDayBar::int3264(QILHOST::VecExCode360::s_vecExCode[idxLocal].data(), QILHOST::TimeSeriesCrossSector::s_vecDate.size() + 30, true) };
                        std::deque<QILHOST::IntLimitUpDn> deqLimit;
                        std::deque<int32_t> deqDate;
                        for (size_t idxVecIntDayBar { 1 }; idxVecIntDayBar < vecIntDayBar.size(); ++idxVecIntDayBar) {
                            int32_t limitType = QILHOST::TechLimitType0::int32(QILHOST::VecExCode360::s_vecExCode[idxLocal].data());
                            if (QILHOST::TechLimitCur1::int32(vecIntDayBar[idxVecIntDayBar - 1].m_cl, 100 + limitType) == vecIntDayBar[idxVecIntDayBar].m_cl) {
                                QILHOST::IntLimitUpDn temp;
                                temp.m_preCl = vecIntDayBar[idxVecIntDayBar - 1].m_cl;
                                temp.m_idxVecExCode = idxLocal;
                                temp.m_idxVecIntDayBar = idxVecIntDayBar;
                                if (deqLimit.empty()) {
                                    temp.m_count = 1;
                                } else {
                                    if (deqLimit.back().m_idxVecIntDayBar + 1 == idxVecIntDayBar) {
                                        temp.m_count = deqLimit.back().m_count + 1;
                                    } else {
                                        temp.m_count = 1;
                                    }
                                }
                                deqLimit.push_back(temp);
                                deqDate.push_back(vecIntDayBar[idxVecIntDayBar].m_date);
                            }
                        }
                        while (!deqDate.empty()) {
                            if (deqDate.front() < QILHOST::TimeSeriesCrossSector::s_vecDate.front()) {
                                deqDate.pop_front();
                                deqLimit.pop_front();
                            } else {
                                break;
                            }
                        }
                        for (size_t idxVecDate { 0 }; idxVecDate < QILHOST::TimeSeriesCrossSector::s_vecDate.size(); ++idxVecDate) {
                            if (deqDate.empty()) {
                                break;
                            } else {
                                if (deqDate.front() == QILHOST::TimeSeriesCrossSector::s_vecDate[idxVecDate]) {
                                    vecVecIntLimitUp[idxVecDate].push_back(deqLimit.front());
                                    deqLimit.pop_front();
                                    deqDate.pop_front();
                                } else {
                                    continue;
                                }
                            }
                        }
                    }
                }
                {
                    std::unique_lock<std::mutex> lk(mutIdx);
                    for (size_t idxVecVecIntLimitUp { 0 }; idxVecVecIntLimitUp < vecVecIntLimitUp.size(); ++idxVecVecIntLimitUp) {
                        for (const auto& e : vecVecIntLimitUp[idxVecVecIntLimitUp]) {
                            QILHOST::TimeSeriesCrossSector::s_vecVecIntLimitUp[idxVecVecIntLimitUp].push_back(e);
                        }
                    }
                }
            });
        }
    }
    for (auto& e : QILHOST::TimeSeriesCrossSector::s_vecVecIntLimitUp) {
        std::sort(e.begin(), e.end(), [](const QILHOST::IntLimitUpDn& a, const QILHOST::IntLimitUpDn& b) {
            return a.m_count > b.m_count;
        });
    }
    if (true) {
        std::string empty { "          " };
        for (size_t idxTimeSeries { 0 }; idxTimeSeries < QILHOST::TimeSeriesCrossSector::s_vecDate.size(); ++idxTimeSeries) {
            std::cout << QILHOST::TimeSeriesCrossSector::s_vecDate[idxTimeSeries] << std::endl;
            for (const auto& e : QILHOST::TimeSeriesCrossSector::s_vecVecIntLimitUp[idxTimeSeries]) {
                for (int32_t idxCount { 0 }; idxCount < e.m_count; ++idxCount)
                    std::cout << empty;
                std::cout << QILHOST::VecExCode360::s_vecName[e.m_idxVecExCode].data() << '_' << e.m_count << std::endl;
            }
        }
    }
}