// Copyright (c) 2025-present Mason Zhao MasonSZhao@qq.com

#include "..\include\QilHostFileTd.h"
#include "..\include\QilHostSecurity.h"
#include "..\include\QilHostTech.h"

#include <iostream>

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

SCENARIO("Seq Calc Limit", "[Seq Calc Limit]")
{
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
