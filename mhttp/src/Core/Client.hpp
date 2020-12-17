#pragma once

#include <thread>
#include <string>

#include "Core/Http/HttpRequest.hpp"
#include "Util/ThreadSafeQueue.hpp"

namespace mhttp::Core
{
	class Client
	{
	public:
		Client();
		~Client();

		void Get(std::string url);
		void Shutdown();
		void Wait() const;
	private:
		Util::ThreadSafeQueue<Http::HttpRequest*> m_queue;
		mutable std::thread m_requestThread;
	};
}