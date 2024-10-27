#pragma once

class GameObject;

class Scene
{
protected:
	const SceneIds id;
	std::vector<GameObject*> removeObjectVector;
	std::vector<std::vector<GameObject*>> gameObjectVector;

public:
	Scene(const SceneIds id);
	virtual ~Scene() = default;

	virtual void Init() = 0;
	virtual void Release() = 0;

	virtual void Enter();
	virtual void Exit();

	virtual void Update(float dt);
	virtual void Render(sf::RenderWindow& window);

public:

	virtual GameObject* AddGameObject(GameObject* obj, RenderLayer rayer);
	virtual void RemoveGameObject(GameObject* obj);
	virtual GameObject* FindGameObject(const std::string& name);
	virtual int FindGameObjectAll(const std::string& name, std::list<GameObject*>& list);

	template<typename T>
	T* AddGameObject(T* obj, RenderLayer rayer);

};

template<typename T>
inline T* Scene::AddGameObject(T* obj, RenderLayer rayer)
{
	if (std::find(gameObjectVector[(int)rayer].begin(), gameObjectVector[(int)rayer].end(), obj) == gameObjectVector[(int)rayer].end())
	{
		gameObjectVector[(int)rayer].push_back(obj);
	}
	return obj;
}
