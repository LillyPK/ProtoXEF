#include "window/window.hpp"
#include "window/darkmode.hpp"
#include "window/styling.hpp"

namespace ProtoXEF {

constexpr int IDC_TOGGLE = 1001;

class ClientWindow : public Window {
public:
    ClientWindow()
        : Window({ L"ProtoXEF Client Login", 520, 380 })
    {}

protected:
    void OnCreate() {
        // Get colors based on dark mode
        COLORREF backgroundColor = m_darkMode ? RGB(32,32,32) : RGB(255,255,255);
        COLORREF textColor = m_darkMode ? RGB(255,255,255) : RGB(0,0,0);

        m_background = CreateSolidBrush(backgroundColor);

        DWORD labelStyle = WS_CHILD | WS_VISIBLE | SS_LEFT;
        DWORD editStyle = WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT;

        // Improved spacing - more modern layout
        int leftMargin = 30;
        int topStart = 30;
        int verticalSpacing = 70;
        int labelHeight = 22;
        int editHeight = 32;
        int editWidth = 360;

        // IP Address section
        m_lblIp = CreateWindowExW(0, L"STATIC", L"Server IP Address:",
            labelStyle, leftMargin, topStart, 200, labelHeight,
            m_hwnd, nullptr, nullptr, nullptr);

        m_editIp = CreateWindowExW(WS_EX_CLIENTEDGE, L"EDIT", L"",
            editStyle, leftMargin, topStart + 25, editWidth, editHeight,
            m_hwnd, nullptr, nullptr, nullptr);

        // Username section
        m_lblUser = CreateWindowExW(0, L"STATIC", L"Username:",
            labelStyle, leftMargin, topStart + verticalSpacing, 200, labelHeight,
            m_hwnd, nullptr, nullptr, nullptr);

        m_editUser = CreateWindowExW(WS_EX_CLIENTEDGE, L"EDIT", L"",
            editStyle, leftMargin, topStart + verticalSpacing + 25, editWidth, editHeight,
            m_hwnd, nullptr, nullptr, nullptr);

        // Password section
        m_lblPass = CreateWindowExW(0, L"STATIC", L"Password:",
            labelStyle, leftMargin, topStart + verticalSpacing * 2, 200, labelHeight,
            m_hwnd, nullptr, nullptr, nullptr);

        m_editPass = CreateWindowExW(WS_EX_CLIENTEDGE, L"EDIT", L"",
            editStyle | ES_PASSWORD, leftMargin, topStart + verticalSpacing * 2 + 25,
            editWidth, editHeight, m_hwnd, nullptr, nullptr, nullptr);

        // Toggle checkbox - FIX: BS_AUTOCHECKBOX → BS_CHECKBOX
        m_toggle = CreateWindowExW(0, L"BUTTON",
            L"Require Authentication",
            WS_CHILD | WS_VISIBLE | BS_CHECKBOX,  // ← Corrected here
            leftMargin, topStart + verticalSpacing * 3, 280, 28,
            m_hwnd, (HMENU)IDC_TOGGLE, nullptr, nullptr);

        SendMessage(m_toggle, BM_SETCHECK, BST_UNCHECKED, 0);
        EnableWindow(m_editUser, FALSE);
        EnableWindow(m_editPass, FALSE);

        // Apply modern theme to all controls
        ApplyModernTheme(m_lblIp, m_darkMode);
        ApplyModernTheme(m_editIp, m_darkMode);
        ApplyModernTheme(m_lblUser, m_darkMode);
        ApplyModernTheme(m_editUser, m_darkMode);
        ApplyModernTheme(m_lblPass, m_darkMode);
        ApplyModernTheme(m_editPass, m_darkMode);
        ApplyModernTheme(m_toggle, m_darkMode);
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
                LRESULT currentState = SendMessage(m_toggle, BM_GETCHECK, 0, 0);
                LRESULT newState = (currentState == BST_CHECKED) ? BST_UNCHECKED : BST_CHECKED;
                SendMessage(m_toggle, BM_SETCHECK, newState, 0);

                bool enabled = (newState == BST_CHECKED);
                EnableWindow(m_editUser, enabled);
                EnableWindow(m_editPass, enabled);

                out = 0;
                return true;
            }
        }

        // Handle label text color in dark mode
        if (msg == WM_CTLCOLORSTATIC && m_darkMode) {
            HDC hdcStatic = reinterpret_cast<HDC>(w);
            SetTextColor(hdcStatic, RGB(255, 255, 255));
            SetBkColor(hdcStatic, RGB(32, 32, 32));
            out = reinterpret_cast<LRESULT>(m_background);
            return true;
        }

        return false;
    }

private:
    HWND m_lblIp = nullptr;
    HWND m_editIp = nullptr;
    HWND m_lblUser = nullptr;
    HWND m_editUser = nullptr;
    HWND m_lblPass = nullptr;
    HWND m_editPass = nullptr;
    HWND m_toggle = nullptr;
    HBRUSH m_background = nullptr;
};

} // namespace ProtoXEF

int WINAPI wWinMain(HINSTANCE h, HINSTANCE, PWSTR, int cmd) {
    ProtoXEF::ClientWindow window;
    if (!window.Create(h)) return -1;
    window.Show(cmd);
    return window.MessageLoop();
}
