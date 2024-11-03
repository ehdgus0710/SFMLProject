#include "stdafx.h"
#include "Scene.h"
#include "Camera.h"

Scene::Scene(const SceneIds id)
	: id(id)
	, cameraSpeed(500.f)
	, mainCamera(nullptr)
	, uICamera(nullptr)
{
	gameObjectVector.resize((int)RenderLayer::End);
	cameraPosition = sf::Vector2f::zero;

	mainCamera = new Camera(WindowManager::GetInstance().GetRenderWindow()->getDefaultView(), CameraType::Main);
	uICamera = new Camera(WindowManager::GetInstance().GetRenderWindow()->getDefaultView(), CameraType::UI);
}

Scene::~Scene()
{
	if (mainCamera != nullptr)
	{
		delete mainCamera;
		mainCamera = nullptr;
	}
	if (uICamera != nullptr)
	{
		delete uICamera;
		uICamera = nullptr;
	}
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
	WindowManager::GetInstance().GetRenderWindow()->setView(mainCamera->GetView());

	for (int i = 0; i < (int)RenderLayer::UI; ++i)
	{
		for (auto& object : gameObjectVector[i])
		{
			if (!object->IsActive())
				continue;

			object->Render(window);
		}
	}
	WindowManager::GetInstance().GetRenderWindow()->setView(uICamera->GetView());

	for (int i = (int)RenderLayer::UI; i < (int)RenderLayer::End; ++i)
	{
		for (auto& object : gameObjectVector[i])
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
