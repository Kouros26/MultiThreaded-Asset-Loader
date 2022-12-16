#pragma once

#include "ThreadPool.h"
#include <unordered_map>
#include <string>

class IResource
{
public:
	virtual ~IResource() = default;
	virtual void Init() {}
};

class ResourceManager
{
public:
	std::unordered_map <std::string, std::unique_ptr<IResource>> manager;
	ThreadPool* pool;

	ResourceManager();

	~ResourceManager();

	template <typename T, typename ...Args>
	T* Create(const char* const& filename, Args&... pArgs);

	template <typename T>
	T* Get(std::string const& filename)
	{
		auto it = manager.find(filename);
		if (it == manager.end())
		{
			return nullptr;
		}

		return static_cast <T*>(it->second.get());
	};

	void DeleteRessource(const std::string& str);
	void Clear();
};

template <typename T, typename ... Args>
T* ResourceManager::Create(const char* const& filename, Args&... pArgs)
{
	static_assert(std::is_base_of_v<IResource, T>, "T is not a child of IResources");
	auto it = manager.find(filename);
	if (it != manager.end())
	{
		return static_cast <T*>(it->second.get());
	}

	manager[filename] = nullptr;
	if (pool)
	{
		pool->AddToQueue([this, filename, &pArgs...]
			{
				manager[filename] = std::make_unique<T>(filename, pArgs...);
			});
	}
	else
	{
		manager[filename] = std::make_unique<T>(filename, pArgs...);
	}

	//here I want to wait for the task to be over before init and return !!!!
	while (!manager[filename])
	{
		//this is not good
		//maybe conditional mutex
		//or future and promise
	}

	std::unique_ptr<IResource>& value = manager[filename];
	IResource* ptr = value.get();
	ptr->Init();
	T* rsc = static_cast<T*>(ptr);
	return rsc;
}
