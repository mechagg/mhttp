#include "mpch.hpp"
#include "Client.hpp"

namespace mhttp::Core
{
	Client::Client()
	{
		// Initialize the request thread.
		this->m_requestThread = std::thread([](Util::ThreadSafeQueue<Http::HttpRequest*>& queue) {
			while (true)
			{
				auto opt = queue.Pop();
				if (!opt) continue;

				auto request = *opt;
				if (request == nullptr) break;

				auto response = request->Perform();

				std::cout << response.body << std::endl;

				delete request;
			}
		}, std::ref(this->m_queue));
	}

	Client::~Client()
	{}
	
	// Get pushes a new GET request onto the request queue.
	void Client::Get(std::string url)
	{
		auto request = new Http::HttpRequest(mhttp::HttpRequestOptions{
			url,
			"GET",
			std::map<std::string, std::string>(),
		});

		this->m_queue.Push(request);
	}

	void Client::Shutdown()
	{
		this->m_queue.Push(nullptr);
	}

	void Client::Wait() const
	{
		this->m_requestThread.join();
	}
}