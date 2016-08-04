#pragma once

class ProxySession
{
public:
	short id;

	void bind(ACE_Svc_Handler* handle) { _handle = handle; };
protected:
private:
	ACE_Svc_Handler* _handle;
};