#include "Framework.h"

#include "InputManager.h"
#include "ResourcesManager.h"
#include "TimeManager.h"
#include "WindowManager.h"
#include "Core.h"


void Framework::init()
{

    ResourcesManager<sf::Texture>::GetInstance().Load("Bee", "test/test.png");
    renderWindow = WindowManager::GetInstance().GetRenderWindow();
}

void Framework::Update()
{
    sf::Event event;
    while (renderWindow->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            renderWindow->close();
        //InputManager::GetInstance().UpdateEvent(event);
    }
}

Framework::Framework()
{
}

Framework::~Framework()
{
}
