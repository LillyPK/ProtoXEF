#pragma once
#include <windows.h>
#include <uxtheme.h>
#include <dwmapi.h>

namespace ProtoXEF {

// Windows 11 Build number
constexpr DWORD WIN11_BUILD = 22000;

inline bool IsWindows11OrGreater() {
    typedef LONG (WINAPI *RtlGetVersionPtr)(PRTL_OSVERSIONINFOW);

    HMODULE ntdll = GetModuleHandleW(L"ntdll.dll");
    if (!ntdll) return false;

    RtlGetVersionPtr RtlGetVersion =
        (RtlGetVersionPtr)GetProcAddress(ntdll, "RtlGetVersion");

    if (!RtlGetVersion) return false;

    RTL_OSVERSIONINFOW osInfo = {};
    osInfo.dwOSVersionInfoSize = sizeof(osInfo);

    if (RtlGetVersion(&osInfo) == 0) {
        return osInfo.dwBuildNumber >= WIN11_BUILD;
    }

    return false;
}

// Enable dark mode for window title bar
inline void EnableDarkModeForWindow(HWND hwnd, bool dark) {
    // DWMWA_USE_IMMERSIVE_DARK_MODE = 20
    BOOL value = dark ? TRUE : FALSE;
    DwmSetWindowAttribute(hwnd, 20, &value, sizeof(value));
}

// Apply modern backdrop effect (Windows 11)
enum class BackdropType {
    None = 1,      // DWMSBT_DISABLE
    Mica = 2,      // DWMSBT_MAINWINDOW (auto Mica)
    Acrylic = 3,   // DWMSBT_TRANSIENTWINDOW
    MicaAlt = 4    // DWMSBT_TABBEDWINDOW
};

inline void SetBackdropType(HWND hwnd, BackdropType type) {
    if (!IsWindows11OrGreater()) return;

    // DWMWA_SYSTEMBACKDROP_TYPE = 38
    int value = static_cast<int>(type);
    DwmSetWindowAttribute(hwnd, 38, &value, sizeof(value));
}

// Apply modern theme to standard controls
inline void ApplyModernTheme(HWND hwnd, bool darkMode) {
    if (darkMode) {
        SetWindowTheme(hwnd, L"DarkMode_Explorer", nullptr);
    } else {
        SetWindowTheme(hwnd, L"Explorer", nullptr);
    }
}

// Enable rounded corners (Windows 11)
enum class CornerPreference {
    Default = 0,      // Let system decide
    DoNotRound = 1,   // Never round
    Round = 2,        // Always round
    RoundSmall = 3    // Small rounded corners
};

inline void SetWindowCornerPreference(HWND hwnd, CornerPreference pref) {
    if (!IsWindows11OrGreater()) return;

    // DWMWA_WINDOW_CORNER_PREFERENCE = 33
    int value = static_cast<int>(pref);
    DwmSetWindowAttribute(hwnd, 33, &value, sizeof(value));
}

// Apply all modern styling to a window
inline void ApplyModernStyling(HWND hwnd, bool darkMode) {
    EnableDarkModeForWindow(hwnd, darkMode);
    SetWindowCornerPreference(hwnd, CornerPreference::Round);

    if (IsWindows11OrGreater()) {
        SetBackdropType(hwnd, BackdropType::Mica);
    }
}

} // namespace ProtoXEF
