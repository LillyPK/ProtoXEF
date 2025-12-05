#ifndef PROTOXEF_WINDOW_H
#define PROTOXEF_WINDOW_H

#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>

namespace ProtoXEF {

class Window {
public:
    Window(const wchar_t* title, int width = 800, int height = 600);
    ~Window();

    bool Create(HINSTANCE hInstance);
    void Show(int nCmdShow);
    int MessageLoop();

    HWND GetHandle() const { return m_hwnd; }

private:
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

    HWND m_hwnd;
    const wchar_t* m_title;
    int m_width;
    int m_height;

    static const wchar_t* CLASS_NAME;
};

} // namespace ProtoXEF

#endif // PROTOXEF_WINDOW_H
