#include "../include/Server.h"
#include "../../core/include/WinSock.h"
#include <iostream>

Server::Server()
{
	WinSock::Initialization();
}

Server::~Server()
{
	WinSock::Uninitialization();
}

void Server::Run()
{
	const char* pszStartupLibraryName = "startup.dll";
	const int dwPort = 80;

	HMODULE hModule = LoadLibraryA(pszStartupLibraryName);
	if (!hModule)
	{
		std::cout << "The startup dynamic library '" << pszStartupLibraryName << "' not found." << std::endl;
		return;
	}

	STARTUPPROC srartupProc = (STARTUPPROC)GetProcAddress(hModule, "Startup");
	if (!srartupProc)
	{
		std::cout << "The 'void startup(HttpInterface&)' function in '" << pszStartupLibraryName << "' not found." << std::endl;
		return;
	}

	srartupProc(m_httpInterface);

	m_httpInterface.Start(dwPort);

	std::cout << "Started on port " << dwPort << std::endl;

	while (true) {}
}
