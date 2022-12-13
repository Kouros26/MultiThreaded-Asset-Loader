#pragma once
#include <cstdarg>
#include <filesystem>

#ifdef _DEBUG
#define DEBUG_LOG(...) {\
    char str[4096];\
    sprintf_s(str, __VA_ARGS__);\
    std::cout << "[" << __FILE__ << "][" << __FUNCTION__ << "][Line " << __LINE__ << "] " << str << std::endl;\
    }
#else
#define DEBUG_LOG(...)
#endif
namespace Core
{
	namespace Debug
	{
		class Log
		{
		public:
			bool Openfile(std::filesystem::path const& filename);

			~Log();

			void Print(const char* format, ...);
		private:
			FILE* logFile = nullptr;
		};
	}
}
