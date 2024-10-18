#include "Core.h"

#include "InputManager.h"
#include "ResourcesManager.h"
#include "TimeManager.h"
#include "WindowManager.h"

int main()
{
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    WindowManager::GetInstance().init({ 1920, 1080 }, "haha");
    auto renderWindow = WindowManager::GetInstance().GetRenderWindow();

    while (renderWindow->isOpen())
    {
        sf::Event event;
        while (renderWindow->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                renderWindow->close();
        }

        renderWindow->clear();
        renderWindow->draw(shape);
        renderWindow->display();
    }

    return 0;
}