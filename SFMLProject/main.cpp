#include "stdafx.h"
#include "Core.h"
#include "Framework.h"
int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    Framework framework;
    WindowManager::GetInstance().init({ 1920, 1080 }, "haha");
    auto renderWindow = WindowManager::GetInstance().GetRenderWindow();
    
    framework.Init();
    framework.Update();

    //while (renderWindow->isOpen())
    //{

    //    // 랜더 매니저에게 전달
    //    renderWindow->clear();
    //    renderWindow->display();
    //}

    return 0;
}