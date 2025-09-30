// Copyright (c) 2025-present Mason Zhao MasonSZhao@qq.com

// QilD2d.h : Include file for standard system include files, or project specific include files.

#pragma once

#include <windows.h> // <windows.h> should be in front of <commctrl.h>
#include <windowsx.h>

#include <commctrl.h>

#include <d2d1_3.h>
#pragma comment(lib, "d2d1.lib")
#include <dwrite_3.h>
#pragma comment(lib, "dwrite.lib")

#include "..\include\QilD2dWndDep.h"
#include "..\include\QilD2dWndDepLimitPeriod.h"
#include "..\include\QilD2dWndDepMain.h"
#include "..\include\QilD2dWndDepTimeSharing.h"
#include "..\include\QilD2dWndIndep.h"
