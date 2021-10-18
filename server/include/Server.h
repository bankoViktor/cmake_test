#ifndef _SERVER_H
#define _SERVER_H

#include "../../core/include/HttpInterface.h"
#include "../../core/include/HttpInterfaceConfigurator.h"

typedef void (*STARTUPPROC)(HttpInterfaceConfigurator& httpInterface);

class Server
{
private:
	HttpInterface *m_pHttpInterface;

public:
	Server();
	~Server();
	void Run();

};

#endif // !_SERVER_H
