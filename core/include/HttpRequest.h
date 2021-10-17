#ifndef _HTTP_REQUEST_H
#define _HTTP_REQUEST_H

#include "export.h"
#include <string>
#include <map>

typedef std::map<std::string, std::string> HttpHeaderCollection;

class DLLEXPORTED HttpRequest
{
private:
	std::string m_body;

public:
	std::string m_method;
	std::string m_uri;
	std::string m_protocolName;
	std::string m_protocolVersion;
	HttpHeaderCollection m_headers;

public:
	HttpRequest(
		const std::string &method, 
		const std::string &uri,
		const std::string &protocolName,
		const std::string &protocolVersion,
		const HttpHeaderCollection &headers,
		const std::string &content,
		size_t body_begin,
		size_t contentLen);
};

#endif // !_HTTP_REQUEST_H
