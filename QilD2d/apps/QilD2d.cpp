// Copyright (c) 2025-present Mason Zhao MasonSZhao@qq.com

// QilD2d.cpp : Defines the entry point for the application.

#include "QilD2d.h"

LRESULT CALLBACK WndProcMain(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR lpCmdLine,
    _In_ int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // Use HeapSetInformation to specify that the process should terminate if the heap manager detects an error in any heap used by the process.
    HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);

    // AllocConsole();

    // WNDCLASS
    {
        WNDCLASS wc {};
        wc.lpfnWndProc = WndProcMain;
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

    return (int)msg.wParam;
}

LRESULT CALLBACK WndProcMain(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg) {
    case WM_ERASEBKGND: {
        return true /*avoid flicker*/;
    }
    case WM_NCDESTROY: {
        PostQuitMessage(0);
        return 0;
    }
    case WM_CREATE: {
        return 0;
    }
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hDC = BeginPaint(hWnd, &ps);
        SetBkMode(hDC, TRANSPARENT);
        RECT rc;
        GetClientRect(hWnd, &rc);
        FillRect(hDC, &ps.rcPaint, //(HBRUSH)GetStockObject(WHITE_BRUSH));
            CreateSolidBrush(RGB((rand() % (255 + 1)), (rand() % (255 + 1)), (rand() % (255 + 1)))));
        EndPaint(hWnd, &ps);
        ValidateRect(hWnd, NULL);
        return 0;
    }
    default:
        break;
    }
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}