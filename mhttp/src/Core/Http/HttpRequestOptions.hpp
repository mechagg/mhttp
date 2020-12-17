#pragma once

#include <string>
#include <vector>
#include <map>

namespace mhttp
{
	struct HttpRequestOptions
	{
		std::string url;
		std::string method;
		std::map<std::string, std::string> headers;
	};
}