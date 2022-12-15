#include "../Core/include/RessourceManager.h"

ResourceManager::ResourceManager()
{
	pool = new ThreadPool();
}

ResourceManager::~ResourceManager()
{
	Clear();
	delete pool;
}

void ResourceManager::DeleteRessource(const std::string& pStr)
{
	auto it = manager.find(pStr);
	if (it != manager.end())
	{
		manager.erase(it);
	}
}

void ResourceManager::Clear()
{
	manager.clear();
}