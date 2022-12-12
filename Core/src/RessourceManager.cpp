#include "RessourceManager.h"

ResourceManager::~ResourceManager()
{
	for (std::unordered_map<std::string, IResource*>::iterator it = manager.begin(); it != manager.end(); it++)
		delete it->second;
	manager.clear();

	pool.~ThreadPool();
}

void ResourceManager::DeleteRessource(const std::string& pStr)
{
	std::unordered_map<std::string, IResource*>::iterator it = manager.find(pStr);
	if (it != manager.end())
	{
		delete it->second;
		manager.erase(it);
	}
}

void ResourceManager::Clear()
{
	for (std::unordered_map<std::string, IResource*>::iterator it = manager.begin(); it != manager.end(); it++)
		delete it->second;
	manager.clear();
}