#include "window/window.hpp"
#include "window/darkmode.hpp"

namespace ProtoXEF {

constexpr int IDC_TOGGLE = 1001;

class ServerWindow : public Window {
public:
    ServerWindow()
        : Window({ L"ProtoXEF Server", 520, 320 })
    {}

protected:
    void OnCreate() {
        bool dark = IsSystemDarkMode();
        COLORREF backgroundColor = dark ? RGB(32,32,32) : RGB(255,255,255);
        m_background = CreateSolidBrush(backgroundColor);

        DWORD labelStyle = WS_CHILD | WS_VISIBLE;
        DWORD editStyle = WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT;

        m_lblIp = CreateWindowExW(0, L"STATIC", L"Server Local IP Address:",
            labelStyle, 20, 20, 250, 20, m_hwnd, nullptr, nullptr, nullptr);

        m_ipDisplay = CreateWindowExW(0, L"STATIC", L"192.168.x.x",
            labelStyle, 20, 50, 200, 20, m_hwnd, nullptr, nullptr, nullptr);

        m_lblUser = CreateWindowExW(0, L"STATIC", L"Username:",
            labelStyle, 20, 95, 200, 20, m_hwnd, nullptr, nullptr, nullptr);

        m_editUser = CreateWindowExW(0, L"EDIT", L"",
            editStyle, 20, 120, 300, 25, m_hwnd, nullptr, nullptr, nullptr);

        m_lblPass = CreateWindowExW(0, L"STATIC", L"Password:",
            labelStyle, 20, 165, 200, 20, m_hwnd, nullptr, nullptr, nullptr);

        m_editPass = CreateWindowExW(0, L"EDIT", L"",
            editStyle | ES_PASSWORD, 20, 190, 300, 25, m_hwnd,
            nullptr, nullptr, nullptr);

        m_toggle = CreateWindowExW(0, L"BUTTON",
            L"Enable Username and Password",
            WS_CHILD | WS_VISIBLE | BS_CHECKBOX,
            20, 230, 260, 24, m_hwnd, (HMENU)IDC_TOGGLE, nullptr, nullptr);

        SendMessage(m_toggle, BM_SETCHECK, BST_UNCHECKED, 0);
        EnableWindow(m_editUser, FALSE);
        EnableWindow(m_editPass, FALSE);
    }

    void Draw(HDC dc, const RECT& area) override {
        FillRect(dc, &area, m_background);
    }

    bool HandleCustomMessage(UINT msg, WPARAM w, LPARAM l, LRESULT& out) override {
        if (msg == WM_CREATE) {
            OnCreate();
            out = 0;
            return true;
        }

        if (msg == WM_COMMAND) {
            int id = LOWORD(w);
            int code = HIWORD(w);

            if (id == IDC_TOGGLE && code == BN_CLICKED) {
                LRESULT state = SendMessage(m_toggle, BM_GETCHECK, 0, 0);
                bool enabled = (state == BST_CHECKED);
                EnableWindow(m_editUser, enabled);
                EnableWindow(m_editPass, enabled);
                out = 0;
                return true;
            }
        }

        return false;
    }

private:
    HWND m_lblIp = nullptr;
    HWND m_ipDisplay = nullptr;

    HWND m_lblUser = nullptr;
    HWND m_editUser = nullptr;

    HWND m_lblPass = nullptr;
    HWND m_editPass = nullptr;

    HWND m_toggle = nullptr;

    HBRUSH m_background = nullptr;
};

} // namespace ProtoXEF

int WINAPI wWinMain(HINSTANCE h, HINSTANCE, PWSTR, int cmd) {
    ProtoXEF::ServerWindow window;
    if (!window.Create(h)) return -1;
    window.Show(cmd);
    return window.MessageLoop();
}
