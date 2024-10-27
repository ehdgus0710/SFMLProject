#include "stdafx.h"

#include "Framework.h"
#include "Core.h"


void Framework::Init()
{
    ResourcesManager<sf::Texture>::GetInstance().Load("Bee", "graphics/bee.png");
    renderWindow = WindowManager::GetInstance().GetRenderWindow();

    InputManager::GetInstance().Init();
    SceneManager::GetInstance().Init();
    TimeManager::GetInstance().Init();
    ColliderManager::GetInstance().Init();
}

void Framework::Update()
{
    while (renderWindow->isOpen())
    {
        InputManager::GetInstance().UpDownCheck();
        TimeManager::GetInstance().Update();

        while (renderWindow->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                renderWindow->close();
            InputManager::GetInstance().UpdateEvent(&event);
        }

        SceneManager::GetInstance().Update(TimeManager::GetInstance().GetDeletaTime());
        ColliderManager::GetInstance().Update();

        renderWindow->clear();
        SceneManager::GetInstance().Render(*renderWindow);
        renderWindow->display();
    }

}

void Framework::Release()
{
    SceneManager::GetInstance().Release();
}

Framework::Framework()
{
}

Framework::~Framework()
{
    Release();
}
