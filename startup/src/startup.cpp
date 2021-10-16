#include "../include/startup.h"
#include <iostream>


int startup(void* pArg)
{
	std::cout << "Hello world from Dynamic Load Library" << std::endl;

	

	return 1;
}
