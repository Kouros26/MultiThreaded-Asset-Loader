#include "RessourceManager.h"

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

void ResourceManager::InitAll() const
{
    for (const auto& obj : manager)
    {
        obj.second->Init();
    }
}

bool ResourceManager::AreAllRessourcesLoaded() const
{
    for (const auto& obj : manager)
    {
        if (!obj.second)
        {
            return false;
        }
    }
    return true;
}
