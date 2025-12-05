#include "window/window.h"

namespace ProtoXEF {

const wchar_t* Window::CLASS_NAME = L"ProtoXEF_Window_Class";

Window::Window(const wchar_t* title, int width, int height)
    : m_hwnd(nullptr), m_title(title), m_width(width), m_height(height)
{
}

Window::~Window()
{
    if (m_hwnd)
    {
        DestroyWindow(m_hwnd);
    }
}

bool Window::Create(HINSTANCE hInstance)
{
    // Register the window class
    WNDCLASS wc = { };
    wc.lpfnWndProc = Window::WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    RegisterClass(&wc);

    // Create the window
    m_hwnd = CreateWindowEx(
        0,                              // Optional window styles
        CLASS_NAME,                     // Window class
        m_title,                        // Window title
        WS_OVERLAPPEDWINDOW,            // Window style

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, m_width, m_height,

        nullptr,       // Parent window
        nullptr,       // Menu
        hInstance,     // Instance handle
        this           // Pass 'this' pointer to WM_CREATE
    );

    return (m_hwnd != nullptr);
}

void Window::Show(int nCmdShow)
{
    ShowWindow(m_hwnd, nCmdShow);
}

int Window::MessageLoop()
{
    MSG msg = { };
    while (GetMessage(&msg, nullptr, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return static_cast<int>(msg.wParam);
}

LRESULT CALLBACK Window::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    Window* pThis = nullptr;

    if (uMsg == WM_NCCREATE)
    {
        // Get the pointer we passed in CreateWindowEx
        CREATESTRUCT* pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
        pThis = reinterpret_cast<Window*>(pCreate->lpCreateParams);
        SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pThis));

        pThis->m_hwnd = hwnd;
    }
    else
    {
        pThis = reinterpret_cast<Window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
    }

    if (pThis)
    {
        return pThis->HandleMessage(uMsg, wParam, lParam);
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

LRESULT Window::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(m_hwnd, &ps);
            FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
            EndPaint(m_hwnd, &ps);
        }
        return 0;
    }

    return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
}

} // namespace ProtoXEF
