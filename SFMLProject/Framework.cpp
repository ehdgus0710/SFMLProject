#include "stdafx.h"

#include "Framework.h"
#include "Core.h"


void Framework::init()
{
    ResourcesManager<sf::Texture>::GetInstance().Load("Bee", "graphics/bee.png");
    renderWindow = WindowManager::GetInstance().GetRenderWindow();
}

void Framework::Update()
{
    while (renderWindow->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            renderWindow->close();
        InputManager::GetInstance().UpdateEvent(&event);
    }
}

Framework::Framework()
{
}

Framework::~Framework()
{
}
