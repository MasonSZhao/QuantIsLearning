// Copyright (c) 2025-present Mason Zhao MasonSZhao@qq.com

// QilD2d.h : Include file for standard system include files, or project specific include files.

#pragma once

#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE // spdlog #define should be in front of SPD #include.

#include <spdlog/async.h> // spdlog #define should be in front of SPD #include.
#include <spdlog/sinks/basic_file_sink.h> // spdlog文件输出
#include <spdlog/sinks/stdout_color_sinks.h> // spdlog控制台彩色输出
#include <spdlog/spdlog.h> // spdlog #define should be in front of SPD #include.

#include <windows.h> // <windows.h> should be in front of <commctrl.h>
#include <windowsx.h>

#include <ShlObj_core.h> // SHGetSpecialFolderPath CSIDL_LOCAL_APPDATA 头文件

#include <commctrl.h>

#include <d2d1_3.h>
#pragma comment(lib, "d2d1.lib")
#include <dwrite_3.h>
#pragma comment(lib, "dwrite.lib")

#include "..\include\QilD2dWndDep.h"
#include "..\include\QilD2dWndDepAbout.h"
#include "..\include\QilD2dWndDepLimitPeriod.h"
#include "..\include\QilD2dWndDepMain.h"
#include "..\include\QilD2dWndDepTimeSharing.h"
#include "..\include\QilD2dWndIndep.h"
