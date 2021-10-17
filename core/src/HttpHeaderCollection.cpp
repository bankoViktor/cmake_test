#include "../include/HttpHeaderCollection.h"
#include "../include/Utils.h"

HttpHeader::HttpHeader(const std::string& name, const std::string& value)
{
	this->name = new std::string(name);
	this->value = new std::string(value);
}

HttpHeader::~HttpHeader()
{
	SafeReleasePonter(this->name);
	SafeReleasePonter(this->value);
}

long long HttpHeader::asLongLong() const
{
	return std::stoll(value->c_str());
}

HttpHeaderCollection::HttpHeaderCollection()
{
	m_pCollection = new std::vector<const HttpHeader*>();
}

HttpHeaderCollection::HttpHeaderCollection(const HttpHeaderCollection & copy)
{
	m_pCollection = new std::vector<const HttpHeader*>();

	auto it = copy.m_pCollection->cbegin();
	while (it != copy.m_pCollection->cend())
	{
		auto copyHdr = new HttpHeader(*(*it)->name, *(*it)->value);
		m_pCollection->push_back(copyHdr);
	}
}

HttpHeaderCollection::~HttpHeaderCollection()
{
	while (!m_pCollection->empty())
	{
		delete m_pCollection->back();
		m_pCollection->pop_back();
	}

	SafeReleasePonter(m_pCollection);
}

void HttpHeaderCollection::Add(const std::string& name, const std::string& value)
{
	m_pCollection->push_back(new HttpHeader(name, value));
}

const HttpHeader* HttpHeaderCollection::operator[](const char* name)
{
	auto it = m_pCollection->cbegin();
	while (it != m_pCollection->cend())
	{
		if (StringCompare((*it)->name->c_str(), name, true))
			return *it;

		++it;
	}

	return nullptr;
}
