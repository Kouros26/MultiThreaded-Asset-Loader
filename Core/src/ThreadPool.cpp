#include "ThreadPool.h"
#include <iostream>

ThreadPool::ThreadPool()
{
	const unsigned int num_threads = std::thread::hardware_concurrency() * 8 / 10; //take 80 percent of max thread computer can handle

	for (unsigned int i = 0; i < num_threads; i++)
	{
		threads.emplace_back(std::thread(&ThreadPool::ThreadLoop, this));
	}
}

ThreadPool::~ThreadPool()
{
	std::unique_lock<std::mutex> lock(queueMutex);
	shouldStop = true;

	mutexCondition.notify_all();
	for (std::thread& active_thread : threads) {
		active_thread.join();
	}
	threads.clear();
}

void ThreadPool::AddToQueue(const std::function<void()>& task)
{
	std::unique_lock<std::mutex> lock(queueMutex);
	tasksQueue.push(task);

	mutexCondition.notify_one();
}

void ThreadPool::ThreadLoop()
{
	while (true)
	{
		std::function<void()> task;
		{
			std::unique_lock<std::mutex> lock(queueMutex);

			mutexCondition.wait(lock, [this]
				{
					return !tasksQueue.empty() || shouldStop;
				});

			if (shouldStop)
			{
				return;
			}
			task = tasksQueue.front();
			tasksQueue.pop();
		}
		task();
	}
}