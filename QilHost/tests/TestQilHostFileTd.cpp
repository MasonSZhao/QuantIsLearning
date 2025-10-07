// Copyright (c) 2025-present Mason Zhao MasonSZhao@qq.com

#include "..\include\QilHostFileTd.h"
#include "..\include\QilHostSecurity.h"
#include "..\include\QilHostSecurityS.h"

#include <iostream>

/*
 * @details
 *     https://github.com/catchorg/Catch2/blob/devel/docs/own-main.md
 */
#include <catch2/catch_test_macros.hpp>

SCENARIO("Seq Read DayFile", "[Seq Read DayFile]")
{
    GIVEN("File")
    {
        WHEN("Read flt")
        {
            if (true) {
                std::vector<QILHOST::TD::FltDayBar> vecFltDayBar { QILHOST::TD::FileVecDayBar::flt("1999999", 20, true) };
                if (false) {
                    for (size_t i { 0 }; i < vecFltDayBar.size(); ++i)
                        std::cout << vecFltDayBar[i] << std::endl;
                }
                CHECK(vecFltDayBar.size() == 20);
            }
        }
        WHEN("Read Int")
        {
            if (true) {
                std::vector<QILHOST::IntDateBar> vecIntDayBar { QILHOST::TD::FileVecDayBar::int3264("1999999", 20, true) };
                if (false) {
                    for (size_t i { 0 }; i < vecIntDayBar.size(); ++i)
                        std::cout << vecIntDayBar[i] << std::endl;
                }
                CHECK(vecIntDayBar.size() == 20);
            }
        }
    }
}

SCENARIO("Seq Read MinuteFile", "[Seq Read MinuteFile]")
{
    GIVEN("File")
    {
        WHEN("Read flt")
        {
            if (true) {
                std::vector<QILHOST::TD::FltMinuteBar> vecFltMinuteBar { QILHOST::TD::FileVecMinuteBar::flt("1999999", 20, true) };
                if (false) {
                    for (size_t i { 0 }; i < vecFltMinuteBar.size(); ++i)
                        std::cout << vecFltMinuteBar[i] << std::endl;
                }
                CHECK(vecFltMinuteBar.size() == 20);
            }
        }
        WHEN("Read Int")
        {
            if (true) {
                std::vector<QILHOST::IntMinuteBar> vecIntMinuteBar { QILHOST::TD::FileVecMinuteBar::int3264("1999999", 20, true) };
                if (false) {
                    for (size_t i { 0 }; i < vecIntMinuteBar.size(); ++i)
                        std::cout << vecIntMinuteBar[i] << std::endl;
                }
                CHECK(vecIntMinuteBar.size() == 20);
            }
        }
    }
}

SCENARIO("Date Read MinuteFile", "[Date Read MinuteFile]")
{
    GIVEN("File")
    {
        WHEN("Read flt")
        {
            WHEN("Read Set Date")
            {
                std::vector<std::vector<QILHOST::TD::FltMinuteBar>> vecVecFltMinuteBar = QILHOST::TD::FileVecMinuteBar::fltSetDate("1999999", std::set<int32_t> { 20250901, 20250924 });
                if (false) {
                    for (size_t i { 0 }; i < vecVecFltMinuteBar.size(); ++i) {
                        for (size_t j { 0 }; j < vecVecFltMinuteBar[i].size(); ++j)
                            std::cout << vecVecFltMinuteBar[i][j] << std::endl;
                        std::cout << std::endl
                                  << std::endl;
                    }
                }
                CHECK(vecVecFltMinuteBar[0].size() == 240);
                CHECK(vecVecFltMinuteBar[1].size() == 240);
            }
            WHEN("Read Date")
            {
                std::vector<QILHOST::TD::FltMinuteBar> vecFltMinuteBar { QILHOST::TD::FileVecMinuteBar::fltDate("1999999", 20250924) };
                if (false) {
                    for (size_t i { 0 }; i < vecFltMinuteBar.size(); ++i)
                        std::cout << vecFltMinuteBar[i] << std::endl;
                }
                CHECK(vecFltMinuteBar.size() == 240);
            }
        }
        WHEN("Read Int")
        {
            WHEN("Read Set Date")
            {
                std::vector<std::vector<QILHOST::IntMinuteBar>> vecVecIntMinuteBar = QILHOST::TD::FileVecMinuteBar::int3264SetDate("1999999", std::set<int32_t> { 20250901, 20250924 });
                if (true) {
                    for (size_t i { 0 }; i < vecVecIntMinuteBar.size(); ++i) {
                        for (size_t j { 0 }; j < vecVecIntMinuteBar[i].size(); ++j)
                            std::cout << vecVecIntMinuteBar[i][j] << std::endl;
                        std::cout << std::endl
                                  << std::endl;
                    }
                }
                CHECK(vecVecIntMinuteBar[0].size() == 240);
                CHECK(vecVecIntMinuteBar[1].size() == 240);
            }
            WHEN("Read Date")
            {
                std::vector<QILHOST::IntMinuteBar> vecIntMinuteBar { QILHOST::TD::FileVecMinuteBar::int3264Date("1999999", 20250924) };
                if (true) {
                    for (size_t i { 0 }; i < vecIntMinuteBar.size(); ++i)
                        std::cout << vecIntMinuteBar[i] << std::endl;
                }
                CHECK(vecIntMinuteBar.size() == 240);
            }
        }
    }
}

SCENARIO("Seq Read FileVecExCodeSz", "[Seq Read FileVecExCodeSz]")
{
    GIVEN("File360")
    {
        if (true) {
            QILHOST::TD::FileVecExCode360::sz(true, true);
            for (size_t i { 0 }; i < 5; ++i) {
                std::cout << QILHOST::VecExCode360::s_vecExCode[i].data() << '\t' << QILHOST::VecExCode360::s_vecName[i].data() << '\t' << QILHOST::VecExCode360::s_vecSpell[i].data() << std::endl;
            }
        }
    }
    GIVEN("File314")
    {
        if (true) {
            QILHOST::TD::FileVecExCode314::sz(true, true);
            for (size_t i { 0 }; i < 5; ++i) {
                std::cout << QILHOST::VecExCode314::s_vecExCode[i].data() << '\t' << QILHOST::VecExCode314::s_vecName[i].data() << '\t' << QILHOST::VecExCode314::s_vecSpell[i].data() << std::endl;
            }
        }
    }
}

SCENARIO("Seq Read FileVecExCodeSh", "[Seq Read FileVecExCodeSh]")
{
    GIVEN("File360")
    {
        if (true) {
            QILHOST::TD::FileVecExCode360::sh(true, true);
            for (size_t i { 0 }; i < 5; ++i) {
                std::cout << QILHOST::VecExCode360::s_vecExCode[i].data() << '\t' << QILHOST::VecExCode360::s_vecName[i].data() << '\t' << QILHOST::VecExCode360::s_vecSpell[i].data() << std::endl;
            }
        }
    }
    GIVEN("File314")
    {
        if (true) {
            QILHOST::TD::FileVecExCode314::sh(true, true);
            for (size_t i { 0 }; i < 5; ++i) {
                std::cout << QILHOST::VecExCode314::s_vecExCode[i].data() << '\t' << QILHOST::VecExCode314::s_vecName[i].data() << '\t' << QILHOST::VecExCode314::s_vecSpell[i].data() << std::endl;
            }
        }
    }
}

SCENARIO("Seq Read FileVecExCodeBj", "[Seq Read FileVecExCodeBj]")
{
    GIVEN("File360")
    {
        if (true) {
            QILHOST::TD::FileVecExCode360::bj();
            for (size_t i { 0 }; i < 5; ++i) {
                std::cout << QILHOST::VecExCode360::s_vecExCode[i].data() << '\t' << QILHOST::VecExCode360::s_vecName[i].data() << '\t' << QILHOST::VecExCode360::s_vecSpell[i].data() << std::endl;
            }
        }
    }
    GIVEN("File314")
    {
        if (true) {
            QILHOST::TD::FileVecExCode314::bj();
            for (size_t i { 0 }; i < 5; ++i) {
                std::cout << QILHOST::VecExCode314::s_vecExCode[i].data() << '\t' << QILHOST::VecExCode314::s_vecName[i].data() << '\t' << QILHOST::VecExCode314::s_vecSpell[i].data() << std::endl;
            }
        }
    }
}
