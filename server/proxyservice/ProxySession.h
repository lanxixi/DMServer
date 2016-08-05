#pragma once
#include "ace/Svc_Handler.h"
#include "ace/SOCK_Stream.h"

typedef ACE_Svc_Handler<ACE_SOCK_STREAM, ACE_MT_SYNCH> Svc_Handler;

class ProxySession
{
public:
	ProxySession(Svc_Handler* handle):_handle(handle){};

	short id;

	void bind(Svc_Handler* handle) { _handle = handle; };
protected:
private:
	Svc_Handler* _handle;
};