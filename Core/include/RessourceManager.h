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
    std::unordered_map<std::string, IResource*> manager;
    ThreadPool pool;

    ~ResourceManager();

    template <typename T, typename ...Args> T** CreateRessource(const std::string& pStr, Args&... pArgs)
    {
        std::unordered_map<std::string, IResource*>::iterator it = manager.find(pStr);
        if (it != manager.end())
            return (T**)&it->second;

        manager[pStr] = nullptr;
        pool.AddToQueue([this, pStr, &pArgs...]
            {
                manager[pStr] = new T(pArgs...);
            });

        return (T**)&manager[pStr];
    }

    template <typename T> T* Get(const std::string& pStr)
    {
        std::unordered_map<std::string, IResource*>::iterator it = manager.find(pStr);
        if (it == manager.end())
            return nullptr;

        return (T*)it->second;
    }

    void DeleteRessource(const std::string& str);
    void Clear();
};
