#include "../include/HttpInterface.h"
#include "../include/WinSock.h"
#include <iostream>
#include <thread>
#include <sstream>
#include <iomanip>
#include <string>
#include <algorithm>

HttpInterface::HttpInterface() :
	m_dwPort(DEFAULT_PORT),
	m_socket(INVALID_SOCKET)
{
	m_pRequestHandlers = new std::vector<REQUEST_HANDLER_INFO>();
}

HttpInterface::~HttpInterface()
{
	if (m_socket)
	{
		WinSock::CloseSocket(m_socket);
		m_socket = INVALID_SOCKET;
	}

	SafeReleasePonter(m_pRequestHandlers);
}

void HttpInterface::Start(unsigned short dwPort)
{
	SOCKET socket = INVALID_SOCKET;
	if (!WinSock::CreateSocket(&socket, dwPort))
	{
		std::cout << "WinSock::CreateSocket failed " << WSAGetLastError() << std::endl;
		return;
	}

	m_dwPort = dwPort;
	m_socket = socket;

	std::thread acceptionThread{ &HttpInterface::AcceptingHandler, this };
	SetThreadDescription(acceptionThread.native_handle(), L"AcceptinThread");

	acceptionThread.detach();
}

void HttpInterface::AcceptingHandler()
{
	SOCKET clientSocket = INVALID_SOCKET;

	while (true)
	{
		if (!WinSock::Accept(m_socket, &clientSocket))
		{
			std::cout << "WinSock::Accept failed " << WSAGetLastError() << std::endl;
			return;
		}

		std::thread requestThread{ &HttpInterface::RequestHandler, this, clientSocket };

		std::wstringstream ss;
		ss	<< L"Requert " << std::to_wstring((UINT_PTR)socket);

		SetThreadDescription(requestThread.native_handle(), ss.str().c_str());

		requestThread.detach();
	}
}

void HttpInterface::RequestHandler(SOCKET clientSocket)
{
	std::cout << "Request from 0x" << std::setw(8) << std::setfill('0') << std::hex << clientSocket << std::endl;

	std::string received, content, method, uri, protocolName, protocolVersion;
	HttpHeaderCollection headers;
	size_t pos = std::string::npos;
	size_t contentLength = 0;

	while (1)
	{
		if (!WinSock::Receive(clientSocket, received))
		{
			std::cout << "Receive failed " << WSAGetLastError() << std::endl;
			// Transmit Error ?
			return;
		}

		std::string out = "-- received ";
		out += std::to_string(received.size());
		out += " bytes\n";
		OutputDebugStringA(out.data());

		content.append(received);

		if (pos == std::string::npos)
		{
			pos = content.find("\r\n\r\n");
			if (pos != std::string::npos &&
				HttpRequest::Parse(content, pos, method, uri, protocolName, protocolVersion, headers))
			{
				auto pContentLengthHeader = headers["content-length"];
				if (pContentLengthHeader) 
				{
					contentLength = pContentLengthHeader->asLongLong();
					pos += 4;
				}
				else 
				{
					break;
				}
			}
		} 

		if (contentLength > 0) 
		{
			size_t loadedContentLength = content.size() - pos;
			if (loadedContentLength >= contentLength)
			{
				break;
			}
		}
	}

	HttpRequest request(method, uri, protocolName, protocolVersion, headers, content, pos, contentLength);
	HttpResponse response(request);

	auto it = m_pRequestHandlers->cbegin();
	while (it != m_pRequestHandlers->cend())
	{
		if (StringCompare(it->pszMethod, request.m_pszMethod, true) && 
			StringCompare(it->pszResource, request.m_pszUri, true))
		{
			it->handler(request, response);
			break;
		}

		++it;
	}
}

HttpInterface& HttpInterface::on(const char* pszMethod, const char* pszResource, REQUEST_HANDLER handler)
{
	REQUEST_HANDLER_INFO reqHandlerInfo;
	ZeroMemory(&reqHandlerInfo, sizeof(reqHandlerInfo));
	reqHandlerInfo.pszMethod = pszMethod;
	reqHandlerInfo.pszResource = pszResource;
	reqHandlerInfo.handler = handler;
	m_pRequestHandlers->push_back(reqHandlerInfo);
	return *this;
}

HttpInterface& HttpInterface::get(const char* pszResource, REQUEST_HANDLER handler)
{
	return on(HttpMethods::Get, pszResource, handler);
}

HttpInterface& HttpInterface::post(const char* pszResource, REQUEST_HANDLER handler)
{
	return on(HttpMethods::Post, pszResource, handler);
}
