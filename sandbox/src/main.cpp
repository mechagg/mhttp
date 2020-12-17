#include <mhttp.hpp>

#include <vector>
#include <string>
#include <iostream>

void handleResults(mhttp::ThreadSafeQueue<mhttp::HttpRequest*>* queue)
{
	while (true)
	{
		auto request = queue->Pop();
		if (!request) continue;
		auto rq = *request;
		auto res = rq->Perform();

		std::cout << res.body << std::endl;

		delete rq;
	}
}

int main()
{
	auto request = new mhttp::HttpRequest(mhttp::HttpRequestOptions{
		"https://jsonplaceholder.typicode.com/todos/1",
		"GET",
		std::map<std::string, std::string>(),
	});

	auto request2 = new mhttp::HttpRequest(mhttp::HttpRequestOptions{
		"https://jsonplaceholder.typicode.com/todos/2",
		"GET",
		std::map<std::string, std::string>(),
	});

	mhttp::ThreadSafeQueue<mhttp::HttpRequest*> queue;

	std::thread thread(handleResults, &queue);

	queue.Push(request);
	queue.Push(request2);

	thread.join();

	return 0;
}