#include "stdafx.h"
#include "Scene.h"

Scene::Scene(const SceneIds id)
	: id(id)
{
}

void Scene::Init()
{
	for (auto object : gameObjectList)
	{
		object->Init();
	}
}

void Scene::Release()
{
	for (auto object : gameObjectList)
	{
		object->Release();
		delete object;
	}
	gameObjectList.clear();
}

void Scene::Enter()
{
	for (auto object : gameObjectList)
	{
		object->Reset();
	}
}

void Scene::Exit()
{
	
}

void Scene::Update(float deltaTime)
{
	for (auto object : gameObjectList)
	{
		if (!object->IsActive())
			continue;

		object->Update(deltaTime);
	}
}

void Scene::Render(sf::RenderWindow& window)
{
	for (auto object : gameObjectList)
	{
		if (!object->IsActive())
			continue;

		object->Render(window);
	}
}

GameObject* Scene::AddGameObject(GameObject* obj)
{
	if (std::find(gameObjectList.begin(), gameObjectList.end(), obj) == gameObjectList.end())
	{
		gameObjectList.push_back(obj);
	}
	return obj;
}

void Scene::RemoveGameObject(GameObject* obj)
{
	gameObjectList.remove(obj);
}

GameObject* Scene::FindGameObject(const std::string& name)
{
	for (auto object : gameObjectList)
	{
		if (object->GetName() == name)
		{
			return object;
		}
	}

	return nullptr;
}

int Scene::FindGameObjectAll(const std::string& name, std::list<GameObject*>& list)
{
	int currnetCount = 0;
	for (auto object : gameObjectList)
	{
		if (object->GetName() == name)
		{
			++currnetCount;
			list.push_back(object);
		}
	}
	return 0;
}
