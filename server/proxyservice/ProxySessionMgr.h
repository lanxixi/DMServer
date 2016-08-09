#pragma once
#include "ProxySession.h"
#include "ace/Singleton.h"
#include <map>

class ProxySessionManager
{
public:
	int add_session(ACE_HANDLE fd, ProxySession* pSession);

	int activate_session(ACE_HANDLE fd, short uid);

	int activate_session(ProxySession* pSession, short uid);

	ProxySession* find_session(ACE_HANDLE fd);

	ACE_HANDLE find_fd(ProxySession* pSession);

	int del_session(ACE_HANDLE fd);

	int del_session(ProxySession* pSession);

protected:
private:
	ACE_Thread_Mutex _mutex_lock;
	std::map<short, ProxySession*> _sessions;
};

typedef ACE_Singleton<ProxySessionManager, ACE_Thread_Mutex> ProxySessionMgr; 
