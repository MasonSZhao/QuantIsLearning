// Copyright (c) 2025-present Mason Zhao MasonSZhao@qq.com

// QilD2d.cpp : Defines the entry point for the application.

#include "QilD2d.h"
#include "..\src\Resource.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR lpCmdLine,
    _In_ int nCmdShow)
{
    // 创建一个文件输出器，若为空文件夹则自动创建文件夹和文件，若存在文件及和文件则自动续写。
    std::string logPath;
    {
        int32_t intDate;
        {
            time_t systemTime = time(nullptr);
            tm localTime;
            localtime_s(&localTime, &systemTime);
            intDate = (localTime.tm_year + 1900) * 10000 + (localTime.tm_mon + 1) * 100 + localTime.tm_mday;
        }
        {
            char User_AppData_Local[MAX_PATH];
            SHGetSpecialFolderPathA(0, User_AppData_Local, CSIDL_LOCAL_APPDATA, 0);
            logPath = std::string { User_AppData_Local } + "\\.QIL\\SpLog\\" + std::to_string(intDate) + ".txt";
        }
    }

    auto file_logger = spdlog::basic_logger_mt("daily_logger", logPath);

    file_logger->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%t] [%s-%#-%!] [%l] %v"); // 设置日志格式 %t thread id, %s source fileName, %# source fileLine, %! source funcName, #l log level, %v log text.
    file_logger->set_level(spdlog::level::info); // 设置文件日志级别
    file_logger->flush_on(spdlog::level::info);

    // spdlog::register_logger(file_logger); // 注册多态日志器
    spdlog::set_default_logger(file_logger);
    spdlog::set_level(spdlog::level::info);

    if (false) {
        std::wstring msg { L"QIL启动。" };
        USES_CONVERSION;
        SPDLOG_INFO(W2A(msg.c_str()));
    } else {
        SPDLOG_INFO("QIL starts.");
    }

    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);

    // Use HeapSetInformation to specify that the process should terminate if the heap manager detects an error in any heap used by the process.
    HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);

    AllocConsole();

    QILD2D::D2dWndIndep::s_hCout = GetStdHandle(STD_OUTPUT_HANDLE);

    HRESULT hr = S_OK;

    // FACTORY
    {
        if (SUCCEEDED(hr))
            hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_MULTI_THREADED, &QILD2D::D2dWndIndep::s_pD2D1Factory);
        if (SUCCEEDED(hr))
            hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory7), reinterpret_cast<IUnknown**>(&QILD2D::D2dWndIndep::s_pDWriteFactory));
    }

    // FONT
    {
        if (SUCCEEDED(hr))
            hr = QILD2D::D2dWndIndep::s_pDWriteFactory->CreateFontSetBuilder(&QILD2D::D2dWndIndep::s_pDWriteFontSetBuilder);
        std::wstring pFilePath = L"../AlibabaPuHuiTi-3-55-Regular.ttf";
        IDWriteFontFile* pDWriteFontFile = NULL;
        if (SUCCEEDED(hr))
            hr = QILD2D::D2dWndIndep::s_pDWriteFactory->CreateFontFileReference(pFilePath.c_str(), nullptr /*lastWriteTime*/, &pDWriteFontFile);
        if (SUCCEEDED(hr))
            hr = QILD2D::D2dWndIndep::s_pDWriteFontSetBuilder->AddFontFile(pDWriteFontFile);
        if (SUCCEEDED(hr))
            hr = QILD2D::D2dWndIndep::s_pDWriteFontSetBuilder->CreateFontSet(&QILD2D::D2dWndIndep::s_pDWriteFontSet);
        QILD2D::D2dWndIndep::s_pDWriteFactory->CreateFontCollectionFromFontSet(QILD2D::D2dWndIndep::s_pDWriteFontSet, &QILD2D::D2dWndIndep::s_pDWriteFontCollection);
        if (SUCCEEDED(hr)) {
            hr = QILD2D::D2dWndIndep::s_pDWriteFactory->CreateTextFormat(L"Alibaba PuHuiTi 3.0", QILD2D::D2dWndIndep::s_pDWriteFontCollection /* NULL sets to the system font collection*/, DWRITE_FONT_WEIGHT_REGULAR, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 16.f, L"zh-cn", &QILD2D::D2dWndIndep::s_pDWriteTextFormat16);
            hr = QILD2D::D2dWndIndep::s_pDWriteFactory->CreateTextFormat(L"Alibaba PuHuiTi 3.0", QILD2D::D2dWndIndep::s_pDWriteFontCollection /* NULL sets to the system font collection*/, DWRITE_FONT_WEIGHT_REGULAR, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 14.f, L"zh-cn", &QILD2D::D2dWndIndep::s_pDWriteTextFormat14);
        }
        if (SUCCEEDED(hr)) {
            IDWriteTextLayout* pDWriteTextLayout;
            {
                std::wstring temp = L"lineHeight16";
                QILD2D::D2dWndIndep::s_pDWriteFactory->CreateTextLayout(temp.c_str(), temp.size(), QILD2D::D2dWndIndep::s_pDWriteTextFormat16, 0 /*可使用renderTargetSize*/, 0 /*可使用renderTargetSize*/, &pDWriteTextLayout);
                pDWriteTextLayout->SetWordWrapping(DWRITE_WORD_WRAPPING_NO_WRAP); // Set the word wrapping mode to DWRITE_WORD_WRAPPING_NO_WRAP
                DWRITE_TEXT_METRICS metrics;
                pDWriteTextLayout->GetMetrics(&metrics);
                QILD2D::D2dWndIndep::s_lineHeight16 = metrics.height;
                metrics.widthIncludingTrailingWhitespace;
            }
            pDWriteTextLayout->Release();
        }
        if (SUCCEEDED(hr)) {
            IDWriteTextLayout* pDWriteTextLayout;
            {
                std::wstring temp = L"lineHeight14";
                QILD2D::D2dWndIndep::s_pDWriteFactory->CreateTextLayout(temp.c_str(), temp.size(), QILD2D::D2dWndIndep::s_pDWriteTextFormat14, 0 /*可使用renderTargetSize*/, 0 /*可使用renderTargetSize*/, &pDWriteTextLayout);
                pDWriteTextLayout->SetWordWrapping(DWRITE_WORD_WRAPPING_NO_WRAP); // Set the word wrapping mode to DWRITE_WORD_WRAPPING_NO_WRAP
                DWRITE_TEXT_METRICS metrics;
                pDWriteTextLayout->GetMetrics(&metrics);
                QILD2D::D2dWndIndep::s_lineHeight14 = metrics.height;
                metrics.widthIncludingTrailingWhitespace;
            }
            pDWriteTextLayout->Release();
        }
    }

    // WNDCLASS
    {
        WNDCLASS wc {};
        wc.lpfnWndProc = QILD2D::D2dWndDepMain::WndProc;
        wc.cbClsExtra = 0;
        wc.cbWndExtra = sizeof(LONG_PTR);
        wc.hInstance = hInstance;
        wc.hbrBackground = NULL;
        wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_QILD2D)); // https://learn.microsoft.com/en-us/windows/win32/menurc/using-icons
        wc.hCursor = LoadCursor(hInstance, IDC_ARROW);
        wc.lpszClassName = TEXT("WndMain");
        if (!RegisterClass(&wc)) {
            MessageBox(NULL, TEXT("Call to RegisterClass failed!"), TEXT("量化正在学习"), NULL);
            return 1;
        }
    }
    {
        WNDCLASS wc {};
        wc.lpfnWndProc = QILD2D::D2dWndDepLimitPeriodText::WndProc;
        wc.cbClsExtra = 0;
        wc.cbWndExtra = sizeof(LONG_PTR);
        wc.hInstance = hInstance;
        wc.hbrBackground = NULL;
        wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_QILD2D)); // https://learn.microsoft.com/en-us/windows/win32/menurc/using-icons
        wc.hCursor = LoadCursor(hInstance, IDC_ARROW);
        wc.lpszClassName = TEXT("WndLimitPeriodText");
        if (!RegisterClass(&wc)) {
            MessageBox(NULL, TEXT("Call to RegisterClass failed!"), TEXT("量化正在学习"), NULL);
            return 1;
        }
    }
    {
        WNDCLASS wc {};
        wc.lpfnWndProc = QILD2D::D2dWndDepLimitPeriodTimeSharing::WndProc;
        wc.cbClsExtra = 0;
        wc.cbWndExtra = sizeof(LONG_PTR);
        wc.hInstance = hInstance;
        wc.hbrBackground = NULL;
        wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_QILD2D)); // https://learn.microsoft.com/en-us/windows/win32/menurc/using-icons
        wc.hCursor = LoadCursor(hInstance, IDC_ARROW);
        wc.lpszClassName = TEXT("WndLimitPeriodTimeSharing");
        if (!RegisterClass(&wc)) {
            MessageBox(NULL, TEXT("Call to RegisterClass failed!"), TEXT("量化正在学习"), NULL);
            return 1;
        }
    }
    {
        WNDCLASS wc {};
        wc.lpfnWndProc = QILD2D::D2dWndDepAbout::WndProc;
        wc.cbClsExtra = 0;
        wc.cbWndExtra = sizeof(LONG_PTR);
        wc.hInstance = hInstance;
        wc.hbrBackground = NULL;
        wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_QILD2D)); // https://learn.microsoft.com/en-us/windows/win32/menurc/using-icons
        wc.hCursor = LoadCursor(hInstance, IDC_ARROW);
        wc.lpszClassName = TEXT("WndAbout");
        if (!RegisterClass(&wc)) {
            MessageBox(NULL, TEXT("Call to RegisterClass failed!"), TEXT("量化正在学习"), NULL);
            return 1;
        }
    }

    // MENU
    HMENU hMenu = CreateMenu();
    HMENU hMenuSys = CreateMenu();
    AppendMenu(hMenu, MF_POPUP, (UINT)hMenuSys, TEXT("系统(&S)"));
    {
        AppendMenu(hMenuSys, MF_STRING, WNDMAIN_HMENU_SYS_SETDAYBAR, TEXT("指定日线999999.day文件(&D)"));
        AppendMenu(hMenuSys, MF_STRING, WNDMAIN_HMENU_SYS_SETMINUTEBAR, TEXT("指定分钟999999.lc1文件(&M)"));
        AppendMenu(hMenuSys, MF_SEPARATOR, 0, NULL);
        AppendMenu(hMenuSys, MF_STRING | MF_DISABLED, WNDMAIN_HMENU_SYS_SETMULTITHREAD, TEXT("指定多线程性能(&T)"));
        AppendMenu(hMenuSys, MF_SEPARATOR, 0, NULL);
        HMENU hMenuSysColor = CreateMenu();
        AppendMenu(hMenuSys, MF_POPUP, (UINT)hMenuSysColor, TEXT("指定主题颜色(&C)"));
        {
            AppendMenu(hMenuSysColor, MF_STRING | MF_CHECKED, WNDMAIN_HMENU_SYS_COLOR_WHITE, TEXT("浅白(&W)"));
            AppendMenu(hMenuSysColor, MF_STRING | MF_DISABLED, WNDMAIN_HMENU_SYS_COLOR_BLACK, TEXT("深黑(&B)"));
            AppendMenu(hMenuSysColor, MF_STRING | MF_DISABLED, WNDMAIN_HMENU_SYS_COLOR_GRAY, TEXT("浅灰(&G)"));
        }
        AppendMenu(hMenuSys, MF_SEPARATOR, 0, NULL);
        AppendMenu(hMenuSys, MF_STRING | MF_DISABLED, WNDMAIN_HMENU_SYS_EXCONFIGFILE, TEXT("导出配置文件(&E)"));
        AppendMenu(hMenuSys, MF_STRING | MF_DISABLED, WNDMAIN_HMENU_SYS_IMCONFIGFILE, TEXT("导入配置文件(&I)"));
    }
    HMENU hMenuEarlyWarn = CreateMenu();
    AppendMenu(hMenu, MF_POPUP | MF_DISABLED, (UINT)hMenuEarlyWarn, TEXT("预警(&W)"));
    HMENU hMenuL1Eye = CreateMenu();
    AppendMenu(hMenu, MF_POPUP | MF_DISABLED, (UINT)hMenuL1Eye, TEXT("盯盘(&E)"));
    HMENU hMenuReview = CreateMenu();
    AppendMenu(hMenu, MF_POPUP, (UINT)hMenuReview, TEXT("复盘(&R)"));
    {
        HMENU hMenuReviewLimitPeriod = CreateMenu();
        AppendMenu(hMenuReview, MF_POPUP, (UINT)hMenuReviewLimitPeriod, TEXT("时序-造板连板周期(&L)"));
        AppendMenu(hMenuReviewLimitPeriod, MF_STRING, WNDMAIN_HMENU_REVIEW_LIMITPERIOD300TIMESHARING, TEXT("创业板 分时对比"));
        AppendMenu(hMenuReviewLimitPeriod, MF_STRING, WNDMAIN_HMENU_REVIEW_LIMITPERIOD300DESCRIPTION, TEXT("创业板 文字简述"));
        AppendMenu(hMenuReviewLimitPeriod, MF_STRING | MF_DISABLED, WNDMAIN_HMENU_REVIEW_LIMITPERIOD688TIMESHARING, TEXT("科创板 分时对比"));
        AppendMenu(hMenuReviewLimitPeriod, MF_STRING | MF_DISABLED, WNDMAIN_HMENU_REVIEW_LIMITPERIOD688DESCRIPTION, TEXT("科创板 文字简述"));
        AppendMenu(hMenuReviewLimitPeriod, MF_STRING | MF_DISABLED, WNDMAIN_HMENU_REVIEW_LIMITPERIODBJTIMESHARING, TEXT("北交所 分时对比"));
        AppendMenu(hMenuReviewLimitPeriod, MF_STRING | MF_DISABLED, WNDMAIN_HMENU_REVIEW_LIMITPERIODBJDESCRIPTION, TEXT("北交所 文字简述"));
        AppendMenu(hMenuReviewLimitPeriod, MF_STRING | MF_DISABLED, WNDMAIN_HMENU_REVIEW_LIMITPERIODSHSZTIMESHARING, TEXT("主板 分时对比"));
        AppendMenu(hMenuReviewLimitPeriod, MF_STRING | MF_DISABLED, WNDMAIN_HMENU_REVIEW_LIMITPERIODSHSZDESCRIPTION, TEXT("主板 文字简述"));
        HMENU hMenuReviewConceptPeriod = CreateMenu();
        AppendMenu(hMenuReview, MF_STRING | MF_DISABLED, (UINT)hMenuReviewConceptPeriod, TEXT("时序-题材周期(&C)"));
        AppendMenu(hMenuReview, MF_SEPARATOR, 0, NULL);
        HMENU hMenuReivewGOrL = CreateMenu();
        AppendMenu(hMenuReview, MF_STRING | MF_DISABLED, (UINT)hMenuReivewGOrL, TEXT("截面-赚钱亏钱效应(&G)"));
        HMENU hMenuReviewQuotePub = CreateMenu();
        AppendMenu(hMenuReview, MF_POPUP, (UINT)hMenuReviewQuotePub, TEXT("截面-龙虎榜数据(&Q)"));
        AppendMenu(hMenuReviewQuotePub, MF_STRING | MF_DISABLED, WNDMAIN_HMENU_REVIEW_QUOTEPUBINSTI, TEXT("机构"));
        AppendMenu(hMenuReviewQuotePub, MF_STRING | MF_DISABLED, WNDMAIN_HMENU_REVIEW_QUOTEPUBQUANT, TEXT("量化"));
        AppendMenu(hMenuReviewQuotePub, MF_STRING | MF_DISABLED, WNDMAIN_HMENU_REVIEW_QUOTEPUBHOTMONEY, TEXT("游资"));
    }
    HMENU hMenuFilter = CreateMenu();
    AppendMenu(hMenu, MF_POPUP, (UINT)hMenuFilter, TEXT("选股(&F)"));
    {
        HMENU hMenuFilterPr = CreateMenu();
        AppendMenu(hMenuFilter, MF_POPUP | MF_DISABLED, (UINT)hMenuFilterPr, TEXT("价"));
        HMENU hMenuFilterVol = CreateMenu();
        AppendMenu(hMenuFilter, MF_POPUP | MF_DISABLED, (UINT)hMenuFilterVol, TEXT("量"));
        HMENU hMenuFilterForm = CreateMenu();
        AppendMenu(hMenuFilter, MF_POPUP | MF_DISABLED, (UINT)hMenuFilterForm, TEXT("形态"));
    }
    HMENU hMenuHelp = CreateMenu();
    AppendMenu(hMenu, MF_POPUP, (UINT)hMenuHelp, TEXT("帮助(&H)"));
    {
        AppendMenu(hMenuHelp, MF_STRING, WNDMAIN_HMENU_HELP_ABOUT, TEXT("关于(&A)"));
    }

    // CREATE
    HWND hWnd = CreateWindow(
        TEXT("WndMain"), // Window class
        TEXT("量化正在学习"), // Window text
        WS_OVERLAPPEDWINDOW, // Window style
        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        NULL, // Parent window
        hMenu, // Menu
        hInstance, // Instance handle
        NULL // Additional application data
    );

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    // Run the message loop.
    MSG msg {};

    // Run the message loop.
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // FONT
    QILD2D::D2dWndIndep::SafeRelease(&QILD2D::D2dWndIndep::s_pD2D1StrokeStyle);
    QILD2D::D2dWndIndep::SafeRelease(&QILD2D::D2dWndIndep::s_pDWriteTextFormat16);
    QILD2D::D2dWndIndep::SafeRelease(&QILD2D::D2dWndIndep::s_pDWriteFontSet);
    QILD2D::D2dWndIndep::SafeRelease(&QILD2D::D2dWndIndep::s_pDWriteFontSetBuilder);
    QILD2D::D2dWndIndep::SafeRelease(&QILD2D::D2dWndIndep::s_pDWriteFontCollection);

    // FACTORY
    QILD2D::D2dWndIndep::SafeRelease(&QILD2D::D2dWndIndep::s_pDWriteFactory);
    QILD2D::D2dWndIndep::SafeRelease(&QILD2D::D2dWndIndep::s_pD2D1Factory);

    if (false) {
        std::wstring msg { L"QIL退出。" };
        USES_CONVERSION;
        SPDLOG_INFO(W2A(msg.c_str()));
    } else {
        SPDLOG_INFO("QIL ends.");
    }

    {
        // 清理并释放资源
        spdlog::drop_all(); // 释放所有资源
    }

    return (int)msg.wParam;
}
