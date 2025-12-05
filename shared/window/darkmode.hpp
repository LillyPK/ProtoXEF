#pragma once
#include <windows.h>
#include <winreg.h>

inline bool IsSystemDarkMode() {
    DWORD value = 0;
    DWORD size  = sizeof(value);

    const wchar_t* path =
        L"Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize";

    if (RegGetValueW(
            HKEY_CURRENT_USER,
            path,
            L"AppsUseLightTheme",
            RRF_RT_REG_DWORD,
            nullptr,
            &value,
            &size) == ERROR_SUCCESS)
    {
        return value == 0;
    }

    return false;
}
