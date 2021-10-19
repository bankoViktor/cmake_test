#ifndef _HTTP_REQUEST_H
#define _HTTP_REQUEST_H

#include "export.h"
#include <string>
#include "Utils.h"
#include "HttpHeaderCollection.h"


class DLLEXPORTED HttpRequest
{
public:
	const HttpHeaderCollection& m_pHeaders;
	const std::string& m_sMethod;
	const std::string& m_sUri;
	const std::string& m_sProtocolName;
	const std::string& m_sProtocolVersion;
	const std::string& m_sBody;

public:
	HttpRequest(
		const HttpHeaderCollection& headers,
		const std::string& method,
		const std::string& uri,
		const std::string& protocolName,
		const std::string& protocolVersion,
		const std::string& body);
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
