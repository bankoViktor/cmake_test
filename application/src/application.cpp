#include "../include//application.h"

int main()
{
	std::cout << "Hello CMake." << std::endl;

	HMODULE hLib = LoadLibraryA("..\\startup\\startup.dll");
	if (hLib)
	{
		STARTUP_FUNC startup = (STARTUP_FUNC)GetProcAddress(hLib, "startup");
		if (startup)
		{
			int arg = 2;
			int iResult = startup(&arg);
		}

		FreeLibrary(hLib);
	}


	system("pause");
	return 0;
}
