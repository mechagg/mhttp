#pragma once

#include <mutex>
#include <queue>
#include <optional>

namespace mhttp 
{
	template <class T>
	class ThreadSafeQueue
	{
	public:
		ThreadSafeQueue() = default;
		ThreadSafeQueue(const ThreadSafeQueue<T>&) = delete;
		ThreadSafeQueue& operator=(const ThreadSafeQueue<T>&) = delete;

		virtual ~ThreadSafeQueue() {};

		void Push(const T& item);
		std::optional<T> Pop();
	private:
		std::queue<T> m_queue;
		mutable std::mutex m_mutex;
	};
}
