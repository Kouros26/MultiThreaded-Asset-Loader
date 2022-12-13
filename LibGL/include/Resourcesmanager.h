#pragma once
#include <memory>
#include <unordered_map>

namespace Resources
{
	class IResource
	{
	public:
		virtual ~IResource() = default;
	};
	class ResourcesManager
	{
	public:
		~ResourcesManager() = default;
		template<typename T, typename ...args>
		T* Create(const char* const& filename, args... Args)
		{
			static_assert(std::is_base_of_v<IResource, T>, "T is not a child of IResources");

			manager[filename] = std::make_unique<T>(filename, Args...);
			std::unique_ptr<IResource>& value = manager[filename];
			IResource* ptr = value.get();
			T* rsc = static_cast<T*>(ptr);
			return rsc;
		};
		template<typename T>
		T* Get(std::string const& filename)
		{
			auto it = manager.find(filename);
			if (it == manager.end())
			{
				return nullptr;
			}

			return static_cast <T*>(it->second.get());
		};

		void Delete(std::string const& filename);
	private:
		std::unordered_map <std::string, std::unique_ptr<IResource>> manager;
	};
}