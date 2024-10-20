#include "Core.h"
#include "WindowManager.h"
#include "Framework.h"
#include "InputManager.h"

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
        sf::Event event;
        while (renderWindow->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                renderWindow->close();

            //InputManager::GetInstance().UpdateEvent(event);
        }

        framework.Update();

        // 랜더 매니저에게 전달
        renderWindow->clear();
        renderWindow->draw(shape);
        renderWindow->display();
    }

    return 0;
}