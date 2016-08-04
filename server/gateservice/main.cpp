#include "ace/OS_main.h"
#include "ace/Reactor.h"
#include "GateService.h"
#include <ace/Log_Msg.h>

int ACE_TMAIN(int argc, ACE_TCHAR *argv[])
{
	if (!GateService::instance()->init())
	{
		return 0;
	}
    ACE_Reactor::instance()->run_reactor_event_loop();
	return 0;
}
