#ifndef _HTTP_REQUEST_H
#define _HTTP_REQUEST_H

#include "export.h"
#include <string>
#include <map>
#include "HttpHeaderCollection.h"
#include "Utils.h"


class DLLEXPORTED HttpRequest
{
private:
	char * m_pszBody;

public:
	char * m_pszMethod;
	char * m_pszUri;
	char * m_pszProtocolName;
	char * m_pszProtocolVersion;
	HttpHeaderCollection* m_pHeaders;

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
	~HttpRequest();

	static bool Parse(
		const std::string& content,
		size_t end,
		std::string& method,
		std::string& uri,
		std::string& protocolName,
		std::string& protocolVersion,
		HttpHeaderCollection& headers);

private:
	static size_t ParseItem(
		std::string& out,
		const std::string& content,
		const char* target,
		size_t offset,
		int verb = 0);
};


#endif // !_HTTP_REQUEST_H
