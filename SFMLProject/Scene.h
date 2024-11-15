#pragma once

class GameObject;
class Camera;

class Scene
{
protected:
	const SceneIds							id;
	std::vector<GameObject*>				removeObjectVector;
	std::vector<std::vector<GameObject*>>	gameObjectVectors;

	Camera*									mainCamera;
	Camera*									uICamera;
	Camera*									freeCamera;

	sf::Vector2f							cameraPosition;
	float									cameraSpeed;
	bool									isFreeView;

public:
	sf::Vector2f ScreenToWorld(sf::Vector2i screenPos);
	sf::Vector2i WorldToScreen(sf::Vector2f screenPos);

	sf::Vector2f ScreenToUI(sf::Vector2i screenPos);
	sf::Vector2i UIToScreen(sf::Vector2f screenPos);
	sf::Vector2f ScreenToWorld(const sf::View& view, sf::Vector2i screenPos);
	sf::Vector2i WorldToScreen(const sf::View& view, sf::Vector2f screenPos);

public:
	virtual GameObject* AddGameObject(GameObject* obj, LayerType layer);
	virtual void RemoveGameObject(GameObject* obj);
	virtual void RemoveGameObject(GameObject* obj, LayerType layer);

	virtual void ApplyRemoveGameObject();

	virtual GameObject* FindGameObject(const std::string& name, LayerType layer);
	virtual GameObject* FindGameObject(const std::string& name);
	virtual int FindGameObjectAll(const std::string& name, std::vector<GameObject*>& vector);
	

	const std::vector<std::vector<GameObject*>>& GetObjectVectors() { return gameObjectVectors; }
	const std::vector<GameObject*>& GetObjectVector(LayerType layer) { return gameObjectVectors[(int)layer]; }

	template<typename T>
	T* AddGameObject(T* obj, LayerType layer);

public:
	virtual void Init() = 0;
	virtual void Release() = 0;

	virtual void Enter();
	virtual void Exit();

	virtual void Update(float dt);
	virtual void FixedUpdate(float fixedDeltaTime);
	virtual void Render(sf::RenderWindow& window);

public:
	Scene(const SceneIds id);
	virtual ~Scene();

};

template<typename T>
inline T* Scene::AddGameObject(T* obj, LayerType layer)
{
	if (std::find(gameObjectVectors[(int)layer].begin(), gameObjectVectors[(int)layer].end(), obj) == gameObjectVectors[(int)layer].end())
	{
		gameObjectVectors[(int)layer].push_back(obj);
	}
	return obj;
}
