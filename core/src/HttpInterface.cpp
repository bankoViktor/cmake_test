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
	std::string content, method, uri, protocolName, protocolVersion;
	HttpHeaderCollection headers;

	if (!Receive(clientSocket, headers, method, uri, protocolName, protocolVersion, content)) return;

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

	if (!Transmit(clientSocket, response)) return;

	WinSock::CloseSocket(clientSocket);

	std::cout 
		<< std::setfill('.') 
		<< std::setw(4) << std::right << clientSocket << ' '
		<< std::setw(10) << std::left << request.m_sMethod << ' '
		<< std::setw(80) << request.m_sUri << ' '
		<< std::setw(3) << response.GetStatusCode() << ' '
		<< std::setw(18) << std::left << HttpResponse::TranslateStatusCode((HttpStatusCodes)response.GetStatusCode())
		<< std::endl;
}

bool HttpInterface::Receive(
	SOCKET socket,
	HttpHeaderCollection& headers,
	std::string& method,
	std::string& uri,
	std::string& protocolName,
	std::string& protocolVersion,
	std::string& body)
{
	body.clear();

	std::string received, content;
	size_t pos = std::string::npos;
	size_t contentLength = 0;

	while (true)
	{
		if (!WinSock::Receive(socket, received))
		{
			std::cout << "Receive failed " << WSAGetLastError() << std::endl;
			// Transmit Error ?
			return false;
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
					break;
				}
			}
		}

		if (contentLength > 0)
		{
			size_t loadedContentLength = content.size() - pos;
			if (loadedContentLength >= contentLength)
			{
				body = content.substr(pos, loadedContentLength);
				break;
			}
		}
	}

	return true;
}

bool HttpInterface::Transmit(
	SOCKET socket,
	const HttpResponse& response)
{
	std::stringstream ss;

	return response.WriteData(ss) && WinSock::Transmit(socket, ss.str());
}