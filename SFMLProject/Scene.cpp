#include "stdafx.h"
#include "Scene.h"

Scene::Scene(const SceneIds id)
	: id(id)
{
	gameObjectVector.resize((int)ColliderLayer::End);
}

void Scene::Init()
{
	for (auto& objectVector : gameObjectVector)
	{
		for (auto& object : objectVector)
		{
			object->Awake();
		}
	}
}

void Scene::Release()
{
	for (auto& objectVector : gameObjectVector)
	{
		for (auto& object : objectVector)
		{
			object->Release();
			delete object;
		}
		objectVector.clear();
	}
}

void Scene::Enter()
{
	for (auto& objectVector : gameObjectVector)
	{
		for (auto& object : objectVector)
		{
			object->Start();
		}
	}
}

void Scene::Exit()
{
	
}

void Scene::Update(float deltaTime)
{
	for (auto& objectVector : gameObjectVector)
	{
		for (auto& object : objectVector)
		{
			if (!object->IsActive())
				continue;

			object->Update(deltaTime);
		}
	}
}

void Scene::Render(sf::RenderWindow& window)
{
	for (auto& objectVector : gameObjectVector)
	{
		for (auto& object : objectVector)
		{
			if (!object->IsActive())
				continue;

			object->Render(window);
		}
	}
}

GameObject* Scene::AddGameObject(GameObject* obj, RenderLayer rayer)
{
	if (std::find(gameObjectVector[(int)rayer].begin(), gameObjectVector[(int)rayer].end(), obj) == gameObjectVector[(int)rayer].end())
	{
		gameObjectVector[(int)rayer].push_back(obj);
	}
	return obj;
}

void Scene::RemoveGameObject(GameObject* obj)
{
	for (auto& objectVector : gameObjectVector)
	{
		gameObjectVector.erase(std::find(gameObjectVector.begin(), gameObjectVector.end(), objectVector));
	}
	

	// gameObjectList.remove(obj);
}

GameObject* Scene::FindGameObject(const std::string& name)
{
	/*for (auto object : gameObjectList)
	{
		if (object->GetName() == name)
		{
			return object;
		}
	}

	*/
	return nullptr;
}

int Scene::FindGameObjectAll(const std::string& name, std::list<GameObject*>& list)
{
	/*int currnetCount = 0;
	for (auto object : gameObjectList)
	{
		if (object->GetName() == name)
		{
			++currnetCount;
			list.push_back(object);
		}
	}
	*/
	return 0;
}
