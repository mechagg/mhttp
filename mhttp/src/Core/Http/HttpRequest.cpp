#include "mpch.hpp"
#include "Core/Http/HttpRequest.hpp"

static std::string trim(const std::string& str)
{
	size_t first = str.find_first_not_of(' ');
	if (std::string::npos == first)
	{
		return str;
	}
	size_t last = str.find_last_not_of(' ');
	return str.substr(first, (last - first + 1));
}

namespace mhttp::Core::Http
{
	HttpRequest::HttpRequest(HttpRequestOptions options)
		: m_options(options)
	{
		this->m_responseCode = CURLE_OK;
	}

	HttpRequest::~HttpRequest()
	{}

	HttpResponse HttpRequest::Perform()
	{
		HttpResponse response;

		// Initialize curl using curl_easy_init.
		CURL* curl = curl_easy_init();

		// Configure the request method and url.
		curl_easy_setopt(curl, CURLOPT_URL, this->m_options.url.c_str());

		auto outgoingHeaders = this->MakeOutgoingHeaders();
		curl_easy_setopt(curl, CURLOPT_HEADER, outgoingHeaders);
		
		// Configure the data buffer and function.
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, this);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, static_cast<CURL_WRITEFUNCTION_PTR>([](char* data, size_t length, size_t members, void* userp) {
			size_t size = length * members;
			auto klass = static_cast<HttpRequest*>(userp);
			klass->BodyCallback(data, size);
			return size;
		}));

		// Configure the header parser.
		curl_easy_setopt(curl, CURLOPT_HEADERDATA, this);
		curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, static_cast<CURL_WRITEFUNCTION_PTR>([](char* data, size_t length, size_t members, void* userp) {
			size_t size = length * members;
			auto klass = static_cast<HttpRequest*>(userp);
			klass->HeaderCallback(data, size);
			return size;
		}));

		// Perform the request, and create the response.
		this->m_responseCode = curl_easy_perform(curl);
		
		// Return the response with error = error message if curl failed to make the request.
		if (this->m_responseCode != CURLE_OK)
		{
			const char* error = curl_easy_strerror(this->m_responseCode);

			response.error = error;
			return response;
		}

		// Get the response data from curl.
		// TODO: The responses from these calls shouldn't be ignored. They provide information regarding compatability.
		long responseCode;
		curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &responseCode);
		response.statusCode = responseCode;

		curl_off_t contentLength;
		curl_easy_getinfo(curl, CURLINFO_CONTENT_LENGTH_DOWNLOAD_T, &contentLength);
		response.contentLength = static_cast<int>(contentLength);

		char* contentType = nullptr;
		curl_easy_getinfo(curl, CURLINFO_CONTENT_TYPE, &contentType);
		
		if (contentType != nullptr)
			response.contentType = std::string(contentType);

		response.body = this->m_incomingBody;
		response.headers = this->m_incomingHeaders;

		curl_easy_cleanup(curl);
		curl_slist_free_all(outgoingHeaders);

		return response;
	}

	// Handles the curl write callback function.
	// Writes the incoming data to a string on the class.
	void HttpRequest::BodyCallback(char* data, size_t size)
	{
		this->m_incomingBody.append(data, size);
	}

	// Handles the curl header callback function.
	// Writes the incoming header into key=value map.
	void HttpRequest::HeaderCallback(char* data, size_t size)
	{
		std::string str(data);

		size_t index = str.find(":", 0);

		if (index == std::string::npos)
			return;

		auto key = trim(str.substr(0, index));
		auto value = trim(str.substr(index + 1));

		this->m_incomingHeaders[key] = value;
	}

	// Returns a curl_slist* from the headers passed in the options.
	// Make sure to free the curl_slist* after use.
	struct curl_slist* HttpRequest::MakeOutgoingHeaders()
	{
		struct curl_slist* headers = NULL; // Gets pushed onto the heap by curl_slist_append.

		for (auto const& entry : this->m_options.headers) 
		{
			// unscuff please
			std::string header;
			header.append(entry.first);
			header.append(": ");
			header.append(entry.second);

			curl_slist_append(headers, header.c_str());
		}

		return headers;
	}
}