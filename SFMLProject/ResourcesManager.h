#pragma once
#include "Resources.h"
#include "Core.h"

template<typename T>
class ResourcesManager : public Singleton<ResourcesManager<T>>
{
	friend Singleton<ResourcesManager<T>>;
protected:
	std::unordered_map<std::string, Resources<T>*> resourcesMap;

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

	bool Load(const std::string& id, const std::string& filepath)
	{
		if (resourcesMap.find(id) != resourcesMap.end())
			return false;

		Resources<T>* resource = new Resources<T>;

		bool success = resource->resource.loadFromFile(filepath);
		assert(success);

		if (success)
		{
			resourcesMap.insert({ id, resource });
			resource->SetKey(id);
			resource->SetFilePath(filepath);
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

	Resources<T>& GetResource(const std::string& id)
	{
		auto iter = resourcesMap.find(id);
		if (iter == resourcesMap.end())
		{
			return Empty;
		}
		return *(iter->second);
	}

	T& Get(const std::string& id)
	{
		auto iter = resourcesMap.find(id);
		if (iter == resourcesMap.end())
		{
			return Empty;
		}
		return (iter->second->resource);
	}
};

template<typename T>
T ResourcesManager<T>::Empty;

#define TEXTURE_MANAGER (ResourcesManager<sf::Texture>::GetInstance())