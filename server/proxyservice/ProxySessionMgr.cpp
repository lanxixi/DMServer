#include "ProxySessionMgr.h"

int ProxySessionManager::add_session(ACE_HANDLE fd, ProxySession* pSession)
{
	_sessions[fd] = pSession;
	return 0;
}