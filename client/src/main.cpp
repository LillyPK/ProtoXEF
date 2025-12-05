#include "window/window.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                     PWSTR pCmdLine, int nCmdShow)
{
    ProtoXEF::Window window(L"ProtoXEF Client", 800, 600);

    if (!window.Create(hInstance))
    {
        return -1;
    }

    window.Show(nCmdShow);

    return window.MessageLoop();
}
