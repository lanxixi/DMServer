#pragma once
#include "ProxySession.h"
#include "ace/Singleton.h"
#include <map>

class ProxySessionManager
{
public:
	int add_session(ACE_HANDLE fd, ProxySession* pSession);

	/*int activate_session();

	ProxySession* find_session();

	int del_session();*/

protected:
private:
	std::map<short, ProxySession*> _sessions;
};

typedef ACE_Singleton<ProxySessionManager, ACE_Thread_Mutex> ProxySessionMgr; 
