#include "../include/HttpInterface.h"
#include "../include/WinSock.h"
#include <iostream>
#include <thread>
#include <sstream>
#include <iomanip>

HttpInterface::HttpInterface() :
	m_status(0),
	m_port(0),
	m_socket(INVALID_SOCKET)
{
}

HttpInterface::~HttpInterface()
{
	if (m_socket)
	{
		WinSock::CloseSocket(m_socket);
		m_socket = INVALID_SOCKET;
	}
}

void HttpInterface::Start(int port)
{
	SOCKET socket = INVALID_SOCKET;
	if (!WinSock::CreateSocket(&socket, port))
	{
		std::cout << "WinSock::CreateSocket failed " << WSAGetLastError() << std::endl;
		return;
	}

	m_port = port;
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

bool compareChar(char& c1, char& c2)
{
	if (c1 == c2)
		return true;
	else if (std::toupper(c1) == std::toupper(c2))
		return true;
	return false;
}
/*
 * Case Insensitive String Comparision
 */
bool caseInSensStringCompare(std::string& str1, std::string& str2)
{
	return ((str1.size() == str2.size()) &&
		std::equal(str1.begin(), str1.end(), str2.begin(), &compareChar));
}

void HttpInterface::RequestHandler(SOCKET clientSocket)
{
	std::cout << "Request from 0x" << std::setw(8) << std::setfill('0') << std::hex << clientSocket << std::endl;

	// Recieving

	// Processing

	char buffer[1024 * 5] = { 0 };

	HttpRequest request(buffer, sizeof(buffer));

	HttpResponse response(request);

	const char* resource = "/Index";

	for (int i = 0; i < m_requestHandlers.size(); ++i)
	{
		std::string a = m_requestHandlers[i].pszResource;
		std::string b = resource;
		if (caseInSensStringCompare(a, b))
		{
			m_requestHandlers[i].handler(request, response);
			break;
		}
	}
}

HttpInterface& HttpInterface::on(const char* pszMethod, const char* pszResource, REQUEST_HANDLER handler)
{
	REQUEST_HANDLER_INFO reqHandlerInfo;
	ZeroMemory(&reqHandlerInfo, sizeof(reqHandlerInfo));
	reqHandlerInfo.pszMethod = pszMethod;
	reqHandlerInfo.pszResource = pszResource;
	reqHandlerInfo.handler = handler;
	m_requestHandlers.push_back(reqHandlerInfo);
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
