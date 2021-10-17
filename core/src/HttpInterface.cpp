#include "../include/HttpInterface.h"
#include "../include/WinSock.h"
#include <iostream>
#include <thread>
#include <sstream>
#include <iomanip>
#include <string>
#include <algorithm>

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

inline void to_upper(std::string& str) 
{
	std::transform(str.begin(), str.end(), str.begin(), ::toupper);
}

inline void to_lower(std::string& str)
{
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);
}

inline void ltrim(std::string& str)
{
	str.erase(0, str.find_first_not_of(" \r\n\t"));
}

size_t parse(std::string& out, const std::string& content, const char* target, size_t offset, int verb = 0)
{
	auto pos = content.find(target, offset);
	auto fragment = content.substr(offset, pos - offset);

	if (verb < 0)
		to_lower(fragment);
	else if (verb > 0)
		to_upper(fragment);

	out = fragment;
	return pos + strlen(target);
}

bool HttpInterface::ParseRequest(
	const std::string& content,
	size_t end,
	std::string& method,
	std::string& uri,
	std::string& protocolName,
	std::string& protocolVersion,
	HttpHeaderCollection& headers)
{
	size_t pos = 0;

	pos = parse(method, content, " ", pos, 1);
	pos = parse(uri, content, " ", pos, -1);
	pos = parse(protocolName, content, "/", pos, +1);
	pos = parse(protocolVersion, content, "\r\n", pos);

	// Headers
	std::string header, value;
	while (pos < end)
	{
		pos = parse(header, content, ":", pos);
		to_lower(header);
		pos = parse(value, content, "\r\n", pos);
		ltrim(value);
		headers.insert(std::pair<std::string, std::string>(header, value));
	}

	return true;
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
			if (pos != std::string::npos)
			{
				ParseRequest(content, pos, method, uri, protocolName, protocolVersion, headers);
				contentLength = std::stoll(headers["content-length"]);
				pos += 4;
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

	//HttpResponse response(request);

	//const char* resource = "/Index";

	//for (int i = 0; i < m_requestHandlers.size(); ++i)
	//{
	//	std::string a = m_requestHandlers[i].pszResource;
	//	std::string b = resource;
	//	if (caseInSensStringCompare(a, b))
	//	{
	//		m_requestHandlers[i].handler(request, response);
	//		break;
	//	}
	//}
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

bool HttpInterface::Receive(SOCKET socket, std::string& data)
{
	
	return true;
}
