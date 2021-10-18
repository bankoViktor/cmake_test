#include "../include/HttpInterfaceConfigurator.h"

HttpInterfaceConfigurator::HttpInterfaceConfigurator()
{
	m_pRequestHandlers = new HttpHandlerCollection();
}

HttpInterfaceConfigurator::~HttpInterfaceConfigurator()
{
	SafeReleasePonter(m_pRequestHandlers);
}

HttpInterfaceConfigurator& HttpInterfaceConfigurator::on(const char* pszMethod, const char* pszResource, REQUEST_HANDLER handler)
{
	REQUEST_HANDLER_INFO reqHandlerInfo = { 0 };
	reqHandlerInfo.pszMethod = pszMethod;
	reqHandlerInfo.pszResource = pszResource;
	reqHandlerInfo.handler = handler;
	m_pRequestHandlers->push_back(reqHandlerInfo);
	return *this;
}

HttpInterfaceConfigurator& HttpInterfaceConfigurator::on(HttpMethods method, const char* pszResource, REQUEST_HANDLER handler)
{
	auto szMmethod = HttpHelper::Translate(method);
	return on(szMmethod, pszResource, handler);
}

HttpInterfaceConfigurator& HttpInterfaceConfigurator::get(const char* pszResource, REQUEST_HANDLER handler)
{
	return on(HttpMethods::Get, pszResource, handler);
}

HttpInterfaceConfigurator& HttpInterfaceConfigurator::post(const char* pszResource, REQUEST_HANDLER handler)
{
	return on(HttpMethods::Post, pszResource, handler);
}
