#include "ace/OS_main.h"
#include "ace/Reactor.h"
#include "ProxyService.h"

int ACE_TMAIN(int argc, ACE_TCHAR *argv[])
{
	if (!ProxyService::instance()->init())
	{
		return 0;
	}
    ProxyService::instance()->run();
	return 0;
}
