#include "DMService.h"
#include <ace/Log_Msg.h>


void DMService::receive(const AMQP::Message &message)
{
	_handle->handle(message);
}
