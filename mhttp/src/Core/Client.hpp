#pragma once

#include <thread>
#include <string>

namespace mhttp
{
	class Client
	{
	public:
		Client();
		~Client();

		void Get(std::string url);
	private:
		std::thread m_requestThread;
	};
}