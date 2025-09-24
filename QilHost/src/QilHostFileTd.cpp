// Copyright (c) 2025-present Mason Zhao MasonSZhao@qq.com

#include "..\include\QilHostFileTd.h"

#include <fstream>

namespace QILHOST {

namespace TD {

    std::string FileVecDayBar::s_folderPath { "C:/new_tdx/vipdoc/" };

    std::string FileVecDayBar::getFilePath(const char* exCode)
    {
        std::string filePath { s_folderPath };
        if ('0' == exCode[0]) {
            filePath += "sz/lday/sz";
            filePath += &exCode[1];
            filePath += ".day";
        } else if ('1' == exCode[0]) {
            filePath += "sh/lday/sh";
            filePath += &exCode[1];
            filePath += ".day";
        } else if ('2' == exCode[0]) {
            filePath += "bj/lday/bj";
            filePath += &exCode[1];
            filePath += ".day";
        } else {
            throw std::runtime_error("Expect 0, 1 or 2. The actual is " + exCode[0]);
        }
        return filePath;
    }

    std::vector<QILHOST::TD::FltDayBar> FileVecDayBar::flt(const char* exCode, const size_t readCount, const bool readBackNotFront)
    {
        std::vector<QILHOST::TD::FltDayBar> vecFltDayBar;
        {
            std::string filePath { QILHOST::TD::FileVecDayBar::getFilePath(exCode) };
            std::ifstream ifs(filePath, std::ios::binary);
            if (ifs.is_open()) {
                ifs.seekg(0, std::ios::end);
                std::streampos fileSize = ifs.tellg();
                size_t readSize = readCount * sizeof(QILHOST::TD::FltDayBar);
                // 从尾读取
                if (readBackNotFront) {
                    if (fileSize >= readSize) {
                        ifs.seekg(-1 * readSize, std::ios::end);
                        vecFltDayBar.resize(readCount);
                        ifs.read(reinterpret_cast<char*>(&vecFltDayBar[0]), readSize);
                    } else {
                        ifs.seekg(0, std::ios::beg);
                        vecFltDayBar.resize(fileSize / sizeof(QILHOST::TD::FltDayBar));
                        ifs.read(reinterpret_cast<char*>(&vecFltDayBar[0]), fileSize);
                    }
                }
                // 从头读取
                else {
                    if (fileSize >= readSize) {
                        ifs.seekg(0, std::ios::beg);
                        vecFltDayBar.resize(readCount);
                        ifs.read(reinterpret_cast<char*>(&vecFltDayBar[0]), readSize);
                    } else {
                        ifs.seekg(0, std::ios::beg);
                        vecFltDayBar.resize(fileSize / sizeof(QILHOST::TD::FltDayBar));
                        ifs.read(reinterpret_cast<char*>(&vecFltDayBar[0]), fileSize);
                    }
                }
            } else {
                std::cerr << "Failed to open file: " << filePath << std::endl;
            }
            ifs.close();
        }

        return vecFltDayBar;
    }

    std::vector<QILHOST::IntDateBar> FileVecDayBar::int3264(const char* exCode, const size_t readCount, const bool readBackNotFront)
    {
        std::vector<QILHOST::TD::FltDayBar> vecFltDayBar { flt(exCode, readCount, readBackNotFront) };
        std::vector<QILHOST::IntDateBar> vecIntDateBar;
        vecIntDateBar.resize(vecFltDayBar.size());
        for (size_t i { 0 }; i < vecFltDayBar.size(); ++i) {
            memcpy(&vecIntDateBar[i].m_date, &vecFltDayBar[i].m_date, sizeof(uint32_t) * 5);
            vecIntDateBar[i].m_amo = vecFltDayBar[i].m_amo * 100;
            vecIntDateBar[i].m_vol = vecFltDayBar[i].m_vol;
        }
        return vecIntDateBar;
    }

    std::string FileVecMinuteBar::s_folderPath { "C:/new_tdx/vipdoc/" };

    std::string FileVecMinuteBar::getFilePath(const char* exCode)
    {
        std::string filePath { s_folderPath };
        if ('0' == exCode[0]) {
            filePath += "sz/minline/sz";
            filePath += &exCode[1];
            filePath += ".lc1";
        } else if ('1' == exCode[0]) {
            filePath += "sh/minline/sh";
            filePath += &exCode[1];
            filePath += ".lc1";
        } else if ('2' == exCode[0]) {
            filePath += "bj/minline/bj";
            filePath += &exCode[1];
            filePath += ".lc1";
        } else {
            throw std::runtime_error("Expect 0, 1 or 2. The actual is " + exCode[0]);
        }
        return filePath;
    }

    std::vector<QILHOST::TD::FltMinuteBar> FileVecMinuteBar::flt(const char* exCode, const size_t readCount, const bool readBackNotFront)
    {
        std::vector<QILHOST::TD::FltMinuteBar> vecFltMinuteBar;
        {
            std::string filePath { QILHOST::TD::FileVecMinuteBar::getFilePath(exCode) };
            std::ifstream ifs(filePath, std::ios::binary);
            if (ifs.is_open()) {
                ifs.seekg(0, std::ios::end);
                std::streampos fileSize = ifs.tellg();
                size_t readSize = readCount * sizeof(QILHOST::TD::FltMinuteBar);
                // 从尾读取
                if (readBackNotFront) {
                    if (fileSize >= readSize) {
                        ifs.seekg(-1 * readSize, std::ios::end);
                        vecFltMinuteBar.resize(readCount);
                        ifs.read(reinterpret_cast<char*>(&vecFltMinuteBar[0]), readSize);
                    } else {
                        ifs.seekg(0, std::ios::beg);
                        vecFltMinuteBar.resize(fileSize / sizeof(QILHOST::TD::FltMinuteBar));
                        ifs.read(reinterpret_cast<char*>(&vecFltMinuteBar[0]), fileSize);
                    }
                }
                // 从头读取
                else {
                    if (fileSize >= readSize) {
                        ifs.seekg(0, std::ios::beg);
                        vecFltMinuteBar.resize(readCount);
                        ifs.read(reinterpret_cast<char*>(&vecFltMinuteBar[0]), readSize);
                    } else {
                        ifs.seekg(0, std::ios::beg);
                        vecFltMinuteBar.resize(fileSize / sizeof(QILHOST::TD::FltMinuteBar));
                        ifs.read(reinterpret_cast<char*>(&vecFltMinuteBar[0]), fileSize);
                    }
                }
            } else {
                std::cerr << "Failed to open file: " << filePath << std::endl;
            }
            ifs.close();
        }
        return vecFltMinuteBar;
    }

    std::vector<QILHOST::IntMinuteBar> FileVecMinuteBar::int3264(const char* exCode, const size_t readCount, const bool readBackNotFront)
    {
        std::vector<QILHOST::TD::FltMinuteBar> vecFltMinuteBar { flt(exCode, readCount, readBackNotFront) };
        std::vector<QILHOST::IntMinuteBar> vecIntMinuteBar;
        vecIntMinuteBar.reserve(vecFltMinuteBar.size());
        for (const auto& e : vecFltMinuteBar) {
            QILHOST::IntMinuteBar temp;
            temp.m_date = static_cast<int32_t>(e.uintDate());
            temp.m_time = static_cast<int32_t>(e.uintTime());
            temp.m_op = static_cast<int32_t>(e.m_op * 100);
            temp.m_hi = static_cast<int32_t>(e.m_hi * 100);
            temp.m_lo = static_cast<int32_t>(e.m_lo * 100);
            temp.m_cl = static_cast<int32_t>(e.m_cl * 100);
            temp.m_amo = static_cast<int64_t>(e.m_amo * 100);
            temp.m_vol = static_cast<int64_t>(e.m_vol);
            vecIntMinuteBar.push_back(temp);
        }
        return vecIntMinuteBar;
    }

}

}
