#include <mhttp.hpp>

#include <vector>
#include <string>
#include <iostream>
#include <chrono>

int main()
{
	auto client = new mhttp::Core::Client();

	client->Get("https://jsonplaceholder.typicode.com/todos/1");
	client->Get("https://jsonplaceholder.typicode.com/todos/2");
	client->Get("https://jsonplaceholder.typicode.com/todos/3");
	client->Get("https://jsonplaceholder.typicode.com/todos/4");

	client->Shutdown();
	client->Wait();

	delete client;

	return 0;
}