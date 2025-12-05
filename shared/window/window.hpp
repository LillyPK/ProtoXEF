#ifndef PROTOXEF_WINDOW_H
#define PROTOXEF_WINDOW_H

#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>

namespace ProtoXEF {

class Window {
public:
    struct Config {
        const wchar_t* title;
        int width;
        int height;
        DWORD style = WS_OVERLAPPEDWINDOW;
    };

    Window(const Config& cfg);
    virtual ~Window();

    bool Create(HINSTANCE hInstance);
    void Show(int nCmdShow);
    int MessageLoop();

    HWND GetHandle() const { return m_hwnd; }

protected:
    virtual void OnResize(int width, int height) {}
    virtual void Draw(HDC dc, const RECT& area) {}
    virtual void OnDestroy() {}

    virtual bool HandleCustomMessage(UINT msg, WPARAM w, LPARAM l, LRESULT& result) {
        return false;
    }

    HWND m_hwnd = nullptr;

private:
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM w, LPARAM l);
    LRESULT HandleMessage(UINT msg, WPARAM w, LPARAM l);

    Config m_cfg;
    static const wchar_t* CLASS_NAME;
};

} // namespace ProtoXEF

#endif
