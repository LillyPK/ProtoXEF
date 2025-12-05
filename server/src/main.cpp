#include "window/window.hpp"

namespace ProtoXEF {

class ServerWindow : public Window {
public:
    ServerWindow()
        : Window({ L"ProtoXEF Server", 800, 600 })
    {}

protected:
    void OnResize(int width, int height) override {
        // server resize handling
    }

    void Draw(HDC dc, const RECT& area) override {
        FillRect(dc, &area, (HBRUSH)(COLOR_WINDOW + 1));
        const wchar_t* text = L"ProtoXEF Server";
        TextOut(dc, 10, 10, text, lstrlenW(text));
    }

    bool HandleCustomMessage(UINT msg, WPARAM w, LPARAM l, LRESULT& out) override {
        // handle server specific messages if needed
        return false;
    }
};

} // namespace ProtoXEF

int WINAPI wWinMain(HINSTANCE h, HINSTANCE, PWSTR, int cmd) {
    ProtoXEF::ServerWindow window;
    if (!window.Create(h)) return -1;
    window.Show(cmd);
    return window.MessageLoop();
}
