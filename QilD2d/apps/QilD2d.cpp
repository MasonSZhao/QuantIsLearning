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

    // MENU
    HMENU hMenu = CreateMenu();
    HMENU hMenuHelp = CreateMenu();
    AppendMenu(hMenu, MF_POPUP, (UINT)hMenuHelp, TEXT("帮助(&H)"));

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
        if (true) {
            IDWriteTextLayout* pDWriteTextLayoutTemp;
            {
                std::wstring temp = L"Quant Is Learning. 量化正在学习。测试永久免费商用字体。";
                QILD2D::D2dWndIndep::s_pDWriteFactory->CreateTextLayout(temp.c_str(), temp.size(), QILD2D::D2dWndIndep::s_pDWriteTextFormat16, 500 /*width of layout box*/, 100 /*height of layout box*/, &pDWriteTextLayoutTemp);
            }
            for (size_t i = 0; i < 25; ++i) {
                switch (i % 5) {
                case 0:
                    ptr->m_D2dWndDep.m_pD2D1HwndRenderTarget->DrawTextLayout(D2D1::Point2F(i * 20, i * 20), pDWriteTextLayoutTemp, ptr->m_D2dWndDep.m_pD2DSolidColorBrushBlack);
                    break;
                case 1:
                    ptr->m_D2dWndDep.m_pD2D1HwndRenderTarget->DrawTextLayout(D2D1::Point2F(i * 20, i * 20), pDWriteTextLayoutTemp, ptr->m_D2dWndDep.m_pD2DSolidColorBrushLightGray);
                    break;
                case 2:
                    ptr->m_D2dWndDep.m_pD2D1HwndRenderTarget->DrawTextLayout(D2D1::Point2F(i * 20, i * 20), pDWriteTextLayoutTemp, ptr->m_D2dWndDep.m_pD2DSolidColorBrushGray);
                    break;
                case 3:
                    ptr->m_D2dWndDep.m_pD2D1HwndRenderTarget->DrawTextLayout(D2D1::Point2F(i * 20, i * 20), pDWriteTextLayoutTemp, ptr->m_D2dWndDep.m_pD2DSolidColorBrushRed);
                    break;
                case 4:
                    ptr->m_D2dWndDep.m_pD2D1HwndRenderTarget->DrawTextLayout(D2D1::Point2F(i * 20, i * 20), pDWriteTextLayoutTemp, ptr->m_D2dWndDep.m_pD2DSolidColorBrushGreen);
                    break;
                default:
                    break;
                }
            }
            pDWriteTextLayoutTemp->Release();
        }
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
    default:
        break;
    }
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

}
