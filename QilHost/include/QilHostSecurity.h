// Copyright (c) 2025-present Mason Zhao MasonSZhao@qq.com

#pragma once

#include <cstdint>
#include <iostream>

namespace QILHOST {

/**
 * @brief hash() for std::unordered_map<const char*>. 字符数组哈希函数。
 * @details
 *     https://en.cppreference.com/w/cpp/container/unordered_map
 *
 *     https://en.cppreference.com/w/cpp/container/unordered_map/hash_function
 * @warning
 *     Don't use std::hash<const char*>, these functions examine the pointer (the memory address) rather than the content\n
 *     UnitTestStockConstChar.cpp has given some examples to show the differences.
 */
struct SeqCharHash {
    [[nodiscard]] int operator()(const char* a) const;
};

/**
 * @brief key_eq() for std::unordered_map<const char*>. 字符数组求等函数。
 * @details
 *     https://en.cppreference.com/w/cpp/container/unordered_map
 *
 *     https://en.cppreference.com/w/cpp/container/unordered_map/key_eq
 * @warning
 *     Don't use std::equal_to<const char*>, these functions examine the pointer (the memory address) rather than the content\n
 *     UnitTestStockConstChar.cpp has given some examples to show the differences.
 */
template <typename unsigned short count = 8>
struct SeqCharEqualTo {
    [[nodiscard]] bool operator()(const char* lhs, const char* rhs) const
    {
        // https://en.cppreference.com/w/cpp/string/byte/memcmp
        return 0 == memcmp /*return 0 if all count bytes of lhs and rhs are equal.*/ (lhs, rhs, count);
    }
};

namespace TD {
    /**
     * @brief Represents the candle bar. 日期K线。
     */
    /*POD*/ struct FltDayBar {
        /*I unsigned int->*/ uint32_t m_date; /**< @brief Represents the date of the candle bar.*/
        /*I unsigned int->*/ uint32_t m_op; /**< @brief Represents the open price of the candle bar.*/
        /*I unsigned int->*/ uint32_t m_hi; /**< @brief Represents the high price of the candle bar.*/
        /*I unsigned int->*/ uint32_t m_lo; /**< @brief Represents the low price of the candle bar.*/
        /*I unsigned int->*/ uint32_t m_cl; /**< @brief Represents the close price of the candle bar.*/
        /*f float->*/ float m_amo; /**< @brief Represents the amount of the candle bar.*/
        /*I unsigned int->*/ uint32_t m_vol; /**< @brief Represents the volume of the canlde bar.*/
        /*I unsigned int->*/ uint32_t m_res;
        friend std::ostream& operator<<(std::ostream& os, const FltDayBar& a);
        friend std::istream& operator>>(std::istream& is, FltDayBar& a);
    };

    /**
     * @brief Represents the candle bar. 分钟K线。
     */
    /*POD*/ struct FltMinuteBar {
        /*H unsigned short->*/ uint16_t m_date; /**< @brief Represents the date of the candle bar.*/
        /*H unsigned short->*/ uint16_t m_time; /**< @brief Represents the time of the candle bar.*/
        /*I unsigned int->*/ float m_op; /**< @brief Represents the open price of the candle bar.*/
        /*I unsigned int->*/ float m_hi; /**< @brief Represents the high price of the candle bar.*/
        /*I unsigned int->*/ float m_lo; /**< @brief Represents the low price of the candle bar.*/
        /*I unsigned int->*/ float m_cl; /**< @brief Represents the close price of the candle bar.*/
        /*f float->*/ float m_amo; /**< @brief Represents the amount of the candle bar.*/
        /*I unsigned int->*/ uint32_t m_vol; /**< @brief Represents the volume of the canlde bar.*/
        /*I unsigned int->*/ uint32_t m_res;
        uint32_t uintDate() const;
        uint32_t uintTime() const;
        friend std::ostream& operator<<(std::ostream& os, const FltMinuteBar& a);
        friend std::istream& operator>>(std::istream& is, FltMinuteBar& a);
    };

}

/**
 * @brief Represents the stock candle bar. 日期K线。
 */
/*POD*/ struct IntDateBar {
    /*unsigned int->*/ int32_t m_date; /**< @brief Represents the date of the candle bar.*/
    /*unsigned int->*/ int32_t m_op; /**< @brief Represents the open price of the candle bar.*/
    /*unsigned int->*/ int32_t m_hi; /**< @brief Represents the high price of the candle bar.*/
    /*unsigned int->*/ int32_t m_lo; /**< @brief Represents the low price of the candle bar.*/
    /*unsigned int->*/ int32_t m_cl; /**< @brief Represents the close price of the candle bar.*/
    /*unsigned int->*/ int32_t m_res;
    /*float->uint64_t*/ int64_t m_amo; /**< @brief Represents the amount of the candle bar.*/
    /*unsigned int->uint64_t*/ int64_t m_vol; /**< @brief Represents the volume of the canlde bar.*/
    friend std::ostream& operator<<(std::ostream& os, const IntDateBar& a);
};

/**
 * @brief Represents the candle bar. 分钟K线。
 */
/*POD*/ struct IntMinuteBar {
    int32_t m_date; /**< @brief Represents the date of the candle bar.*/
    int32_t m_time; /**< @brief Represents the time of the candle bar.*/
    /*unsigned int->*/ int32_t m_op; /**< @brief Represents the open price of the candle bar.*/
    /*unsigned int->*/ int32_t m_hi; /**< @brief Represents the high price of the candle bar.*/
    /*unsigned int->*/ int32_t m_lo; /**< @brief Represents the low price of the candle bar.*/
    /*unsigned int->*/ int32_t m_cl; /**< @brief Represents the close price of the candle bar.*/
    /*unsigned int->*/ int32_t m_res;
    /*float->*/ int64_t m_amo; /**< @brief Represents the amount of the candle bar.*/
    /*unsigned int->*/ int64_t m_vol; /**< @brief Represents the volume of the canlde bar.*/
    friend std::ostream& operator<<(std::ostream& os, const IntMinuteBar& a);
};

/**
 * @brief A stock quote is the price of a stock as quoted on an exchange. A basic quote for a specific stock provides information, such as its bid and ask price, last traded price, and volume traded. https://www.investopedia.com/terms/s/stockquote.asp
 */
/*POD*/ struct IntQuote2 {
    int32_t m_time;
    /*int->*/ int32_t m_pr1st; // 买一价 == 卖一价 == 匹配价 非0
    /*int->*/ int32_t m_vol1st; // 买一量 == 卖一量 == 匹配量 非0
    /*int->*/ int32_t m_vol2nd; // 买二量 == 未匹配量 == 0或非0
    friend std::ostream& operator<<(std::ostream& os, const IntQuote2& a);
};

/**
 * @brief A stock quote is the price of a stock as quoted on an exchange. A basic quote for a specific stock provides information, such as its bid and ask price, last traded price, and volume traded. https://www.investopedia.com/terms/s/stockquote.asp
 */
/*POD*/ struct IntQuote5 {
    int32_t m_date;
    int32_t m_time;

    /*int->*/ int32_t m_preCl; /*昨收/分*/

    /*int->*/ int32_t m_op; /*今开/分*/
    /*int->*/ int32_t m_hi; /*最高/分*/
    /*int->*/ int32_t m_lo; /*最低/分*/
    /*int->*/ int32_t m_cl; /*现价/分*/
    /*int->*/ int32_t m_vol; /*现量/手*/
    /*dbl->*/ int64_t m_amoCum; /*总额/元*/
    /*int->*/ int32_t m_volCum; /*总量/手*/
    /*int->*/ int32_t m_volAskCum; /*内盘/手*/
    /*int->*/ int32_t m_volBidCum; /*外盘/手*/

    /*int->*/ int32_t m_prAsk5th; /*卖五/分*/
    /*int->*/ int32_t m_volAsk5th; /*卖五/手*/
    /*int->*/ int32_t m_prAsk4th; /*卖四/分*/
    /*int->*/ int32_t m_volAsk4th; /*卖四/手*/
    /*int->*/ int32_t m_prAsk3rd; /*卖三/分*/
    /*int->*/ int32_t m_volAsk3rd; /*卖三/手*/
    /*int->*/ int32_t m_prAsk2nd; /*卖二/分*/
    /*int->*/ int32_t m_volAsk2nd; /*卖二/手*/
    /*int->*/ int32_t m_volAsk1st; /*卖一/手*/
    /*int->*/ int32_t m_prAsk1st; /*卖一/分*/
    /*int->*/ int32_t m_prBid1st; /*买一/分*/
    /*int->*/ int32_t m_volBid1st; /*买一/手*/
    /*int->*/ int32_t m_prBid2nd; /*买二/分*/
    /*int->*/ int32_t m_volBid2nd; /*买二/手*/
    /*int->*/ int32_t m_prBid3rd; /*买三/分*/
    /*int->*/ int32_t m_volBid3rd; /*买三/手*/
    /*int->*/ int32_t m_prBid4th; /*买四/分*/
    /*int->*/ int32_t m_volBid4th; /*买四/手*/
    /*int->*/ int32_t m_prBid5th; /*买五/分*/
    /*int->*/ int32_t m_volBid5th; /*买五/手*/

    friend std::ostream& operator<<(std::ostream& os, const IntQuote5& a);
};

/*POD*/ struct IntQuoteDiff {
    int32_t m_date;
    int32_t m_time;
    /*int32_t->*/ int32_t m_vol; /*现量/手*/
    /*int32_t->*/ int32_t m_pr; /*现价/分*/

    /*int32_t->*/ int32_t m_qty; /*现价/分*/
    /*int32_t->*/ int32_t m_bs; /*正买负卖*/

    /*int64_t->*/ int64_t m_amoCum; /*总额/元*/

    friend std::ostream& operator<<(std::ostream& os, const IntQuoteDiff& a);
};

struct IntLimitUpDn {
    size_t m_idxVecExCode;
    size_t m_idxVecIntDayBar;
    int32_t m_count;
};

}
