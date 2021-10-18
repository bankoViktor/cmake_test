#include "../include/HttpHeader.h"
#include "../include/Utils.h"


HttpHeader::HttpHeader(const char* name, const char* value)
{
	size_t len;

	len = strlen(name) + 1;
	m_pszName = new char[len];
	strcpy_s((char*)m_pszName, len, name);

	len = strlen(value) + 1;
	m_pszValue = new char[len];
	strcpy_s((char*)m_pszValue, len, value);
}

HttpHeader::HttpHeader(const std::string& name, const std::string& value) :
	HttpHeader(name.data(), value.data())
{
}

HttpHeader::HttpHeader(const HttpHeader& copy) :
	HttpHeader(copy.m_pszName, copy.m_pszValue)
{
}

HttpHeader::~HttpHeader()
{
	SafeReleasePonter(m_pszName);
	SafeReleasePonter(m_pszValue);
}

long long HttpHeader::asLongLong() const
{
	return std::stoll(m_pszValue);
}
