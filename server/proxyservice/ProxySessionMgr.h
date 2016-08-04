#pragma once
#include <map>
class ProxySessionMgr
{
public:
protected:
private:
	std::map<short, ProxySession*> _sessions;
};