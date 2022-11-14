#pragma once
#include <mutex>
#include <condition_variable>
#include <queue>

template <typename T>
class SafeQueue
{
	mutable std::mutex _guardMutex, _uniqueMutex;
	mutable std::condition_variable _block;

	std::queue<T> _rawQueue;

public:
	SafeQueue() = default;
	SafeQueue(const SafeQueue<T>&) = delete;
	SafeQueue(SafeQueue<T>&&) = delete;
	SafeQueue& operator=(const SafeQueue&) = delete;
	SafeQueue& operator=(SafeQueue&&) = delete;

	~SafeQueue() = default;

	const T& front() const
	{
		std::lock_guard<std::mutex> lg(_guardMutex);
		return _rawQueue.front();
	}

	const T& back() const
	{
		std::lock_guard<std::mutex> lg(_guardMutex);
		return _rawQueue.back();
	}

	T pop()
	{
		std::lock_guard<std::mutex> lg(_guardMutex);
		T result = _rawQueue.front();
		_rawQueue.pop();
		return result;
	}

	void push(const T item)
	{
		std::lock_guard<std::mutex> lg(_guardMutex);
		_rawQueue.emplace(std::move(item));
		std::unique_lock<std::mutex> uniqueLock(_uniqueMutex);
		_block.notify_one();
	}

	bool empty() const
	{
		std::lock_guard<std::mutex> lg(_guardMutex);
		return _rawQueue.empty();
	}

	size_t size() const
	{
		std::lock_guard<std::mutex> lg(_guardMutex);
		return _rawQueue.size();
	}

	void wait(bool additionalFlag = false) const
	{
		std::unique_lock<std::mutex> uniqueLock(_uniqueMutex);
		
		_block.wait(uniqueLock, [this, additionalFlag]() {
			return !empty() || additionalFlag;
		});
	}
};
