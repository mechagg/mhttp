#include <mhttp.hpp>

#include <vector>
#include <string>
#include <iostream>

void handleResults(mhttp::ThreadSafeQueue<mhttp::HttpRequest>* queue)
{
	while (true)
	{
		auto request = queue->Pop();
		if (!request) continue;
		auto rq = *request;
		auto res = rq.Perform();

		std::cout << res.body << std::endl;
	}
}

int main()
{
	mhttp::HttpRequest request(mhttp::HttpRequestOptions{
		"https://jsonplaceholder.typicode.com/todos/1",
		"GET",
		std::map<std::string, std::string>(),
	});

	mhttp::HttpRequest request2(mhttp::HttpRequestOptions{
		"https://jsonplaceholder.typicode.com/todos/2",
		"GET",
		std::map<std::string, std::string>(),
	});

	mhttp::ThreadSafeQueue<mhttp::HttpRequest> queue;

	std::thread thread(handleResults, &queue);

	queue.Push(request);
	queue.Push(request2);

	thread.join();

	return 0;
}