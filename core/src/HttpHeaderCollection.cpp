#include "../include/HttpHeaderCollection.h"
#include "../include/Utils.h"


HttpHeaderCollection::HttpHeaderCollection()
{
	m_pHeaders = new std::vector<HttpHeader*>();
}

HttpHeaderCollection::HttpHeaderCollection(const HttpHeaderCollection& copy) :
	HttpHeaderCollection()
{
	for (auto hdr : *copy.m_pHeaders)
	{
		m_pHeaders->push_back(new HttpHeader(*hdr));
	}
}

HttpHeaderCollection::~HttpHeaderCollection()
{
	while (!m_pHeaders->empty())
	{
		delete m_pHeaders->back();
		m_pHeaders->pop_back();
	}

	SafeReleasePonter(m_pHeaders);
}

void HttpHeaderCollection::AddHeader(const HttpHeader& header)
{
	m_pHeaders->push_back(new HttpHeader(header));
}

void HttpHeaderCollection::AddHeader(const char* name, const char* value)
{
	m_pHeaders->push_back(new HttpHeader(name, value));
}

const HttpHeader* HttpHeaderCollection::operator[](const char* name)
{
	auto it = m_pHeaders->cbegin();
	while (it != m_pHeaders->cend())
	{
		if (StringCompare((*it)->m_pszName, name, true))
			return *it;

		++it;
	}

	return nullptr;
}
