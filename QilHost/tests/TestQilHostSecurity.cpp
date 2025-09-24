// Copyright (c) 2025-present Mason Zhao MasonSZhao@qq.com

#include "..\include\QilHostSecurity.h"

#include <array>
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

SCENARIO("Test Hash", "[Test Hash]")
{
    std::cout << "const char ptr" << std::endl;
    std::array<char, 8> lhs { "1999999" };
    std::cout << &lhs[0] << std::endl;
    std::array<char, 8> rhs { "1999999" };
    std::cout << &rhs[0] << std::endl;
    std::cout << std::endl;
    WHEN("hash")
    {
        THEN("Same contents' hash values should be the same.")
        {
            std::cout << "hash:" << std::endl;
            std::cout << std::hash<const char*> {}(&lhs[0]) << std::endl;
            std::cout << std::hash<const char*> {}(&rhs[0]) << std::endl;
            std::cout << QILHOST::SeqCharHash {}.operator()(&lhs[0]) << std::endl;
            std::cout << QILHOST::SeqCharHash {}.operator()(&rhs[0]) << std::endl;
            CHECK(QILHOST::SeqCharHash {}.operator()(&lhs[0]) == QILHOST::SeqCharHash {}.operator()(&rhs[0]));
            std::cout << std::endl;
        }
    }

    WHEN("equal_to")
    {
        THEN("Same contents' should be equal to each other.")
        {
            std::cout << "equal_to:" << std::endl;
            std::cout << std::boolalpha << std::equal_to<const char*> {}(&lhs[0], &rhs[0]) << std::endl;
            std::cout << std::boolalpha << QILHOST::SeqCharEqualTo {}.operator()(&lhs[0], &rhs[0]) << std::endl;
            CHECK(true == QILHOST::SeqCharEqualTo {}.operator()(&lhs[0], &rhs[0]));
            std::cout << std::endl;
        }
    }
}
