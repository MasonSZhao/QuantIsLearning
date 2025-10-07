// Copyright (c) 2025-present Mason Zhao MasonSZhao@qq.com

#pragma once

#include "QilHostSecurity.h"
// #include <mutex>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

namespace QILHOST {

namespace TD {

    /**
     * @brief 读取单个日线文件。
     */
    struct FileVecDayBar {
        static std::string s_folderPath;
        static std::string getFilePath(const char* exCode);
        static std::vector<QILHOST::TD::FltDayBar> flt(const char* exCode, const size_t readCount, const bool readFromBackNotFront);
        static std::vector<QILHOST::IntDateBar> int3264(const char* exCode, const size_t readCount, const bool readFromBackNotFront);
    };

    /**
     * @brief 读取单个分钟文件。
     */
    struct FileVecMinuteBar {
        /////////////////////////////////////////////////////////////////////////////
        //
        // TODO
        //
        // Index Auto Cache
        // Binary Search When Index Cache Doesn't Match
        //

        /////////////////////////////////////////////////////////////////////////////
        //
        // Path of Folder, File
        //
        static std::string s_folderPath;
        static std::string getFilePath(const char* exCode);

        /////////////////////////////////////////////////////////////////////////////
        //
        // Index Auto Cache
        //
        // static std::mutex s_mutCache;
        // static std::set<size_t> s_setFileCount;
        // static std::vector<std::unordered_map<int32_t, size_t>> s_veclutDate;

        /////////////////////////////////////////////////////////////////////////////
        //
        // Read File
        //
        static std::vector<QILHOST::TD::FltMinuteBar> flt(const char* exCode, const size_t readCount, const bool readFromBackNotFront);
        static std::vector<QILHOST::IntMinuteBar> int3264(const char* exCode, const size_t readCount, const bool readFromBackNotFront);

        /////////////////////////////////////////////////////////////////////////////
        //
        // Read Date
        //
        static std::vector<QILHOST::TD::FltMinuteBar> fltDate(const char* exCode, const int32_t readDate);
        static std::vector<QILHOST::IntMinuteBar> int3264Date(const char* exCode, const int32_t readDate);

        /////////////////////////////////////////////////////////////////////////////
        //
        // Read Set Date
        //
        static std::vector<std::vector<QILHOST::TD::FltMinuteBar>> fltSetDate(const char* exCode, std::set<int32_t> readSetDate);
        static std::vector<std::vector<QILHOST::IntMinuteBar>> int3264SetDate(const char* exCode, std::set<int32_t> readSetDate);
    };

    /**
     * @brief 读取证券代码文件。
     */
    struct FileVecExCode360 {
        static std::string s_filePathSh;
        static std::string s_filePathSz;
        static std::string s_filePathBj;

        static void sz(const bool sz00, const bool sz30);
        static void sh(const bool sh60, const bool sh68);
        static void bj();
    };

    /**
     * @brief 读取证券代码文件。
     */
    struct FileVecExCode314 {
        static std::string s_filePathSh;
        static std::string s_filePathSz;
        static std::string s_filePathBj;

        static void sz(const bool sz00, const bool sz30);
        static void sh(const bool sh60, const bool sh68);
        static void bj();
    };

}

}
