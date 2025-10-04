// Copyright (c) 2025-present Mason Zhao MasonSZhao@qq.com

#include "..\include\QilHostFileTd.h"

#include "..\include\QilHostSecurityS.h"
#include <fstream>

#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE // spdlog #define should be in front of SPD #include.

#include <spdlog/spdlog.h> // spdlog #define should be in front of SPD #include.

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

    std::vector<QILHOST::TD::FltDayBar> FileVecDayBar::flt(const char* exCode, const size_t readCount, const bool readFromBackNotFront)
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
                if (readFromBackNotFront) {
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

    std::vector<QILHOST::IntDateBar> FileVecDayBar::int3264(const char* exCode, const size_t readCount, const bool readFromBackNotFront)
    {
        std::vector<QILHOST::TD::FltDayBar> vecFltDayBar { flt(exCode, readCount, readFromBackNotFront) };
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

    std::vector<QILHOST::TD::FltMinuteBar> FileVecMinuteBar::flt(const char* exCode, const size_t readCount, const bool readFromBackNotFront)
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
                if (readFromBackNotFront) {
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

    std::vector<QILHOST::IntMinuteBar> FileVecMinuteBar::int3264(const char* exCode, const size_t readCount, const bool readFromBackNotFront)
    {
        std::vector<QILHOST::TD::FltMinuteBar> vecFltMinuteBar { flt(exCode, readCount, readFromBackNotFront) };
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

    std::vector<QILHOST::TD::FltMinuteBar> FileVecMinuteBar::fltDate(const char* exCode, const size_t readCount, const int32_t readFromDate, const size_t guessFileCount, const ptrdiff_t guessFileIdx /*, const bool readPreClose*/)
    {
        std::vector<QILHOST::TD::FltMinuteBar> vecFltMinuteBar;
        {
            std::string filePath { QILHOST::TD::FileVecMinuteBar::getFilePath(exCode) };
            std::ifstream ifs(filePath, std::ios::binary);
            if (ifs.is_open()) {
                ifs.seekg(0, std::ios::end);
                std::streampos fileSize = ifs.tellg();
                size_t fileCount = fileSize / sizeof(QILHOST::TD::FltMinuteBar);
                bool needReSearch { true };
                if ((guessFileCount == fileCount) && (guessFileIdx > 0)) {
                    needReSearch = false;
                }
                if (false == needReSearch) {
                    ifs.seekg(guessFileIdx * sizeof(QILHOST::TD::FltMinuteBar), std::ios::beg);
                    size_t leftCount = fileCount - guessFileIdx;
                    if (leftCount >= readCount) {
                        vecFltMinuteBar.resize(readCount);
                        ifs.read(reinterpret_cast<char*>(&vecFltMinuteBar[0]), readCount * sizeof(QILHOST::TD::FltMinuteBar));
                    } else {
                        vecFltMinuteBar.resize(leftCount);
                        ifs.read(reinterpret_cast<char*>(&vecFltMinuteBar[0]), leftCount * sizeof(QILHOST::TD::FltMinuteBar));
                    }
                } else {
                    SPDLOG_TRACE(std::string { exCode } + " FileVecMinuteBar " + std::to_string(readFromDate) + " do need research.");
                    ifs.seekg(0, std::ios::beg);
                    size_t leftCount = fileCount;
                    while (!ifs.eof()) {
                        QILHOST::TD::FltMinuteBar temp;
                        ifs >> temp;
                        --leftCount;
                        if (temp.uintDate() != readFromDate) {
                            ifs.ignore(239 * sizeof(QILHOST::TD::FltMinuteBar));
                            leftCount -= 239;
                        } else {
                            vecFltMinuteBar.push_back(temp);
                            break;
                        }
                    }
                    if (leftCount >= readCount - 1) {
                        vecFltMinuteBar.resize(vecFltMinuteBar.size() + readCount - 1);
                        ifs.read(reinterpret_cast<char*>(&vecFltMinuteBar[1]), (readCount - 1) * sizeof(QILHOST::TD::FltMinuteBar));
                    } else {
                        vecFltMinuteBar.resize(vecFltMinuteBar.size() + leftCount);
                        ifs.read(reinterpret_cast<char*>(&vecFltMinuteBar[1]), leftCount * sizeof(QILHOST::TD::FltMinuteBar));
                    }
                }
            } else {
                std::cerr << "Failed to open file: " << filePath << std::endl;
            }
            ifs.close();
        }
        return vecFltMinuteBar;
    }

    std::vector<QILHOST::IntMinuteBar> FileVecMinuteBar::int3264Date(const char* exCode, const size_t readCount, const int32_t readFromDate, const size_t guessFileCount, const ptrdiff_t guessFileIdx /*, const bool readPreClose*/)
    {
        std::vector<QILHOST::TD::FltMinuteBar> vecFltMinuteBar { fltDate(exCode, readCount, readFromDate, guessFileCount, guessFileIdx /*, const bool readPreClose*/) };
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

    std::vector<int32_t> FileVecMinuteBar::s_vecDate1999999;

    std::unordered_map<int32_t, size_t> FileVecMinuteBar::s_lutDate1999999;

    void FileVecMinuteBar::lut1999999()
    {
        std::vector<QILHOST::TD::FltMinuteBar> vecFltMinuteBar;
        {
            std::string filePath { QILHOST::TD::FileVecMinuteBar::getFilePath("1999999") };
            std::ifstream ifs(filePath, std::ios::binary);
            if (ifs.is_open()) {
                ifs.seekg(0, std::ios::end);
                std::streampos fileSize = ifs.tellg();
                size_t readSize = 240 * sizeof(QILHOST::TD::FltMinuteBar);
                // 从尾读取
                if (false) {
                }
                // 从头读取
                else {
                    if (fileSize >= readSize) {
                        ifs.seekg(0, std::ios::beg);
                        size_t fileCount = fileSize / sizeof(QILHOST::TD::FltMinuteBar);
                        vecFltMinuteBar.reserve(fileCount);
                        // BUG: The 'while' code will read the last QILHOST::TD::FltMinuteBar twice, then trigger ifs.tellg() == -1 which means ifs.eof().
                        // while (!ifs.eof()) {
                        // FIX:
                        for (size_t i { 0 }; i < fileCount / 240; ++i) {
                            QILHOST::TD::FltMinuteBar temp;
                            ifs >> temp;
                            vecFltMinuteBar.push_back(temp);
                            ifs.ignore(239 * sizeof(QILHOST::TD::FltMinuteBar));
                        }
                    }
                }
            } else {
                std::cerr << "Failed to open file: " << filePath << std::endl;
            }
            ifs.close();
        }

        FileVecMinuteBar::s_vecDate1999999.reserve(vecFltMinuteBar.size());

        for (const auto& e : vecFltMinuteBar)
            FileVecMinuteBar::s_vecDate1999999.push_back(e.uintDate());

        for (size_t i { 0 }; i < FileVecMinuteBar::s_vecDate1999999.size(); ++i) {
            FileVecMinuteBar::s_lutDate1999999.insert(std::unordered_map<int32_t, size_t>::value_type(FileVecMinuteBar::s_vecDate1999999[i], i));
        }
    }

    std::string FileVecExCode360::s_filePathSz { "C:/new_tdx/T0002/hq_cache/szs.tnf" };

    std::string FileVecExCode360::s_filePathSh { "C:/new_tdx/T0002/hq_cache/shs.tnf" };

    std::string FileVecExCode360::s_filePathBj { "C:/new_tdx/T0002/hq_cache/bjs.tnf" };

    void FileVecExCode360::sz(const bool sz00, const bool sz30)
    {
        std::vector<std::array<char, 8>> vecExCode;
        std::vector<std::array<char, 9>> vecName;
        std::vector<std::array<char, 5>> vecSpell;
        std::ifstream ifs(QILHOST::TD::FileVecExCode360::s_filePathSz, std::ifstream::in | std::ifstream::binary);
        if (ifs.is_open()) {
            ifs.ignore(50);
            while (!ifs.eof()) {
                char buf[360];
                ifs.read(&buf[0], 360);
                bool isExCode { false };
                if (true == sz00) // QUOTE THIE LINE WHEN RUN BY CODE
                    if (('0' == buf[0]) && ('0' == buf[1])) {
                        isExCode = true;
                    }
                if (true == sz30) // QUOTE THIE LINE WHEN RUN BY CODE
                    if (('3' == buf[0]) && ('0' == buf[1])) {
                        isExCode = true;
                    }
                if (true == isExCode) {
                    std::array<char, 8> exCode {};
                    memcpy(&exCode[1], &buf[0], 6);
                    exCode[0] = '0';
                    exCode[7] = '\0';
                    std::array<char, 9> name {};
                    memcpy(name.data(), &buf[31], 8);
                    name[8] = '\0';
                    // std::string name(&buf[31], 9);
                    std::array<char, 5> spell {};
                    memcpy(spell.data(), &buf[329], 4);
                    spell[4] = '\0';
                    // std::string spell(&buf[329], 5);
                    // std::cout << exCode.data() << " " << name.data() << " " << spell.data() << "      ";
                    vecExCode.emplace_back(exCode);
                    vecName.emplace_back(name);
                    vecSpell.emplace_back(spell);
                }
            }
        } else {
            std::cerr << "Failed to open file: " << QILHOST::TD::FileVecExCode360::s_filePathSz << std::endl;
        }
        ifs.close();
        if (QILHOST::VecExCode360::s_vecExCode.empty()) {
            QILHOST::VecExCode360::s_vecExCode.swap(vecExCode);
            QILHOST::VecExCode360::s_vecName.swap(vecName);
            QILHOST::VecExCode360::s_vecSpell.swap(vecSpell);
        } else {
            QILHOST::VecExCode360::s_vecExCode.insert(QILHOST::VecExCode360::s_vecExCode.end(), vecExCode.begin(), vecExCode.end());
            QILHOST::VecExCode360::s_vecName.insert(QILHOST::VecExCode360::s_vecName.end(), vecName.begin(), vecName.end());
            QILHOST::VecExCode360::s_vecSpell.insert(QILHOST::VecExCode360::s_vecSpell.end(), vecSpell.begin(), vecSpell.end());
        }
    }

    void FileVecExCode360::sh(const bool sh60, const bool sh68)
    {
        std::vector<std::array<char, 8>> vecExCode;
        std::vector<std::array<char, 9>> vecName;
        std::vector<std::array<char, 5>> vecSpell;
        std::ifstream ifs(QILHOST::TD::FileVecExCode360::s_filePathSh, std::ifstream::in | std::ifstream::binary);
        if (ifs.is_open()) {
            ifs.ignore(50);
            while (!ifs.eof()) {
                char buf[360];
                ifs.read(&buf[0], 360);
                bool isExCode { false };
                if (true == sh60) // QUOTE THIE LINE WHEN RUN BY CODE
                    if (('6' == buf[0]) && ('0' == buf[1])) {
                        isExCode = true;
                    }
                if (true == sh68) // QUOTE THIE LINE WHEN RUN BY CODE
                    if (('6' == buf[0]) && ('8' == buf[1])) {
                        isExCode = true;
                    }
                if (true == isExCode) {
                    std::array<char, 8> exCode {};
                    memcpy(&exCode[1], &buf[0], 6);
                    exCode[0] = '1';
                    exCode[7] = '\0';
                    std::array<char, 9> name {};
                    memcpy(name.data(), &buf[31], 8);
                    name[8] = '\0';
                    // std::string name(&buf[31], 9);
                    std::array<char, 5> spell {};
                    memcpy(spell.data(), &buf[329], 4);
                    spell[4] = '\0';
                    // std::string spell(&buf[329], 5);
                    // std::cout << exCode.data() << " " << name.data() << " " << spell.data() << "      ";
                    vecExCode.emplace_back(exCode);
                    vecName.emplace_back(name);
                    vecSpell.emplace_back(spell);
                }
            }
        } else {
            std::cerr << "Failed to open file: " << QILHOST::TD::FileVecExCode360::s_filePathSh << std::endl;
        }
        ifs.close();
        if (QILHOST::VecExCode360::s_vecExCode.empty()) {
            QILHOST::VecExCode360::s_vecExCode.swap(vecExCode);
            QILHOST::VecExCode360::s_vecName.swap(vecName);
            QILHOST::VecExCode360::s_vecSpell.swap(vecSpell);
        } else {
            QILHOST::VecExCode360::s_vecExCode.insert(QILHOST::VecExCode360::s_vecExCode.end(), vecExCode.begin(), vecExCode.end());
            QILHOST::VecExCode360::s_vecName.insert(QILHOST::VecExCode360::s_vecName.end(), vecName.begin(), vecName.end());
            QILHOST::VecExCode360::s_vecSpell.insert(QILHOST::VecExCode360::s_vecSpell.end(), vecSpell.begin(), vecSpell.end());
        }
    }

    void FileVecExCode360::bj()
    {
        std::vector<std::array<char, 8>> vecExCode;
        std::vector<std::array<char, 9>> vecName;
        std::vector<std::array<char, 5>> vecSpell;
        std::ifstream ifs(QILHOST::TD::FileVecExCode360::s_filePathBj, std::ifstream::in | std::ifstream::binary);
        if (ifs.is_open()) {
            ifs.ignore(50);
            while (!ifs.eof()) {
                char buf[360];
                ifs.read(&buf[0], 360);
                bool isExCode { false };
                if (('4' == buf[0]) && ('3' == buf[1])) {
                    isExCode = true;
                } else if (('8' == buf[0]) && ('3' == buf[1])) {
                    isExCode = true;
                } else if (('8' == buf[0]) && ('7' == buf[1])) {
                    isExCode = true;
                }
                if (true == isExCode) {
                    std::array<char, 8> exCode {};
                    memcpy(&exCode[1], &buf[0], 6);
                    exCode[0] = '2';
                    exCode[7] = '\0';
                    std::array<char, 9> name {};
                    memcpy(name.data(), &buf[31], 8);
                    name[8] = '\0';
                    // std::string name(&buf[31], 9);
                    std::array<char, 5> spell {};
                    memcpy(spell.data(), &buf[329], 4);
                    spell[4] = '\0';
                    // std::string spell(&buf[329], 5);
                    // std::cout << exCode.data() << " " << name.data() << " " << spell.data() << "      ";
                    vecExCode.emplace_back(exCode);
                    vecName.emplace_back(name);
                    vecSpell.emplace_back(spell);
                }
            }
        } else {
            std::cerr << "Failed to open file: " << QILHOST::TD::FileVecExCode360::s_filePathBj << std::endl;
        }
        ifs.close();
        if (QILHOST::VecExCode360::s_vecExCode.empty()) {
            QILHOST::VecExCode360::s_vecExCode.swap(vecExCode);
            QILHOST::VecExCode360::s_vecName.swap(vecName);
            QILHOST::VecExCode360::s_vecSpell.swap(vecSpell);
        } else {
            QILHOST::VecExCode360::s_vecExCode.insert(QILHOST::VecExCode360::s_vecExCode.end(), vecExCode.begin(), vecExCode.end());
            QILHOST::VecExCode360::s_vecName.insert(QILHOST::VecExCode360::s_vecName.end(), vecName.begin(), vecName.end());
            QILHOST::VecExCode360::s_vecSpell.insert(QILHOST::VecExCode360::s_vecSpell.end(), vecSpell.begin(), vecSpell.end());
        }
    }

    std::string FileVecExCode314::s_filePathSz { "C:/new_tdx/T0002/hq_cache/szm.tnf" };

    std::string FileVecExCode314::s_filePathSh { "C:/new_tdx/T0002/hq_cache/shm.tnf" };

    std::string FileVecExCode314::s_filePathBj { "C:/new_tdx/T0002/hq_cache/bjm.tnf" };

    void FileVecExCode314::sz(const bool sz00, const bool sz30)
    {
        std::vector<std::array<char, 8>> vecExCode;
        std::vector<std::array<char, 19>> vecName;
        std::vector<std::array<char, 10>> vecSpell;
        std::ifstream ifs(QILHOST::TD::FileVecExCode314::s_filePathSz, std::ifstream::in | std::ifstream::binary);
        if (ifs.is_open()) {
            ifs.ignore(50);
            while (!ifs.eof()) {
                char buf[314];
                ifs.read(&buf[0], 314);
                bool isExCode { false };
                if (true == sz00) // QUOTE THIE LINE WHEN RUN BY CODE
                    if (('0' == buf[0]) && ('0' == buf[1])) {
                        isExCode = true;
                    }
                if (true == sz30) // QUOTE THIE LINE WHEN RUN BY CODE
                    if (('3' == buf[0]) && ('0' == buf[1])) {
                        isExCode = true;
                    }
                if (true == isExCode) {
                    std::array<char, 8> exCode {};
                    memcpy(&exCode[1], &buf[0], 6);
                    exCode[0] = '0';
                    exCode[7] = '\0';
                    std::array<char, 19> name {};
                    memcpy(name.data(), &buf[23], 18);
                    std::array<char, 10> spell {};
                    memcpy(spell.data(), &buf[285], 9);
                    vecExCode.emplace_back(exCode);
                    vecName.emplace_back(name);
                    vecSpell.emplace_back(spell);
                }
            }
        } else {
            std::cerr << "Failed to open file: " << QILHOST::TD::FileVecExCode314::s_filePathSz << std::endl;
        }
        ifs.close();
        if (QILHOST::VecExCode314::s_vecExCode.empty()) {
            QILHOST::VecExCode314::s_vecExCode.swap(vecExCode);
            QILHOST::VecExCode314::s_vecName.swap(vecName);
            QILHOST::VecExCode314::s_vecSpell.swap(vecSpell);
        } else {
            QILHOST::VecExCode314::s_vecExCode.insert(QILHOST::VecExCode314::s_vecExCode.end(), vecExCode.begin(), vecExCode.end());
            QILHOST::VecExCode314::s_vecName.insert(QILHOST::VecExCode314::s_vecName.end(), vecName.begin(), vecName.end());
            QILHOST::VecExCode314::s_vecSpell.insert(QILHOST::VecExCode314::s_vecSpell.end(), vecSpell.begin(), vecSpell.end());
        }
    }

    void FileVecExCode314::sh(const bool sh60, const bool sh68)
    {
        std::vector<std::array<char, 8>> vecExCode;
        std::vector<std::array<char, 19>> vecName;
        std::vector<std::array<char, 10>> vecSpell;
        std::ifstream ifs(QILHOST::TD::FileVecExCode314::s_filePathSh, std::ifstream::in | std::ifstream::binary);
        if (ifs.is_open()) {
            ifs.ignore(50);
            while (!ifs.eof()) {
                char buf[314];
                ifs.read(&buf[0], 314);
                bool isExCode { false };
                if (true == sh60) // QUOTE THIE LINE WHEN RUN BY CODE
                    if (('6' == buf[0]) && ('0' == buf[1])) {
                        isExCode = true;
                    }
                if (true == sh68) // QUOTE THIE LINE WHEN RUN BY CODE
                    if (('6' == buf[0]) && ('8' == buf[1])) {
                        isExCode = true;
                    }
                if (true == isExCode) {
                    std::array<char, 8> exCode {};
                    memcpy(&exCode[1], &buf[0], 6);
                    exCode[0] = '1';
                    exCode[7] = '\0';
                    std::array<char, 19> name {};
                    memcpy(name.data(), &buf[23], 18);
                    std::array<char, 10> spell {};
                    memcpy(spell.data(), &buf[285], 9);
                    vecExCode.emplace_back(exCode);
                    vecName.emplace_back(name);
                    vecSpell.emplace_back(spell);
                }
            }
        } else {
            std::cerr << "Failed to open file: " << QILHOST::TD::FileVecExCode314::s_filePathSh << std::endl;
        }
        ifs.close();

        if (QILHOST::VecExCode314::s_vecExCode.empty()) {
            QILHOST::VecExCode314::s_vecExCode.swap(vecExCode);
            QILHOST::VecExCode314::s_vecName.swap(vecName);
            QILHOST::VecExCode314::s_vecSpell.swap(vecSpell);
        } else {
            QILHOST::VecExCode314::s_vecExCode.insert(QILHOST::VecExCode314::s_vecExCode.end(), vecExCode.begin(), vecExCode.end());
            QILHOST::VecExCode314::s_vecName.insert(QILHOST::VecExCode314::s_vecName.end(), vecName.begin(), vecName.end());
            QILHOST::VecExCode314::s_vecSpell.insert(QILHOST::VecExCode314::s_vecSpell.end(), vecSpell.begin(), vecSpell.end());
        }
    }

    void FileVecExCode314::bj()
    {
        std::vector<std::array<char, 8>> vecExCode;
        std::vector<std::array<char, 19>> vecName;
        std::vector<std::array<char, 10>> vecSpell;
        std::ifstream ifs(QILHOST::TD::FileVecExCode314::s_filePathBj, std::ifstream::in | std::ifstream::binary);
        if (ifs.is_open()) {
            ifs.ignore(50);
            while (!ifs.eof()) {
                char buf[314];
                ifs.read(&buf[0], 314);
                bool isExCode { false };
                if (('4' == buf[0]) && ('3' == buf[1])) {
                    isExCode = true;
                } else if (('8' == buf[0]) && ('3' == buf[1])) {
                    isExCode = true;
                } else if (('8' == buf[0]) && ('7' == buf[1])) {
                    isExCode = true;
                }
                if (true == isExCode) {
                    std::array<char, 8> exCode {};
                    memcpy(&exCode[1], &buf[0], 6);
                    exCode[0] = '2';
                    exCode[7] = '\0';
                    std::array<char, 19> name {};
                    memcpy(name.data(), &buf[23], 18);
                    std::array<char, 10> spell {};
                    memcpy(spell.data(), &buf[285], 9);
                    vecExCode.emplace_back(exCode);
                    vecName.emplace_back(name);
                    vecSpell.emplace_back(spell);
                }
            }
        } else {
            std::cerr << "Failed to open file: " << QILHOST::TD::FileVecExCode314::s_filePathBj << std::endl;
        }
        ifs.close();

        if (QILHOST::VecExCode314::s_vecExCode.empty()) {
            QILHOST::VecExCode314::s_vecExCode.swap(vecExCode);
            QILHOST::VecExCode314::s_vecName.swap(vecName);
            QILHOST::VecExCode314::s_vecSpell.swap(vecSpell);
        } else {
            QILHOST::VecExCode314::s_vecExCode.insert(QILHOST::VecExCode314::s_vecExCode.end(), vecExCode.begin(), vecExCode.end());
            QILHOST::VecExCode314::s_vecName.insert(QILHOST::VecExCode314::s_vecName.end(), vecName.begin(), vecName.end());
            QILHOST::VecExCode314::s_vecSpell.insert(QILHOST::VecExCode314::s_vecSpell.end(), vecSpell.begin(), vecSpell.end());
        }
    }

}
}
