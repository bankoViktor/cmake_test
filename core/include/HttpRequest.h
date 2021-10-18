#ifndef _HTTP_REQUEST_H
#define _HTTP_REQUEST_H

#include "export.h"
#include <string>
#include "Utils.h"
#include "HttpHeaderCollection.h"


class DLLEXPORTED HttpRequest
{
public:
	const char * m_pszMethod;
	const char * m_pszUri;
	const char * m_pszProtocolName;
	const char * m_pszProtocolVersion;
	HttpHeaderCollection* m_pHeaders;
	const char* m_pszBody;

public:
	HttpRequest(
		const std::string& method,
		const std::string& uri,
		const std::string& protocolName,
		const std::string& protocolVersion,
		const HttpHeaderCollection& headers,
		const std::string& content,
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
