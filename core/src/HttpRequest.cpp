#include "../include/HttpRequest.h"
#include "../include/Utils.h"


HttpRequest::HttpRequest(
	const HttpHeaderCollection& headers,
	const std::string& method,
	const std::string& uri,
	const std::string& protocolName,
	const std::string& protocolVersion,
	const std::string& body) :
	m_pHeaders(headers),
	m_sMethod(method),
	m_sUri(uri),
	m_sProtocolName(protocolName),
	m_sProtocolVersion(protocolVersion),
	m_sBody(body)
{
}

size_t HttpRequest::ParseItem(
	std::string& out, 
	const std::string& content, 
	const char* target, 
	size_t offset, 
	int verb)
{
	auto pos = content.find(target, offset);
	auto fragment = content.substr(offset, pos - offset);

	if (verb < 0)
		ToLower(fragment);
	else if (verb > 0)
		ToUpper(fragment);

	out = fragment;
	return pos + strlen(target);
}

bool HttpRequest::Parse(
	const std::string& content,
	size_t end,
	std::string& method,
	std::string& uri,
	std::string& protocolName,
	std::string& protocolVersion,
	HttpHeaderCollection& headers)
{
	size_t pos = 0;

	pos = ParseItem(method, content, " ", pos, 1);
	pos = ParseItem(uri, content, " ", pos, -1);
	pos = ParseItem(protocolName, content, "/", pos, +1);
	pos = ParseItem(protocolVersion, content, "\r\n", pos);

	// Headers
	std::string header, value;
	while (pos < end)
	{
		pos = ParseItem(header, content, ":", pos);
		ToLower(header);
		pos = ParseItem(value, content, "\r\n", pos);
		LeftTrim(value);
		auto hrd = new HttpHeader(header, value);
		headers.AddHeader(*hrd);
	}

	return true;
}

const char* HttpRequest::TranslateMethod(HttpMethods method)
{
	switch (method)
	{
	case HttpMethods::Get:		return "GET";
	case HttpMethods::Head:		return "HEAD";
	case HttpMethods::Post:		return "POST";
	case HttpMethods::Put:		return "PUT";
	case HttpMethods::Delete:	return "DELETE";
	case HttpMethods::Connect:	return "CONNECT";
	case HttpMethods::Options:	return "OPTIONS";
	case HttpMethods::Trace:	return "TRACE";
	case HttpMethods::Patch:	return "PATCH";
	default:					return nullptr;
	}
}
