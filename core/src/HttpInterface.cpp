#include "../include/WinSock.h"
#include "../include/HttpInterface.h"
#include "../include/HttpRequest.h"
#include "../include/HttpResponse.h"
#include <iostream>
#include <thread>
#include <sstream>
#include <iomanip>
#include <string>
#include <algorithm>

HttpInterface::HttpInterface(const HttpInterfaceConfigurator& configurator) :
	m_dwPort(DEFAULT_PORT),
	m_socket(INVALID_SOCKET)
{
	m_pRequestHandlers = new HttpHandlerCollection(*configurator.m_pRequestHandlers);
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

	while (true)
	{
		if (!WinSock::Receive(clientSocket, received))
		{
			std::cout << "Receive failed " << WSAGetLastError() << std::endl;
			// Transmit Error ?
			return;
		}

		content.append(received);

		if (pos == std::string::npos)
		{
			pos = content.find("\r\n\r\n");
			if (pos != std::string::npos &&
				HttpRequest::Parse(content, pos, method, uri, protocolName, protocolVersion, headers))
			{
				const char* contentLengthHeaderName = "content-length";
				if (headers.IsContains(contentLengthHeaderName))
				{
					auto& header = headers[contentLengthHeaderName];
					contentLength = header.asLongLong();
					pos += 4;
				}
				else 
				{
					content.clear();
					break;
				}
			}
		} 

		if (contentLength > 0) 
		{
			size_t loadedContentLength = content.size() - pos;
			if (loadedContentLength >= contentLength)
			{
				content.erase(0, content.size() - contentLength);
				break;
			}
		}
	}

	HttpRequest request(headers, method, uri, protocolName, protocolVersion, content);

	HttpResponse response(request);

	auto it = m_pRequestHandlers->cbegin();
	while (it != m_pRequestHandlers->cend())
	{
		if (StringCompare(it->pszMethod, request.m_sMethod.c_str(), true) && 
			StringCompare(it->pszResource, request.m_sUri.data(), true))
		{
			it->handler(request, response);
			break;
		}
		++it;
	}
}

