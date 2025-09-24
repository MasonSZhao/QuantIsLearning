// Copyright (c) 2025-present Mason Zhao MasonSZhao@qq.com

#pragma once

#include <array>
#include <cstdint>

namespace QILHOST {
/**
 * @brief 计算日期时间。
 */
struct TechDateTime {

    static inline bool isLeapYear(int32_t year)
    {
        return ((year % 4 == 0) && (year % 100 != 0) || year % 400 == 0);
    }

    static int32_t calcLastDayOfYearMonth(int32_t year, int32_t month);

    static std::array<int32_t, 3> addDay(int32_t year, int32_t month, int32_t day);

    static std::array<int32_t, 3> addDays(int32_t year, int32_t month, int32_t day, int32_t count);

    /*
     * Kim larsen calculation formula 基姆拉尔森计算公式
     * Zeller calculation formula 蔡勒计算公式
     * 0 Sunday
     * 1 Monday
     * 2 Tuesday
     * 3 Wednesday
     * 4 Thursday
     * 5 Friday
     * 6 Saturday
     */
    static int32_t calcWDayofDate(int32_t year, int32_t month, int32_t day);
};

/**
 * @brief 计算涨跌停价格。
 */
struct TechLimitCur1 {
    /**
     * @brief Given the price in the base period, calculates the Limit Up or Limit Down price in the current period.
     * @param val The price in the base period.
     * @param limit
     *     - 105: calculates the 5% limit up price.
     *     - 110: calculates the 10% limit up price.
     *     - 120: calculates the 20% limit up price.
     *     - 130: calculates the 30% limit up price.
     *     - 95: calculates the 5% limit down price.
     *     - 90: calculates the 10% limit down price.
     *     - 80: calculates the 20% limit down price.
     *     - 70: calculates the 30% limit down price.
     * @return
     */
    static int32_t int32(int32_t val, int32_t limit);

    /**
     * @brief Given the price in the base period, calculates the Limit Up-Limit Down price in the current period.
     * @param val The price in the base period.
     * @param limit
     *     - 1.05: calculates the 5% limit up price.
     *     - 1.1: calculates the 10% limit up price.
     *     - 1.2: calculates the 20% limit up price.
     *     - 0.95: calculates the 5% limit down price.
     *     - 0.90: calculates the 10% limit down price.
     *     - 0.80: calculates the 20% limit down price.
     * @return The Limit Up-Limit Down price in the current period.
     */
    static double dbl(double val, double limit);
};

/**
 * @brief 判断涨跌停类型。
 */
struct TechLimitType0 {
    static int32_t int32(const char* exCode);
    static double dbl(const char* exCode);
};

}
