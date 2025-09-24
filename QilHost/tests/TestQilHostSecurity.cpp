// Copyright (c) 2025-present Mason Zhao MasonSZhao@qq.com

#include "..\include\QilHostSecurity.h"

#include <iostream>

/*
 * @details
 *     https://github.com/catchorg/Catch2/blob/devel/docs/own-main.md
 */
#include <catch2/catch_test_macros.hpp>

SCENARIO("Test Pod", "[Test Pod]")
{
    if (true) {
        CHECK(std::is_pod<QILHOST::TD::FltDayBar>::value);
        CHECK(std::is_pod<QILHOST::TD::FltMinuteBar>::value);

        CHECK(std::is_pod<QILHOST::IntDateBar>::value);
        CHECK(std::is_pod<QILHOST::IntMinuteBar>::value);
        CHECK(std::is_pod<QILHOST::IntQuote2>::value);
        CHECK(std::is_pod<QILHOST::IntQuote5>::value);
        CHECK(std::is_pod<QILHOST::IntQuoteDiff>::value);
    }
}
