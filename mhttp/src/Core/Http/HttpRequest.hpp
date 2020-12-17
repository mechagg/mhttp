#pragma once

#include <curl/curl.h>

#include "Core/Http/HttpRequestOptions.hpp"
#include "Core/Http/HttpResponse.hpp"

typedef size_t(*CURL_WRITEFUNCTION_PTR)(char*, size_t, size_t, void*);

namespace mhttp::Core::Http
{
	class HttpRequest
	{
	public:
		HttpRequest(HttpRequestOptions options);
		~HttpRequest();

		// Runs the request, returns a struct containing response data.
		HttpResponse Perform();

		void BodyCallback(char* data, size_t size);
		void HeaderCallback(char* data, size_t size);
	private:
		struct curl_slist* MakeOutgoingHeaders();

		CURLcode m_responseCode;
		HttpRequestOptions m_options;

		std::map<std::string, std::string> m_incomingHeaders;
		std::string m_incomingBody;
	};
}