// Copyright (c) 2025-present Mason Zhao MasonSZhao@qq.com

#include "..\include\QilHostTech.h"

#include <cmath>
#include <stdexcept>

namespace QILHOST {

int32_t TechDateTime::calcLastDayOfYearMonth(int32_t year, int32_t month)
{
    switch (month) {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        return 31;
    case 2:
        return 28 + TechDateTime::isLeapYear(year);
    case 4:
    case 6:
    case 9:
    case 11:
        return 30;
    default:
        throw std::runtime_error("Not Valid Month");
    }
}

std::array<int32_t, 3> TechDateTime::addDay(int32_t year, int32_t month, int32_t day)
{

    ++day;
    if (day > TechDateTime::calcLastDayOfYearMonth(year, month)) {
        day = 1;
        month++;
        if (month > 12) {
            month = 1;
            year++;
        }
    }
    return { year, month, day };
}

std::array<int32_t, 3> TechDateTime::addDays(int32_t year, int32_t month, int32_t day, int32_t count)
{
    for (int32_t i { 0 }; i < count; ++i) {
        if (day > TechDateTime::calcLastDayOfYearMonth(year, month)) {
            day = 1;
            month++;
            if (month > 12) {
                month = 1;
                year++;
            }
        }
    }
    return { year, month, day };
}

int32_t TechDateTime::calcWDayofDate(int32_t year, int32_t month, int32_t day)
{
    if ((1 == month) || (2 == month)) { // 将每年的1月、2月算为上一年的13月、14月
        int mm = (month == 1 ? 13 : 14);
        int yyyy = year - 1;
        return (day + 2 * mm + 3 * (mm + 1) / 5 + yyyy + yyyy / 4 - yyyy / 100 + yyyy / 400 + 1) % 7;
    } else
        return (day + 2 * month + 3 * (month + 1) / 5 + year + year / 4 - year / 100 + year / 400 + 1) % 7; // return (day + 1 + 2 * month + 3 * (month + 1) / 5 + year + (year >> 2) - year / 100 + year / 400) % 7;
}

int32_t TechLimitCur1::int32(int32_t val, int32_t limit)
{
    if (130 == limit) {
        return std::floor(val * (limit / 100.));
    } else if (70 == limit) {
        return std::ceil(val * (limit / 100.));
    } else {
        return std::round(val * (limit / 100.));
    }
}

double TechLimitCur1::dbl(double val, double limit)
{
    if (1.3 == limit) {
        return std::floor(val * limit * 100) / 100;
    } else if (0.7 == limit) {
        return std::ceil(val * limit * 100) / 100;
    } else {
        return std::round(val * limit * 100) / 100;
    }
}

int32_t TechLimitType0::int32(const char* exCode)
{
    if (('0' == exCode[0]) && ('0' == exCode[1])) {
        return 10;
    } else if (('0' == exCode[0]) && ('3' == exCode[1])) {
        return 20;
    } else if (('1' == exCode[0]) && ('0' == exCode[2])) {
        return 10;
    } else if (('1' == exCode[0]) && ('8' == exCode[2])) {
        return 20;
    } else {
        return 30;
    }
}

double TechLimitType0::dbl(const char* exCode)
{
    if (('0' == exCode[0]) && ('0' == exCode[1])) {
        return 0.1;
    } else if (('0' == exCode[0]) && ('3' == exCode[1])) {
        return 0.2;
    } else if (('1' == exCode[0]) && ('0' == exCode[2])) {
        return 0.1;
    } else if (('1' == exCode[0]) && ('8' == exCode[2])) {
        return 0.2;
    } else {
        return 0.3;
    }
}

}
