#include "GameApp.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    GameApp gameApp(800, 600);

    gameApp.Init();
    gameApp.Run(); // main loop (update, render)
    gameApp.Release();

    return (int)1;
}
