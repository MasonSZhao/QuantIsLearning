// Copyright (c) 2025-present Mason Zhao MasonSZhao@qq.com

// QilHost.h : Include file for standard system include files, or project specific include files.

#pragma once

#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE // spdlog #define should be in front of SPD #include.

#include <spdlog/async.h> // spdlog #define should be in front of SPD #include.
#include <spdlog/sinks/basic_file_sink.h> // spdlog文件输出
#include <spdlog/sinks/stdout_color_sinks.h> // spdlog控制台彩色输出
#include <spdlog/spdlog.h> // spdlog #define should be in front of SPD #include.

#include "..\include\QilHostFileTd.h"
#include "..\include\QilHostSecurity.h"
#include "..\include\QilHostSecurityS.h"
#include "..\include\QilHostTech.h"

#include <ShlObj_core.h> // SHGetSpecialFolderPath CSIDL_LOCAL_APPDATA 头文件
#include <iostream>
