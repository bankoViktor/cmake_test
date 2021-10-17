#ifndef _SERVER_H
#define _SERVER_H

#include "../../core/include/HttpInterface.h"

typedef void (*STARTUPPROC)(HttpInterface& httpInterface);

class Server
{
private:
	HttpInterface m_httpInterface;

public:
	Server();
	~Server();
	void Run();

};

#endif // !_SERVER_H
