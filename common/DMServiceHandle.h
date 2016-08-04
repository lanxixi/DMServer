#pragma once

#include "amqpcpp/amqpcpp.h"
class DMServiceHandle
{
public:
	virtual void handle(const AMQP::Message &message) = 0;
private:
};
