// Copyright (c) 2025-present Mason Zhao MasonSZhao@qq.com

// QilD2d.cpp : Defines the entry point for the application.

#include "QilD2d.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR lpCmdLine,
    _In_ int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

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
        wc.hCursor = LoadCursor(hInstance, IDI_APPLICATION);
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
        wc.hCursor = LoadCursor(hInstance, IDI_APPLICATION);
        wc.lpszClassName = TEXT("WndLimitPeriodText");
        if (!RegisterClass(&wc)) {
            MessageBox(NULL, TEXT("Call to RegisterClass failed!"), TEXT("量化正在学习"), NULL);
            return 1;
        }
    }

    // MENU
    HMENU hMenu = CreateMenu();
    HMENU hMenuFeature = CreateMenu();
    AppendMenu(hMenu, MF_POPUP, (UINT)hMenuFeature, TEXT("功能"));
    {
        AppendMenu(hMenuFeature, MF_STRING, WNDMAIN_HMENU_FEATURE_LIMITPERIOD300, "创业板周期");
        AppendMenu(hMenuFeature, MF_STRING, WNDMAIN_HMENU_FEATURE_LIMITPERIOD688, "科创板周期");
        AppendMenu(hMenuFeature, MF_STRING, WNDMAIN_HMENU_FEATURE_LIMITPERIODBJ, "北交所周期");
    }
    HMENU hMenuOptions = CreateMenu();
    AppendMenu(hMenu, MF_POPUP, (UINT)hMenuOptions, TEXT("设置"));
    {
    }
    HMENU hMenuHelp = CreateMenu();
    AppendMenu(hMenu, MF_POPUP, (UINT)hMenuHelp, TEXT("帮助(&H)"));
    {
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

    return (int)msg.wParam;
}

namespace QILD2D {

// Factory
ID2D1Factory5* D2dWndIndep::s_pD2D1Factory = NULL;
IDWriteFactory7* D2dWndIndep::s_pDWriteFactory = NULL;
IDWriteTextFormat* D2dWndIndep::s_pDWriteTextFormat16 = NULL;
IDWriteTextFormat* D2dWndIndep::s_pDWriteTextFormat14 = NULL;

float D2dWndIndep::s_lineHeight16 = 0;
float D2dWndIndep::s_lineHeight14 = 0;

// Font
IDWriteFontCollection1* D2dWndIndep::s_pDWriteFontCollection = NULL;
IDWriteFontSetBuilder2* D2dWndIndep::s_pDWriteFontSetBuilder = NULL;
IDWriteFontSet* D2dWndIndep::s_pDWriteFontSet = NULL;
ID2D1StrokeStyle* D2dWndIndep::s_pD2D1StrokeStyle = NULL;

HANDLE D2dWndIndep::s_hCout = NULL;

LRESULT CALLBACK D2dWndDepMain::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg) {
    case WM_ERASEBKGND: {
        return true /*avoid flicker*/;
    }
    case WM_NCDESTROY: {
        QILD2D::D2dWndDepMain* ptr = reinterpret_cast<QILD2D::D2dWndDepMain*>(static_cast<LONG_PTR>(GetWindowLongPtr(hWnd, GWLP_USERDATA)));
        QILD2D::D2dWndIndep::SafeRelease(&(ptr->m_D2dWndDep.m_pD2DSolidColorBrushGreen));
        QILD2D::D2dWndIndep::SafeRelease(&(ptr->m_D2dWndDep.m_pD2DSolidColorBrushRed));
        QILD2D::D2dWndIndep::SafeRelease(&(ptr->m_D2dWndDep.m_pD2DSolidColorBrushGray));
        QILD2D::D2dWndIndep::SafeRelease(&(ptr->m_D2dWndDep.m_pD2DSolidColorBrushLightGray));
        QILD2D::D2dWndIndep::SafeRelease(&(ptr->m_D2dWndDep.m_pD2DSolidColorBrushBlack));
        QILD2D::D2dWndIndep::SafeRelease(&(ptr->m_D2dWndDep.m_pD2D1HwndRenderTarget));
        delete ptr;
        ptr = nullptr;
        PostQuitMessage(0);
        return 0;
    }
    case WM_CREATE: {
        QILD2D::D2dWndDepMain* ptr = new QILD2D::D2dWndDepMain;
        SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(ptr));
        // 并行线程
        if (true) {
            std::vector<std::jthread> vecThread;
            // 并行线程 上证指数分时数据
            vecThread.emplace_back([&]() {
                std::vector<QILHOST::IntMinuteBar> des { QILHOST::TD::FileVecMinuteBar::int3264("1999999", 241, true) };
                {
                    ptr->m_D2dWndDepMinuteBar1999999.m_vecMinuteBar.reserve(240);
                    ptr->m_D2dWndDepMinuteBar1999999.m_preCl = des[0].m_cl;
                    ptr->m_D2dWndDepMinuteBar1999999.m_limitUpPr = des[1].m_cl;
                    ptr->m_D2dWndDepMinuteBar1999999.m_limitDnPr = des[1].m_cl;
                    ptr->m_D2dWndDepMinuteBar1999999.m_volMax = des[0].m_vol;
                    for (auto i { 1 }; i <= 240; ++i) {
                        ptr->m_D2dWndDepMinuteBar1999999.m_vecMinuteBar.push_back(des[i]);
                        if (des[i].m_vol > ptr->m_D2dWndDepMinuteBar1999999.m_volMax)
                            ptr->m_D2dWndDepMinuteBar1999999.m_volMax = des[i].m_vol;
                        if (des[i].m_cl > ptr->m_D2dWndDepMinuteBar1999999.m_limitUpPr)
                            ptr->m_D2dWndDepMinuteBar1999999.m_limitUpPr = des[i].m_cl;
                        if (des[i].m_cl < ptr->m_D2dWndDepMinuteBar1999999.m_limitDnPr)
                            ptr->m_D2dWndDepMinuteBar1999999.m_limitDnPr = des[i].m_cl;
                    }
                    int32_t temp = ptr->m_D2dWndDepMinuteBar1999999.m_limitUpPr - des[0].m_cl;
                    if ((des[0].m_cl - ptr->m_D2dWndDepMinuteBar1999999.m_limitDnPr) > temp) {
                        temp = des[0].m_cl - ptr->m_D2dWndDepMinuteBar1999999.m_limitDnPr;
                    }
                    temp += 100;
                    ptr->m_D2dWndDepMinuteBar1999999.m_limitUpPr = ptr->m_D2dWndDepMinuteBar1999999.m_preCl + temp;
                    ptr->m_D2dWndDepMinuteBar1999999.m_limitDnPr = ptr->m_D2dWndDepMinuteBar1999999.m_preCl - temp;
                    ptr->m_D2dWndDepMinuteBar1999999.m_volMax += 0.1 * ptr->m_D2dWndDepMinuteBar1999999.m_volMax;
                }
            });
        }
        HRESULT hr = S_OK;
        if (SUCCEEDED(hr)) {
            RECT rc;
            GetClientRect(hWnd, &rc);
            hr = QILD2D::D2dWndIndep::s_pD2D1Factory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(hWnd, D2D1::SizeU(rc.right, rc.bottom)), &((*ptr).m_D2dWndDep.m_pD2D1HwndRenderTarget));
        }
        if (SUCCEEDED(hr)) {
            hr = (*ptr).m_D2dWndDep.m_pD2D1HwndRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &((*ptr).m_D2dWndDep.m_pD2DSolidColorBrushBlack));
            hr = (*ptr).m_D2dWndDep.m_pD2D1HwndRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::LightGray), &((*ptr).m_D2dWndDep.m_pD2DSolidColorBrushLightGray));
            hr = (*ptr).m_D2dWndDep.m_pD2D1HwndRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Gray), &((*ptr).m_D2dWndDep.m_pD2DSolidColorBrushGray));
            hr = (*ptr).m_D2dWndDep.m_pD2D1HwndRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Red), &((*ptr).m_D2dWndDep.m_pD2DSolidColorBrushRed));
            hr = (*ptr).m_D2dWndDep.m_pD2D1HwndRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Green), &((*ptr).m_D2dWndDep.m_pD2DSolidColorBrushGreen));
        }
        if (!SUCCEEDED(hr)) {
            delete ptr;
            ptr = nullptr;
        }
        return 1;
    }
    case WM_PAINT: {
        // PAINTSTRUCT ps;
        // HDC hDC = BeginPaint(hWnd, &ps);
        // SetBkMode(hDC, TRANSPARENT);
        RECT rc;
        GetClientRect(hWnd, &rc);
        QILD2D::D2dWndDepMain* ptr = reinterpret_cast<QILD2D::D2dWndDepMain*>(static_cast<LONG_PTR>(GetWindowLongPtr(hWnd, GWLP_USERDATA)));
        ptr->m_D2dWndDep.m_pD2D1HwndRenderTarget->BeginDraw();
        // All painting occurs here, between BeginPaint and EndPaint.
        ptr->m_D2dWndDep.m_pD2D1HwndRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));
        QILD2D::D2dWndDepTimeSharing::WMPAINT op;
        op.m_preCl = ptr->m_D2dWndDepMinuteBar1999999.m_preCl;
        op.m_limitUpPr = ptr->m_D2dWndDepMinuteBar1999999.m_limitUpPr;
        op.m_limitDnPr = ptr->m_D2dWndDepMinuteBar1999999.m_limitDnPr;
        op.m_volMax = ptr->m_D2dWndDepMinuteBar1999999.m_volMax;
        op.m_xStart = 0;
        op.m_yStart = 0;
        op.m_xWidth = (rc.right - rc.left);
        op.m_yHeight = (rc.bottom - rc.top);
        op.m_d2dWndDep = &(ptr->m_D2dWndDep);
        op.m_vecIntMinuteBar = &(ptr->m_D2dWndDepMinuteBar1999999.m_vecMinuteBar);
        op.operator()();
        // FillRect(hDC, &ps.rcPaint, //(HBRUSH)GetStockObject(WHITE_BRUSH));
        //     CreateSolidBrush(RGB((rand() % (255 + 1)), (rand() % (255 + 1)), (rand() % (255 + 1)))));
        ptr->m_D2dWndDep.m_pD2D1HwndRenderTarget->EndDraw();
        // EndPaint(hWnd, &ps);
        ValidateRect(hWnd, NULL);
        return 0;
    }
    case WM_SIZE: {
        QILD2D::D2dWndDepMain* ptr = reinterpret_cast<QILD2D::D2dWndDepMain*>(static_cast<LONG_PTR>(GetWindowLongPtr(hWnd, GWLP_USERDATA)));
        D2D1_SIZE_U size = D2D1::SizeU(LOWORD(lParam), HIWORD(lParam));
        ptr->m_D2dWndDep.m_pD2D1HwndRenderTarget->Resize(size);
        InvalidateRect(hWnd, NULL, FALSE);
        return 0;
    }
    case WM_COMMAND: {
        auto hWndCtrl = lParam; // 发送WM_COMMAND的子窗口句柄
        auto wNotifyCode = HIWORD(wParam); // 菜单消息的通知码为0，加速键消息的通知码为1。
        auto wID = LOWORD(wParam);
        switch (wID) {
        case WNDMAIN_HMENU_FEATURE_LIMITPERIOD300: {
            HWND hWndLimitPeriodText = CreateWindow(
                "WndLimitPeriodText", // 窗口类注册名称
                "创业板周期", // 窗口标题
                WS_VISIBLE | WS_OVERLAPPEDWINDOW, // 标准交互
                CW_USEDEFAULT, // 初始x坐标
                CW_USEDEFAULT, // 初始y坐标
                CW_USEDEFAULT, // 初始x方向尺寸
                CW_USEDEFAULT, // 初始y方向尺寸
                hWnd, // 父窗口句柄
                NULL /* Must be NULL! */, // 主窗口菜单句柄、子窗口窗口标识（整形、父窗口内唯一）
                GetModuleHandle(NULL), // 程序实例句柄
                NULL // 窗口创建参数
            );
            QILD2D::D2dWndDepLimitPeriodText* ptr = reinterpret_cast<QILD2D::D2dWndDepLimitPeriodText*>(static_cast<LONG_PTR>(GetWindowLongPtr(hWnd, GWLP_USERDATA)));
            break;
        }
        default:
            break;
        }
        return 0;
    }
    default:
        break;
    }
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

void D2dWndDepTimeSharing::WMPAINT::operator()()
{
    float widthLeft = 50;
    if (!m_hasLeft) {
        widthLeft = 0;
    }
    float widthPrVol = m_xWidth;
    float widthRight = 50;
    if (!m_hasRight) {
        widthRight = 0;
    }
    float heightPr = m_yHeight * 0.75;
    float heightVol = m_yHeight * 0.25;
    m_d2dWndDep->m_pD2D1HwndRenderTarget->DrawRectangle({ m_xStart + widthLeft + 0 /*left*/, m_yStart + 0 /*top*/, m_xStart + widthLeft + widthPrVol /*right*/, m_yStart + heightPr /*bottom*/ }, m_d2dWndDep->m_pD2DSolidColorBrushGray, 1);
    m_d2dWndDep->m_pD2D1HwndRenderTarget->DrawRectangle({ m_xStart + widthLeft + 0 /*left*/, m_yStart + heightPr /*top*/, m_xStart + widthLeft + widthPrVol /*right*/, m_yStart + heightPr + heightVol /*bottom*/ }, m_d2dWndDep->m_pD2DSolidColorBrushGray, 1);
    m_d2dWndDep->m_pD2D1HwndRenderTarget->DrawLine({ m_xStart + widthLeft + 0 /*x*/, m_yStart + heightPr * 0.25f /*y*/ }, { m_xStart + widthLeft + widthPrVol /*x*/, m_yStart + heightPr * 0.25f /*y*/ }, m_d2dWndDep->m_pD2DSolidColorBrushLightGray, 1);
    m_d2dWndDep->m_pD2D1HwndRenderTarget->DrawLine({ m_xStart + widthLeft + 0 /*x*/, m_yStart + heightPr * 0.5f /*y*/ }, { m_xStart + widthLeft + widthPrVol /*x*/, m_yStart + heightPr * 0.5f /*y*/ }, m_d2dWndDep->m_pD2DSolidColorBrushLightGray, 1);
    m_d2dWndDep->m_pD2D1HwndRenderTarget->DrawLine({ m_xStart + widthLeft + 0 /*x*/, m_yStart + heightPr * 0.75f /*y*/ }, { m_xStart + widthLeft + widthPrVol /*x*/, m_yStart + heightPr * 0.75f /*y*/ }, m_d2dWndDep->m_pD2DSolidColorBrushLightGray, 1);
    m_d2dWndDep->m_pD2D1HwndRenderTarget->DrawLine({ m_xStart + widthLeft + widthPrVol * 0.5f /*x*/, m_yStart + 0 /*y*/ }, { m_xStart + widthLeft + widthPrVol * 0.5f /*x*/, m_yStart + heightPr + heightVol /*y*/ }, m_d2dWndDep->m_pD2DSolidColorBrushLightGray, 1);
    m_d2dWndDep->m_pD2D1HwndRenderTarget->DrawLine({ m_xStart + widthLeft + widthPrVol * 0.25f /*x*/, m_yStart + 0 /*y*/ }, { m_xStart + widthLeft + widthPrVol * 0.25f /*x*/, m_yStart + heightPr + heightVol /*y*/ }, m_d2dWndDep->m_pD2DSolidColorBrushLightGray, 1);
    m_d2dWndDep->m_pD2D1HwndRenderTarget->DrawLine({ m_xStart + widthLeft + widthPrVol * 0.75f /*x*/, m_yStart + 0 /*y*/ }, { m_xStart + widthLeft + widthPrVol * 0.75f /*x*/, m_yStart + heightPr + heightVol /*y*/ }, m_d2dWndDep->m_pD2DSolidColorBrushLightGray, 1);
    if (true) {
        int32_t limitUpDnPr = m_limitUpPr - m_limitDnPr;
        {
            D2D1_POINT_2F p0 = { m_xStart + widthLeft, m_yStart + ((float)(m_limitUpPr - (*m_vecIntMinuteBar)[0].m_op) / (float)limitUpDnPr) * heightPr };
            D2D1_POINT_2F p1 = { m_xStart + widthLeft + widthPrVol / 240.f, m_yStart + ((float)(m_limitUpPr - (*m_vecIntMinuteBar)[0].m_cl) / (float)limitUpDnPr) * heightPr };
            m_d2dWndDep->m_pD2D1HwndRenderTarget->DrawLine(p0, p1, m_d2dWndDep->m_pD2DSolidColorBrushBlack, 1);
            for (size_t i { 1 }; i <= 239; ++i) {
                p0 = p1;
                p1.x += widthPrVol / 240.f;
                p1.y = m_yStart + ((float)(m_limitUpPr - (*m_vecIntMinuteBar)[i].m_cl) / (float)limitUpDnPr) * heightPr;
                m_d2dWndDep->m_pD2D1HwndRenderTarget->DrawLine(p0, p1, m_d2dWndDep->m_pD2DSolidColorBrushBlack, 1);
            }
        }
    }
    if (true) {
        D2D1_POINT_2F p0 = { m_xStart + widthLeft, m_yStart + heightPr + (1 - ((float)(*m_vecIntMinuteBar)[0].m_vol) / (float)m_volMax) * heightVol };
        D2D1_POINT_2F p1 = { m_xStart + widthLeft, m_yStart + heightPr + heightVol };
        m_d2dWndDep->m_pD2D1HwndRenderTarget->DrawLine(p0, p1, m_d2dWndDep->m_pD2DSolidColorBrushBlack, 1);
        for (size_t i { 1 }; i <= 239; ++i) {
            p0.x += widthPrVol / 240.f;
            p1.x += widthPrVol / 240.f;
            p0.y = m_yStart + heightPr + (1 - ((float)(*m_vecIntMinuteBar)[i].m_vol) / (float)m_volMax) * heightVol;
            m_d2dWndDep->m_pD2D1HwndRenderTarget->DrawLine(p0, p1, m_d2dWndDep->m_pD2DSolidColorBrushBlack, 1);
        }
    }
    if (false) {
        IDWriteTextLayout* pDWriteTextLayout0930;
        {
            std::wstring temp = L"09:30";
            QILD2D::D2dWndIndep::s_pDWriteFactory->CreateTextLayout(temp.c_str(), temp.size(), QILD2D::D2dWndIndep::s_pDWriteTextFormat14, 200 /*width of layout box*/, 100 /*height of layout box*/, &pDWriteTextLayout0930);
        }
        IDWriteTextLayout* pDWriteTextLayout1030;
        {
            std::wstring temp = L"10:30";
            QILD2D::D2dWndIndep::s_pDWriteFactory->CreateTextLayout(temp.c_str(), temp.size(), QILD2D::D2dWndIndep::s_pDWriteTextFormat14, 200 /*width of layout box*/, 100 /*height of layout box*/, &pDWriteTextLayout1030);
        }
        IDWriteTextLayout* pDWriteTextLayout1300;
        {
            std::wstring temp = L"13:00";
            QILD2D::D2dWndIndep::s_pDWriteFactory->CreateTextLayout(temp.c_str(), temp.size(), QILD2D::D2dWndIndep::s_pDWriteTextFormat14, 200 /*width of layout box*/, 100 /*height of layout box*/, &pDWriteTextLayout1300);
        }
        IDWriteTextLayout* pDWriteTextLayout1400;
        {
            std::wstring temp = L"14:00";
            QILD2D::D2dWndIndep::s_pDWriteFactory->CreateTextLayout(temp.c_str(), temp.size(), QILD2D::D2dWndIndep::s_pDWriteTextFormat14, 200 /*width of layout box*/, 100 /*height of layout box*/, &pDWriteTextLayout1400);
        }
        IDWriteTextLayout* pDWriteTextLayout1500;
        {
            std::wstring temp = L"15:00";
            QILD2D::D2dWndIndep::s_pDWriteFactory->CreateTextLayout(temp.c_str(), temp.size(), QILD2D::D2dWndIndep::s_pDWriteTextFormat14, 200 /*width of layout box*/, 100 /*height of layout box*/, &pDWriteTextLayout1500);
        }
        m_d2dWndDep->m_pD2D1HwndRenderTarget->DrawTextLayout(D2D1::Point2F(m_xStart + widthLeft + 0, m_yStart + heightPr + heightVol), pDWriteTextLayout0930, m_d2dWndDep->m_pD2DSolidColorBrushBlack);
        pDWriteTextLayout0930->Release();
        m_d2dWndDep->m_pD2D1HwndRenderTarget->DrawTextLayout(D2D1::Point2F(m_xStart + widthLeft + widthPrVol * 0.25, m_yStart + heightPr + heightVol), pDWriteTextLayout1030, m_d2dWndDep->m_pD2DSolidColorBrushBlack);
        pDWriteTextLayout1030->Release();
        m_d2dWndDep->m_pD2D1HwndRenderTarget->DrawTextLayout(D2D1::Point2F(m_xStart + widthLeft + widthPrVol / 2, m_yStart + heightPr + heightVol), pDWriteTextLayout1300, m_d2dWndDep->m_pD2DSolidColorBrushBlack);
        pDWriteTextLayout1300->Release();
        m_d2dWndDep->m_pD2D1HwndRenderTarget->DrawTextLayout(D2D1::Point2F(m_xStart + widthLeft + widthPrVol * 0.75, m_yStart + heightPr + heightVol), pDWriteTextLayout1400, m_d2dWndDep->m_pD2DSolidColorBrushBlack);
        pDWriteTextLayout1400->Release();
        m_d2dWndDep->m_pD2D1HwndRenderTarget->DrawTextLayout(D2D1::Point2F(m_xStart + widthLeft + widthPrVol, m_yStart + heightPr + heightVol), pDWriteTextLayout1500, m_d2dWndDep->m_pD2DSolidColorBrushBlack);
        pDWriteTextLayout1500->Release();
    }
}

LRESULT CALLBACK D2dWndDepLimitPeriodText::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg) {
    case WM_ERASEBKGND: {
        return true /*avoid flicker*/;
    }
    case WM_CLOSE: {
        QILD2D::D2dWndDepLimitPeriodText* ptr = reinterpret_cast<QILD2D::D2dWndDepLimitPeriodText*>(static_cast<LONG_PTR>(GetWindowLongPtr(hWnd, GWLP_USERDATA)));
        for (auto& e : ptr->m_vecPDWriteTextLayout)
            e->Release();
        QILD2D::D2dWndIndep::SafeRelease(&(ptr->m_D2dWndDep.m_pD2DSolidColorBrushGreen));
        QILD2D::D2dWndIndep::SafeRelease(&(ptr->m_D2dWndDep.m_pD2DSolidColorBrushRed));
        QILD2D::D2dWndIndep::SafeRelease(&(ptr->m_D2dWndDep.m_pD2DSolidColorBrushGray));
        QILD2D::D2dWndIndep::SafeRelease(&(ptr->m_D2dWndDep.m_pD2DSolidColorBrushLightGray));
        QILD2D::D2dWndIndep::SafeRelease(&(ptr->m_D2dWndDep.m_pD2DSolidColorBrushBlack));
        QILD2D::D2dWndIndep::SafeRelease(&(ptr->m_D2dWndDep.m_pD2D1HwndRenderTarget));
        delete ptr;
        ptr = nullptr;
        DestroyWindow(hWnd);
        return 0;
    }
    case WM_CREATE: {
        QILD2D::D2dWndDepLimitPeriodText* ptr = new QILD2D::D2dWndDepLimitPeriodText;
        SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(ptr));
        // 并行线程
        if (true) {
            std::vector<std::jthread> vecThread;
            // 并行线程
            vecThread.emplace_back([&]() {
                ptr->m_vecPDWriteTextLayout.resize(200);
                for (size_t i = 0; i < 200 /*A large enough number just for feature test*/; ++i) {
                    {
                        std::wstring temp = std::to_wstring(i);
                        temp += L" Quant Is Learning. 量化正在学习。测试永久免费商用字体。 ";
                        temp += std::to_wstring(i);
                        // D2D1_SIZE_F renderTargetSize = ptr->m_D2dWndDep.m_pD2D1HwndRenderTarget->GetSize();
                        QILD2D::D2dWndIndep::s_pDWriteFactory->CreateTextLayout(temp.c_str(), temp.size(), QILD2D::D2dWndIndep::s_pDWriteTextFormat16, 0 /*可使用renderTargetSize*/, 0 /*可使用renderTargetSize*/, &ptr->m_vecPDWriteTextLayout[i]);
                        ptr->m_vecPDWriteTextLayout[i]->SetWordWrapping(DWRITE_WORD_WRAPPING_NO_WRAP); // Set the word wrapping mode to DWRITE_WORD_WRAPPING_NO_WRAP
                        DWRITE_TEXT_METRICS textMetrics;
                        ptr->m_vecPDWriteTextLayout[i]->GetMetrics(&textMetrics);
                        float width = textMetrics.widthIncludingTrailingWhitespace;
                        if (width > ptr->m_maxWidthVecPDWriteTextLayout) {
                            ptr->m_maxWidthVecPDWriteTextLayout = width;
                        }
                    }
                }
            });
        }
        HRESULT hr = S_OK;
        if (SUCCEEDED(hr)) {
            RECT rc;
            GetClientRect(hWnd, &rc);
            hr = QILD2D::D2dWndIndep::s_pD2D1Factory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(hWnd, D2D1::SizeU(rc.right, rc.bottom)), &((*ptr).m_D2dWndDep.m_pD2D1HwndRenderTarget));
        }
        if (SUCCEEDED(hr)) {
            hr = (*ptr).m_D2dWndDep.m_pD2D1HwndRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &((*ptr).m_D2dWndDep.m_pD2DSolidColorBrushBlack));
            hr = (*ptr).m_D2dWndDep.m_pD2D1HwndRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::LightGray), &((*ptr).m_D2dWndDep.m_pD2DSolidColorBrushLightGray));
            hr = (*ptr).m_D2dWndDep.m_pD2D1HwndRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Gray), &((*ptr).m_D2dWndDep.m_pD2DSolidColorBrushGray));
            hr = (*ptr).m_D2dWndDep.m_pD2D1HwndRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Red), &((*ptr).m_D2dWndDep.m_pD2DSolidColorBrushRed));
            hr = (*ptr).m_D2dWndDep.m_pD2D1HwndRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Green), &((*ptr).m_D2dWndDep.m_pD2DSolidColorBrushGreen));
        }
        if (!SUCCEEDED(hr)) {
            delete ptr;
            ptr = nullptr;
        }
        return 1;
    }
    case WM_PAINT: {
        // PAINTSTRUCT ps;
        // HDC hDC = BeginPaint(hWnd, &ps);
        // SetBkMode(hDC, TRANSPARENT);
        RECT rc;
        GetClientRect(hWnd, &rc);
        QILD2D::D2dWndDepLimitPeriodText* ptr = reinterpret_cast<QILD2D::D2dWndDepLimitPeriodText*>(static_cast<LONG_PTR>(GetWindowLongPtr(hWnd, GWLP_USERDATA)));
        ptr->m_D2dWndDep.m_pD2D1HwndRenderTarget->BeginDraw();
        // All painting occurs here, between BeginPaint and EndPaint.
        ptr->m_D2dWndDep.m_pD2D1HwndRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));
        auto idxVScroll = GetScrollPos(hWnd, SB_VERT); // 垂直
        auto idxHScroll = GetScrollPos(hWnd, SB_HORZ); // 水平
        if (true) {
            IDWriteTextLayout* pDWriteTextLayoutTemp;
            int32_t lineCount = std::ceil((rc.bottom - rc.top) / QILD2D::D2dWndIndep::s_lineHeight16);
            for (size_t i = 0; i < lineCount; ++i) {
                if (i + idxVScroll < ptr->m_vecPDWriteTextLayout.size()) {
                    ptr->m_D2dWndDep.m_pD2D1HwndRenderTarget->DrawTextLayout(D2D1::Point2F(0 - idxHScroll, i * QILD2D::D2dWndIndep::s_lineHeight16), ptr->m_vecPDWriteTextLayout[i + idxVScroll], ptr->m_D2dWndDep.m_pD2DSolidColorBrushBlack);
                }
            }
        }
        // FillRect(hDC, &ps.rcPaint, //(HBRUSH)GetStockObject(WHITE_BRUSH));
        //     CreateSolidBrush(RGB((rand() % (255 + 1)), (rand() % (255 + 1)), (rand() % (255 + 1)))));
        ptr->m_D2dWndDep.m_pD2D1HwndRenderTarget->EndDraw();
        // EndPaint(hWnd, &ps);
        ValidateRect(hWnd, NULL);
        return 0;
    }
    // https://learn.microsoft.com/en-us/windows/win32/controls/scroll-text-in-scroll-bars
    case WM_SIZE: {
        QILD2D::D2dWndDepLimitPeriodText* ptr = reinterpret_cast<QILD2D::D2dWndDepLimitPeriodText*>(static_cast<LONG_PTR>(GetWindowLongPtr(hWnd, GWLP_USERDATA)));
        //  Set the vertical scrolling range and page size
        {
            SCROLLINFO si;
            si.cbSize = sizeof(si);
            si.fMask = SIF_RANGE | SIF_PAGE;
            si.nMin = 0;
            si.nMax = ptr->m_vecPDWriteTextLayout.size();
            si.nPage = std::ceil(HIWORD(lParam) /*height*/ / QILD2D::D2dWndIndep::s_lineHeight16);
            SetScrollInfo(hWnd, SB_VERT, &si, TRUE);
        }
        // Set the horizontal scrolling range and page size.
        {
            SCROLLINFO si;
            si.cbSize = sizeof(si);
            si.fMask = SIF_RANGE | SIF_PAGE;
            si.nMin = 0;
            si.nMax = ptr->m_maxWidthVecPDWriteTextLayout;
            si.nPage = LOWORD(lParam);
            SetScrollInfo(hWnd, SB_HORZ, &si, TRUE);
        }
        D2D1_SIZE_U size = D2D1::SizeU(LOWORD(lParam) /*width*/, HIWORD(lParam) /*height*/);
        ptr->m_D2dWndDep.m_pD2D1HwndRenderTarget->Resize(size);
        // InvalidateRect(hWnd, NULL, FALSE);
        return 0;
    }
    // https://learn.microsoft.com/en-us/windows/win32/controls/scroll-text-in-scroll-bars
    case WM_VSCROLL: {
        SCROLLINFO si;
        // Get all the vertial scroll bar information.
        si.cbSize = sizeof(si);
        si.fMask = SIF_ALL;
        GetScrollInfo(hWnd, SB_VERT, &si);
        switch (LOWORD(wParam)) {
        case SB_TOP:
            si.nPos = si.nMin;
            break; // User clicked the HOME keyboard key.
        case SB_BOTTOM:
            si.nPos = si.nMax;
            break; // User clicked the END keyboard key.
        case SB_LINEUP:
            si.nPos -= 1;
            break; // User clicked the top arrow.
        case SB_LINEDOWN:
            si.nPos += 1;
            break; // User clicked the bottom arrow.
        case SB_PAGEUP:
            si.nPos -= si.nPage;
            break; // User clicked the scroll bar shaft above the scroll box.
        case SB_PAGEDOWN:
            si.nPos += si.nPage;
            break; // User clicked the scroll bar shaft below the scroll box.
        case SB_THUMBTRACK:
            si.nPos = si.nTrackPos;
            break; // User dragged the scroll box.
        default:
            break;
        }
        // Set the position and then retrieve it.  Due to adjustments by Windows it may not be the same as the value set.
        si.fMask = SIF_POS;
        SetScrollInfo(hWnd, SB_VERT, &si, TRUE);
        GetScrollInfo(hWnd, SB_VERT, &si);
        InvalidateRect(hWnd, NULL, FALSE);
        return 0;
    }
    // https://learn.microsoft.com/en-us/windows/win32/controls/scroll-text-in-scroll-bars
    case WM_HSCROLL: {
        SCROLLINFO si;
        // Get all the horizontal scroll bar information.
        si.cbSize = sizeof(si);
        si.fMask = SIF_ALL;
        GetScrollInfo(hWnd, SB_HORZ, &si);
        switch (LOWORD(wParam)) {
        case SB_TOP:
            si.nPos = si.nMin;
            break; // User clicked the HOME keyboard key.
        case SB_BOTTOM:
            si.nPos = si.nMax;
            break; // User clicked the END keyboard key.
        case SB_LINEUP:
            si.nPos -= 1;
            break; // User clicked the top arrow.
        case SB_LINEDOWN:
            si.nPos += 1;
            break; // User clicked the bottom arrow.
        case SB_PAGEUP:
            si.nPos -= si.nPage;
            break; // User clicked the scroll bar shaft above the scroll box.
        case SB_PAGEDOWN:
            si.nPos += si.nPage;
            break; // User clicked the scroll bar shaft below the scroll box.
        case SB_THUMBTRACK:
            si.nPos = si.nTrackPos;
            break; // User dragged the scroll box.
        default:
            break;
        }
        // Set the position and then retrieve it.  Due to adjustments by Windows it may not be the same as the value set.
        si.fMask = SIF_POS;
        SetScrollInfo(hWnd, SB_HORZ, &si, TRUE);
        GetScrollInfo(hWnd, SB_HORZ, &si);
        InvalidateRect(hWnd, NULL, FALSE);
        return 0;
    }
    // https://learn.microsoft.com/en-us/windows/win32/controls/scroll-text-in-scroll-bars
    case WM_KEYDOWN: {
        // vertical
        {
            WORD wScrollNotify = 0xFFFF;
            switch (wParam) {
            case VK_UP:
                wScrollNotify = SB_LINEUP;
                break;
            case VK_PRIOR:
                wScrollNotify = SB_PAGEUP;
                break;
            case VK_NEXT:
                wScrollNotify = SB_PAGEDOWN;
                break;
            case VK_DOWN:
                wScrollNotify = SB_LINEDOWN;
                break;
            case VK_HOME:
                wScrollNotify = SB_TOP;
                break;
            case VK_END:
                wScrollNotify = SB_BOTTOM;
                break;
            }
            if (wScrollNotify != -1)
                SendMessage(hWnd, WM_VSCROLL, MAKELONG(wScrollNotify, 0), 0L);
        }
        // horizontal
        {
            WORD wScrollNotify = 0xFFFF;
            switch (wParam) {
            case VK_LEFT:
                wScrollNotify = SB_LINELEFT;
                break;
            case VK_RIGHT:
                wScrollNotify = SB_LINERIGHT;
                break;
            }
            if (wScrollNotify != -1)
                SendMessage(hWnd, WM_HSCROLL, MAKELONG(wScrollNotify, 0), 0L);
        }
        return 0;
    }
    case WM_MOUSEWHEEL: {
        SCROLLINFO si;
        // Get all the vertial scroll bar information.
        si.cbSize = sizeof(si);
        si.fMask = SIF_ALL;
        GetScrollInfo(hWnd, SB_VERT, &si);
        si.nPos -= GET_WHEEL_DELTA_WPARAM(wParam);
        // Set the position and then retrieve it.  Due to adjustment by Windows it may not be the same as the value set.
        si.fMask = SIF_POS;
        SetScrollInfo(hWnd, SB_VERT, &si, TRUE);
        GetScrollInfo(hWnd, SB_VERT, &si);
        InvalidateRect(hWnd, NULL, FALSE);
        return 0;
    }
    default:
        break;
    }
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

}
