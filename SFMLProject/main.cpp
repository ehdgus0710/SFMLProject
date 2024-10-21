#include "stdafx.h"
#include "Core.h"
#include "Framework.h"
int main()
{
    Framework framework;

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    WindowManager::GetInstance().init({ 1920, 1080 }, "haha");
    auto renderWindow = WindowManager::GetInstance().GetRenderWindow();
    
    framework.init();
    
    while (renderWindow->isOpen())
    {
        framework.Update();

        // 랜더 매니저에게 전달
        renderWindow->clear();
        renderWindow->draw(shape);
        renderWindow->display();
    }

    return 0;
}