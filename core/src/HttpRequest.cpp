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
	auto methodLen = method.size() + 1;
	m_pszMethod = new char[methodLen];
	strcpy_s(m_pszMethod, methodLen, method.data());

	auto uriLen = uri.size() + 1;
	m_pszUri = new char[uriLen];
	strcpy_s(m_pszUri, uriLen, uri.data());

	auto protocolNameLen = protocolName.size() + 1;
	m_pszProtocolName = new char[protocolNameLen];
	strcpy_s(m_pszProtocolName, protocolNameLen, protocolName.data());

	auto protocolVersionLen = protocolName.size() + 1;
	m_pszProtocolVersion = new char[protocolVersionLen];
	strcpy_s(m_pszProtocolVersion, protocolVersionLen, protocolVersion.data());

	m_pHeaders = new HttpHeaderCollection();

	m_pszBody = nullptr;
	if (contentLen > 0)
	{
		m_pszBody = new char[contentLen]; 
		strcpy_s(m_pszBody, contentLen,  protocolVersion.data() + body_begin);
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
		headers.Add(header, value);
	}

	return true;
}
