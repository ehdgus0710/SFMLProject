#include "stdafx.h"
#include "SceneManager.h"

#include "SceneDev1.h"
#include "SceneDev2.h"

void SceneManager::Init()
{
	sceneVec.push_back(new SceneDev1());
	sceneVec.push_back(new SceneDev2());

	for (auto& scene : sceneVec)
	{
		scene->Init();
	}

	currentScene = startScene;
	sceneVec[(int)currentScene]->Enter();
}

void SceneManager::Release()
{
	for (auto& scene : sceneVec)
	{
		scene->Release();
		delete scene;
	}

	sceneVec.clear();
}

void SceneManager::ChangeScene(SceneIds id)
{
	sceneVec[(int)currentScene]->Exit();
	currentScene = id;
	sceneVec[(int)currentScene]->Enter();
}

void SceneManager::Update(float dt)
{
	sceneVec[(int)currentScene]->Update(dt);
}

void SceneManager::Render(sf::RenderWindow& window)
{
	sceneVec[(int)currentScene]->Render(window);
}
