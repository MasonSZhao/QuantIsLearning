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
