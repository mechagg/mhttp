#pragma once

#include <string>
#include <vector>
#include <map>

namespace mhttp
{
	struct HttpResponse
	{
		std::string contentType;
		int contentLength = 0;

		std::string body;

		unsigned int statusCode = 0;
		std::map<std::string, std::string> headers;

		std::string error;
	};
}