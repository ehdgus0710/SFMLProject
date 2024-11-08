#include "stdafx.h"
#include "Scene.h"
#include "Camera.h"

Scene::Scene(const SceneIds id)
	: id(id)
	, cameraSpeed(500.f)
	, mainCamera(nullptr)
	, uICamera(nullptr)
{
	gameObjectVectors.resize((int)LayerType::End);
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
	for (auto& objectVector : gameObjectVectors)
	{
		for (auto& object : objectVector)
		{
			object->Awake();
		}
	}
}

void Scene::Release()
{
	for (auto& objectVector : gameObjectVectors)
	{
		for (auto& object : objectVector)
		{
			object->Release();
			delete object;
		}
		objectVector.clear();
	}
	gameObjectVectors.clear();
}

void Scene::Enter()
{
	for (auto& objectVector : gameObjectVectors)
	{
		for (auto& object : objectVector)
		{
			object->Start();
		}
	}
}

void Scene::Exit()
{
	Release();

	ResourcesManager<sf::Texture>::GetInstance().UnloadAll();
	ResourcesManager<sf::Font>::GetInstance().UnloadAll();
	ResourcesManager<sf::SoundBuffer>::GetInstance().UnloadAll();
}

void Scene::Update(float deltaTime)
{
	for (auto& objectVector : gameObjectVectors)
	{
		for (auto& object : objectVector)
		{
			if (!object->IsActive())
				continue;

			object->Update(deltaTime);
		}
	}

	mainCamera->Update(deltaTime);
	uICamera->Update(deltaTime);
}

void Scene::FixedUpdate(float fixedDeltaTime)
{
	for (auto& objectVector : gameObjectVectors)
	{
		for (auto& object : objectVector)
		{
			if (!object->IsActive())
				continue;

			object->FixedUpdate(fixedDeltaTime);
		}
	}
}

void Scene::Render(sf::RenderWindow& window)
{
	auto& saveView = WindowManager::GetInstance().GetRenderWindow()->getView();

	WindowManager::GetInstance().GetRenderWindow()->setView(mainCamera->GetView());

	for (int i = 0; i < (int)LayerType::UI; ++i)
	{
		for (auto& object : gameObjectVectors[i])
		{
			if (!object->IsActive())
				continue;

			object->Render(window);
		}
	}
	WindowManager::GetInstance().GetRenderWindow()->setView(uICamera->GetView());

	for (int i = (int)LayerType::UI; i < (int)LayerType::End; ++i)
	{
		for (auto& object : gameObjectVectors[i])
		{
			if (!object->IsActive())
				continue;

			object->Render(window);
		}
	}

	 WindowManager::GetInstance().GetRenderWindow()->setView(saveView);
}


GameObject* Scene::AddGameObject(GameObject* obj, LayerType rayer)
{
	if (std::find(gameObjectVectors[(int)rayer].begin(), gameObjectVectors[(int)rayer].end(), obj) == gameObjectVectors[(int)rayer].end())
	{
		gameObjectVectors[(int)rayer].push_back(obj);
	}
	return obj;
}

void Scene::RemoveGameObject(GameObject* obj)
{
	for (int i = 0; i < (int)LayerType::End; ++i)
	{
		auto iter = std::find(gameObjectVectors[i].begin(), gameObjectVectors[i].end(), obj);

		if (iter != gameObjectVectors[i].end())
		{
			gameObjectVectors[i].erase(iter);
			return;
		}
	}
}

void Scene::RemoveGameObject(GameObject* obj, LayerType layer)
{
	auto iter = std::find(gameObjectVectors[(int)layer].begin(), gameObjectVectors[(int)layer].end(), obj);

	if(iter != gameObjectVectors[(int)layer].end())
		gameObjectVectors[(int)layer].erase(iter);
}

void Scene::ApplyRemoveGameObject()
{
	for (auto object : removeObjectVector)
	{
		//gameObjects.remove(object);
	}
	removeObjectVector.clear();
}

GameObject* Scene::FindGameObject(const std::string& name)
{
	for (int i = 0; i < (int)LayerType::End; ++i)
	{
		for (auto object : gameObjectVectors[i])
		{
			if (object->GetName() == name)
			{
				return object;
			}
		}
	}
	return nullptr;
}

GameObject* Scene::FindGameObject(const std::string& name, LayerType layer)
{
	int index = (int)layer;

	for (auto object : gameObjectVectors[index])
	{
		if (object->GetName() == name)
		{
			return object;
		}
	}

	return nullptr;
}

int Scene::FindGameObjectAll(const std::string& name, std::vector<GameObject*>& vector)
{
	for (int i = 0; i < (int)LayerType::End; ++i)
	{
		for (auto object : gameObjectVectors[i])
		{
			if (object->GetName() == name)
			{
				vector.push_back(object);
			}
		}
	}

	return (int)vector.size();
}


sf::Vector2f Scene::ScreenToWorld(sf::Vector2i screenPos)
{
	return WindowManager::GetInstance().GetRenderWindow()->mapPixelToCoords(screenPos, mainCamera->GetView());
}

sf::Vector2i Scene::WorldToScreen(sf::Vector2f screenPos)
{
	return WindowManager::GetInstance().GetRenderWindow()->mapCoordsToPixel(screenPos, mainCamera->GetView());
}

sf::Vector2f Scene::ScreenToUI(sf::Vector2i screenPos)
{
	return WindowManager::GetInstance().GetRenderWindow()->mapPixelToCoords(screenPos, uICamera->GetView());
}

sf::Vector2i Scene::UIToScreen(sf::Vector2f screenPos)
{
	return  WindowManager::GetInstance().GetRenderWindow()->mapCoordsToPixel(screenPos, uICamera->GetView());
}

sf::Vector2f Scene::ScreenToWorld(const sf::View& view, sf::Vector2i screenPos)
{
	return  WindowManager::GetInstance().GetRenderWindow()->mapPixelToCoords(screenPos, view);
}

sf::Vector2i Scene::WorldToScreen(const sf::View& view, sf::Vector2f screenPos)
{
	return WindowManager::GetInstance().GetRenderWindow()->mapCoordsToPixel(screenPos, view);
}
