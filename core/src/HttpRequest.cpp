#include "../include/HttpRequest.h"

HttpRequest::HttpRequest(
	const std::string& method,
	const std::string& uri,
	const std::string& protocolName,
	const std::string& protocolVersion,
	const HttpHeaderCollection& headers,
	const std::string& content,
	size_t body_begin,
	size_t contentLen) :
	m_method(method),
	m_uri(uri),
	m_protocolName(protocolName),
	m_protocolVersion(protocolVersion),
	m_headers(headers)
{
	m_body = content.substr(body_begin, body_begin + contentLen);
}