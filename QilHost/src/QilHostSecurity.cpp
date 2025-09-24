// Copyright (c) 2025-present Mason Zhao MasonSZhao@qq.com

#include "..\include\QilHostSecurity.h"

namespace QILHOST {

int SeqCharHash::operator()(const char* a) const
{
    const static int seed { 131 };
    int hash { 0 };
    hash = (hash * seed) + (*a);
    while (*(++a)) {
        hash = (hash * seed) + (*a);
    }
    return hash & (0x7FFFFFFF);
}

namespace TD {

    std::ostream& operator<<(std::ostream& os, const FltDayBar& a)
    {
        os << '|' << a.m_date
           << '|' << a.m_op
           << '|' << a.m_hi
           << '|' << a.m_lo
           << '|' << a.m_cl
           << '|' << a.m_amo
           << '|' << a.m_vol
           << '|';
        return os;
    }

    std::istream& operator>>(std::istream& is, FltDayBar& a)
    {
        is.read(reinterpret_cast<char*>(&a), sizeof(FltDayBar));
        return is;
    }

    uint32_t FltMinuteBar::uintDate() const
    {
        uint32_t tempYYYYMMDD { 0 };
        tempYYYYMMDD += (m_date / 2048 + 2004) /*year*/ * 10000; // year
        auto tempMMDD { m_date % 2048 };
        tempYYYYMMDD += (tempMMDD / 100) /*month*/ * 100;
        tempYYYYMMDD += (tempMMDD % 100) /*day*/;
        return tempYYYYMMDD;
    }

    uint32_t FltMinuteBar::uintTime() const
    {
        return (m_time / 60) * 100 /*hour*/ + (m_time % 60) /*minute*/;
    }

    std::ostream& operator<<(std::ostream& os, const FltMinuteBar& a)
    {
        os << '|' << a.uintDate()
           << '|' << a.uintTime()
           << '|' << a.m_op
           << '|' << a.m_hi
           << '|' << a.m_lo
           << '|' << a.m_cl
           << '|' << a.m_amo
           << '|' << a.m_vol
           << '|';
        return os;
    }

    std::istream& operator>>(std::istream& is, FltMinuteBar& a)
    {
        is.read(reinterpret_cast<char*>(&a), sizeof(FltMinuteBar));
        return is;
    }

}

std::ostream& operator<<(std::ostream& os, const IntDateBar& a)
{
    os
        << '|' << a.m_date
        << '|' << a.m_op
        << '|' << a.m_hi
        << '|' << a.m_lo
        << '|' << a.m_cl
        << '|' << a.m_amo
        << '|' << a.m_vol
        << '|';
    return os;
}

std::ostream& operator<<(std::ostream& os, const IntMinuteBar& a)
{
    os << a.m_date << '|' << a.m_time << '|';
    os
        << '|' << a.m_op
        << '|' << a.m_hi
        << '|' << a.m_lo
        << '|' << a.m_cl
        << '|' << a.m_amo
        << '|' << a.m_vol;
    return os;
}

std::ostream& operator<<(std::ostream& os, const IntQuote2& a)
{
    os
        << '|' << a.m_time
        << '|' << a.m_pr1st
        << '|' << a.m_vol1st
        << '|' << a.m_vol2nd;
    return os;
}

std::ostream& operator<<(std::ostream& os, const IntQuote5& a)
{
    std::cout << std::endl
              << std::endl
              << "时间" << '\t' << a.m_time << std::endl
              << "现价" << '\t' << a.m_cl << ' ' << "现量" << '\t' << a.m_vol << ' ' << '\t' << "今开" << '\t' << a.m_op << std::endl
              << "涨跌" << '\t' << (a.m_cl - a.m_preCl) << ' ' << "最高" << '\t' << a.m_hi << std::endl
              << "涨幅" << '\t' << (a.m_cl - a.m_preCl) * 100. / a.m_preCl << '%' << ' ' << "最低" << '\t' << a.m_lo << std::endl
              << "昨收" << '\t' << a.m_preCl << ' ' << "均价" << '\t';
    if (0 == a.m_volCum) {
        std::cout << "NA" << std::endl;
    } else {
        std::cout << a.m_amoCum / a.m_volCum / 100. << std::endl;
    }
    std::cout << "振幅" << '\t' << (a.m_hi - a.m_lo) * 100. / a.m_lo << '%' << ' ' << "量比" << '\t' << std::endl
              << "总量" << '\t' << a.m_volCum << ' ' << "总额" << '\t';
    if (a.m_amoCum < 100000000.)
        std::cout << a.m_amoCum / 10000. << "万" << std::endl;
    else
        std::cout << a.m_amoCum / 100000000. << "亿" << std::endl;
    std::cout << "外盘" << '\t' << a.m_volBidCum << ' ' << "内盘" << '\t' << a.m_volAskCum << std::endl;
    std::cout
        << std::endl
        << "- - - " << std::endl
        << "卖五" << '\t' << a.m_prAsk5th << '\t' << '\t' << a.m_volAsk5th << std::endl
        << "卖四" << '\t' << a.m_prAsk4th << '\t' << '\t' << a.m_volAsk4th << std::endl
        << "卖三" << '\t' << a.m_prAsk3rd << '\t' << '\t' << a.m_volAsk3rd << std::endl
        << "卖二" << '\t' << a.m_prAsk2nd << '\t' << '\t' << a.m_volAsk2nd << std::endl
        << "卖一" << '\t' << a.m_prAsk1st << '\t' << '\t' << a.m_volAsk1st << std::endl
        << "买一" << '\t' << a.m_prBid1st << '\t' << '\t' << a.m_volBid1st << std::endl
        << "买二" << '\t' << a.m_prBid2nd << '\t' << '\t' << a.m_volBid2nd << std::endl
        << "买三" << '\t' << a.m_prBid3rd << '\t' << '\t' << a.m_volBid3rd << std::endl
        << "买四" << '\t' << a.m_prBid4th << '\t' << '\t' << a.m_volBid4th << std::endl
        << "买五" << '\t' << a.m_prBid5th << '\t' << '\t' << a.m_volBid5th << std::endl
        << "------" << std::endl;

    return os;
}

std::ostream& operator<<(std::ostream& os, const IntQuoteDiff& a)
{
    os
        << '|' << a.m_date
        << '|' << a.m_time
        << '|' << a.m_pr
        << '|' << a.m_vol
        << '|' << a.m_qty
        << '|' << a.m_bs
        << '|' << a.m_amoCum
        << '|';
    return os;
}

}
