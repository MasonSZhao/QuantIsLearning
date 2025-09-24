// Copyright (c) 2025-present Mason Zhao MasonSZhao@qq.com

#pragma once

#include "QilHostSecurity.h"
#include <string>
#include <vector>

namespace QILHOST {

namespace TD {

    /**
     * @brief 读取单个日线文件。
     */
    struct FileVecDayBar {
        static std::string s_folderPath;
        static std::string getFilePath(const char* exCode);
        static std::vector<QILHOST::TD::FltDayBar> flt(const char* exCode, const size_t readCount, const bool readBackNotFront);
        static std::vector<QILHOST::IntDateBar> int3264(const char* exCode, const size_t readCount, const bool readBackNotFront);
    };

    /**
     * @brief 读取单个分钟文件。
     */
    struct FileVecMinuteBar {
        static std::string s_folderPath;
        static std::string getFilePath(const char* exCode);
        static std::vector<QILHOST::TD::FltMinuteBar> flt(const char* exCode, const size_t readCount, const bool readBackNotFront);
        static std::vector<QILHOST::IntMinuteBar> int3264(const char* exCode, const size_t readCount, const bool readBackNotFront);
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
