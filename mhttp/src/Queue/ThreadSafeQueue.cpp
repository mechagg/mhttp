#include "mpch.hpp"
#include "ThreadSafeQueue.hpp"

namespace mhttp
{
	template<class T>
	void ThreadSafeQueue<T>::Push(const T &item)
	{
		std::lock_guard<std::mutex> guard(this->m_mutex);
		this->m_queue.push(item);
	}

	template<class T>
	std::optional<T> ThreadSafeQueue<T>::Pop()
	{
		std::lock_guard<std::mutex> guard(this->m_mutex);
		
		auto tmp = this->m_queue.front();
		this->m_queue->pop();

		return tmp;
	}
}