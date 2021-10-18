#include "../include/Server.h"
#include "../../core/include/WinSock.h"
#include <iostream>
#include "../../core/include/HttpInterfaceConfigurator.h"

Server::Server()
{
	WinSock::Initialization();

	m_pHttpInterface = nullptr;
}

Server::~Server()
{
	SafeReleasePonter(m_pHttpInterface);

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
		std::cout << "The startup function in '" << pszStartupLibraryName << "' not found." << std::endl;
		return;
	}

	HttpInterfaceConfigurator configurator;

	srartupProc(configurator);

	m_pHttpInterface = new HttpInterface(configurator);

	m_pHttpInterface->Start(dwPort);

	std::cout << "Started on port " << dwPort << std::endl;

	while (true) {}
}
