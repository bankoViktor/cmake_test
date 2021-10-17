#ifndef _STARTUP_H
#define _STARTUP_H

#include "../../core/include/HttpInterface.h"
#include "export.h"

#ifdef __cplusplus
extern "C"
{
#endif

DLLEXPORTED void Startup(HttpInterface& httpInterface);

#ifdef __cplusplus
}
#endif

#endif // !_STARTUP_H