#pragma once

class GameObject;

class Scene
{
protected:
	const SceneIds id;
	std::list<GameObject*> gameObjectList;
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

	virtual GameObject* AddGameObject(GameObject* obj);
	virtual void RemoveGameObject(GameObject* obj);
	virtual GameObject* FindGameObject(const std::string& name);
	virtual int FindGameObjectAll(const std::string& name, std::list<GameObject*>& list);

	template<typename T>
	T* AddGameObject(T* obj);

};

template<typename T>
inline T* Scene::AddGameObject(T* obj)
{
	if (std::find(gameObjectList.begin(), gameObjectList.end(), obj) == gameObjectList.end())
	{
		gameObjectList.push_back(obj);
	}
	return obj;
}
