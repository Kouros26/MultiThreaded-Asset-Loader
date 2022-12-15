#include "../Core/include/ThreadPool.h"
#include <iostream>

int main()
{
	ThreadPool* pool = new ThreadPool();

	for (int i = 0; i < 10; i++)
	{
		pool->AddToQueue([i] { std::cout << i; });
	}
	while (true)
	{
	}

	return 0;
}