#pragma once

#include "Singleton.h"
#include "Core.h"

template<typename T>
class ResourcesManager : public Singleton<ResourcesManager<T>>
{
	friend Singleton<ResourcesManager<T>>;
protected:
	std::unordered_map<std::string, T*> resourcesMap;

	ResourcesManager() = default;
	~ResourcesManager()
	{
		UnloadAll();
	}
	ResourcesManager(const ResourcesManager&) = delete;
	ResourcesManager& operator=(const ResourcesManager&) = delete;
public:
	static T Empty;

	void UnloadAll()
	{
		for (const auto& iter : resourcesMap)
		{
			delete iter.second;
		}
		resourcesMap.clear();
	}

	bool Load(const std::string& id)
	{
		if (resourcesMap.find(id) != resourcesMap.end())
			return false;

		T* resource = new T();
		bool success = resource->LoadFromFile(id);
		if (success)
		{
			resourcesMap.insert({ id, resource });
		}
		else
		{
			delete resource;
		}

		return success;
	}

	bool unLoad(const std::string& id)
	{
		auto iter = resourcesMap.find(id);

		if (iter == resourcesMap.end())
			return false;

		delete iter->second;
		resourcesMap.erase(iter);
		return true;
	}

	T& Get(const std::string& id)
	{
		auto iter = resourcesMap.find(id);
		if (iter == resourcesMap.end())
		{
			return Empty;
		}
		return *(iter->second);
	}
};

template<typename T>
T ResourcesManager<T>::Empty = nullptr;