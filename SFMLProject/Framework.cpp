#include "stdafx.h"

#include "Framework.h"
#include "Core.h"
#include "ImguiManger.h"

void Framework::Init()
{
	renderWindow = WindowManager::GetInstance().GetRenderWindow();

	ImguiManger::GetInstance().Init(*renderWindow);
	InputManager::GetInstance().Init();
	ColliderManager::GetInstance().Init();
	SceneManager::GetInstance().Init();
	TimeManager::GetInstance().Init();
}

void Framework::Update()
{
	while (renderWindow->isOpen())
	{
		InputManager::GetInstance().UpDownCheck();
		TimeManager::GetInstance().Update();

		while (renderWindow->pollEvent(event))
		{
			ImguiManger::GetInstance().ProcessEvent(*renderWindow, event);
			if (event.type == sf::Event::Closed)
				renderWindow->close();
			InputManager::GetInstance().UpdateEvent(&event);
		}
		 
		ImguiManger::GetInstance().Update(*renderWindow, TimeManager::GetInstance().GetTime());

		InputManager::GetInstance().Update(TimeManager::GetInstance().GetDeletaTime());
		if (TimeManager::GetInstance().IsFixedUpdate())
		{
			SceneManager::GetInstance().FixedUpdate(TimeManager::GetInstance().GetFixedDeletaTime());
		}

		SceneManager::GetInstance().Update(TimeManager::GetInstance().GetDeletaTime());
		ColliderManager::GetInstance().Update();

		renderWindow->clear();
		SceneManager::GetInstance().Render(*renderWindow);
		TimeManager::GetInstance().Render(*renderWindow);

		ImguiManger::GetInstance().Render(*renderWindow);
		renderWindow->display();
	}
	
}

void Framework::Release()
{
	SceneManager::GetInstance().Release();
	ImguiManger::GetInstance().Release();
}

Framework::Framework()
	: renderWindow(nullptr)
	, event()
{
}

Framework::~Framework()
{
	Release();
}
