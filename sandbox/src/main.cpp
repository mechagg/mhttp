#include <mhttp.hpp>

#include <vector>
#include <string>
#include <iostream>

int main()
{
	auto request = new mhttp::HttpRequest(mhttp::HttpRequestOptions{
		"https://jsonplaceholder.typicode.com/todos/1",
		"GET",
		std::map<std::string, std::string>(),
	});

	auto response = request->Perform();

	if (response.error != "")
		std::cout << "Error: " << response.error << std::endl;

	std::cout << response.body << std::endl;

	delete request;

	return 0;
}