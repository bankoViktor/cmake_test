#include "../include/HttpRequest.h"
#include "../include/Utils.h"


HttpRequest::HttpRequest(
	const std::string& method,
	const std::string& uri,
	const std::string& protocolName,
	const std::string& protocolVersion,
	const HttpHeaderCollection& headers,
	const std::string& content,
	size_t body_begin,
	size_t contentLen)
{
	size_t len;

	len = method.size() + 1;
	m_pszMethod = new char[len];
	strcpy_s((char*)m_pszMethod, len, method.data());

	len = uri.size() + 1;
	m_pszUri = new char[len];
	strcpy_s((char*)m_pszUri, len, uri.data());

	len = protocolName.size() + 1;
	m_pszProtocolName = new char[len];
	strcpy_s((char*)m_pszProtocolName, len, protocolName.data());

	len = protocolName.size() + 1;
	m_pszProtocolVersion = new char[len];
	strcpy_s((char*)m_pszProtocolVersion, len, protocolVersion.data());

	m_pHeaders = new HttpHeaderCollection(headers);

	m_pszBody = nullptr;
	if (contentLen > 0)
	{
		len = contentLen + 1;
		m_pszBody = new char[len];
		strcpy_s((char*)m_pszBody, len,  protocolVersion.data() + body_begin);
	}
}

HttpRequest::~HttpRequest()
{
	SafeReleasePonter(m_pszBody);
	SafeReleasePonter(m_pszMethod);
	SafeReleasePonter(m_pszUri);
	SafeReleasePonter(m_pszProtocolName);
	SafeReleasePonter(m_pszProtocolVersion);
	SafeReleasePonter(m_pHeaders);
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
