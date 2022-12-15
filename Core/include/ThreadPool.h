#pragma once
#include <condition_variable>
#include <functional>
#include <queue>
#include <thread>

class ThreadPool
{
public:

	ThreadPool();
	~ThreadPool();
	void AddToQueue(const std::function<void()>& task);

private:

	void ThreadLoop();
	bool shouldStop = false;
	std::mutex queueMutex;
	std::condition_variable mutexCondition;
	std::vector<std::thread> threads;
	std::queue<std::function<void()>> tasksQueue;
};