#include "window/window.hpp"

namespace ProtoXEF {

const wchar_t* Window::CLASS_NAME = L"ProtoXEF_Window_Class";

Window::Window(const Config& cfg)
    : m_cfg(cfg)
{
}

Window::~Window() {
    if (m_hwnd) {
        DestroyWindow(m_hwnd);
    }
}

bool Window::Create(HINSTANCE hInstance) {
    // Register class only once
    static bool registered = false;
    if (!registered) {
        WNDCLASS wc = {};
        wc.lpfnWndProc   = Window::WindowProc;
        wc.hInstance     = hInstance;
        wc.lpszClassName = CLASS_NAME;
        wc.hCursor       = LoadCursor(nullptr, IDC_ARROW);
        wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
        RegisterClass(&wc);
        registered = true;
    }

    m_hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        m_cfg.title,
        m_cfg.style,
        CW_USEDEFAULT, CW_USEDEFAULT,
        m_cfg.width, m_cfg.height,
        nullptr,
        nullptr,
        hInstance,
        this
    );

    return m_hwnd != nullptr;
}

void Window::Show(int nCmdShow) {
    ShowWindow(m_hwnd, nCmdShow);
}

int Window::MessageLoop() {
    MSG msg = {};
    while (GetMessage(&msg, nullptr, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int)msg.wParam;
}

LRESULT CALLBACK Window::WindowProc(HWND hwnd, UINT msg, WPARAM w, LPARAM l) {
    Window* pThis = nullptr;

    if (msg == WM_NCCREATE) {
        auto cs = reinterpret_cast<CREATESTRUCT*>(l);
        pThis = reinterpret_cast<Window*>(cs->lpCreateParams);
        SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pThis));
        pThis->m_hwnd = hwnd;
    } else {
        pThis = reinterpret_cast<Window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
    }

    if (pThis) {
        return pThis->HandleMessage(msg, w, l);
    }

    return DefWindowProc(hwnd, msg, w, l);
}

LRESULT Window::HandleMessage(UINT msg, WPARAM w, LPARAM l) {
    // Give derived classes a chance to intercept any message
    LRESULT result = 0;
    if (HandleCustomMessage(msg, w, l, result)) {
        return result;
    }

    switch (msg) {

    case WM_SIZE: {
        int width  = LOWORD(l);
        int height = HIWORD(l);
        OnResize(width, height);
        return 0;
    }

    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC dc = BeginPaint(m_hwnd, &ps);
        Draw(dc, ps.rcPaint);
        EndPaint(m_hwnd, &ps);
        return 0;
    }

    case WM_DESTROY:
        OnDestroy();
        return 0;
    }

    return DefWindowProc(m_hwnd, msg, w, l);
}

} // namespace ProtoXEF
