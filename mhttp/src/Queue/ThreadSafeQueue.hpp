#pragma once

#include <mutex>
#include <queue>
#include <optional>
#include <condition_variable>

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

		void Push(const T& item)
		{
			std::unique_lock<std::mutex> guard(this->m_mutex);
			this->m_queue.push(item);
		};
	
		std::optional<T> Pop()
		{
			std::unique_lock<std::mutex> guard(this->m_mutex);

			if (this->m_queue.empty())
				return {};

			auto tmp = this->m_queue.front();
			this->m_queue.pop();

			return tmp;
		};

		std::queue<T>* InternalQueue()
		{
			return &m_queue;
		};
	private:
		std::queue<T> m_queue;
		mutable std::mutex m_mutex;
	};
}
