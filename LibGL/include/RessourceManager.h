#pragma once

#include "ThreadPool.h"
#include <unordered_map>
#include <string>

class IResource
{
public:
	virtual ~IResource() = default;
};

class ResourceManager
{
public:
	std::unordered_map <std::string, std::unique_ptr<IResource>> manager;
	ThreadPool* pool;

	ResourceManager();

	~ResourceManager();

	template <typename T, typename ...Args>
	T* CreateRessource(const char* const& filename, Args&... pArgs)
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
		std::unique_ptr<IResource>& value = manager[filename];
		IResource* ptr = value.get();
		T* rsc = static_cast<T*>(ptr);
		return rsc;
	}

	template <typename T, typename ...args>
	T* Create(const char* const& filename, args... Args)
	{
		static_assert(std::is_base_of_v<IResource, T>, "T is not a child of IResources");

		manager[filename] = std::make_unique<T>(filename, Args...);
		std::unique_ptr<IResource>& value = manager[filename];
		IResource* ptr = value.get();
		T* rsc = static_cast<T*>(ptr);
		return rsc;
	};

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
