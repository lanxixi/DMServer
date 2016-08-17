#pragma once
#include "DMServiceHandle.h"
#include "ace/Task_T.h"
#include "ace/Synch_Traits.h"
#include "ace/SOCK_Stream.h"
#include "ace/Svc_Handler.h"
#include "DMMessage.h"

class ProxyServiceHandle : public DMServiceHandle, public ACE_Svc_Handler<ACE_SOCK_STREAM, ACE_MT_SYNCH>
{
public:

	//主要是处理从消息服务器过来的维护、心跳、添加/删除proxy的消息
	virtual void handle(const AMQP::Message &message) override;

	//在连接上接收accountid，返回一个proxyserver的host
	virtual int handle_input(ACE_HANDLE fd = ACE_INVALID_HANDLE) override;

	bool recv_client_data(DMMessage &msg);

	//重写实现。需要绑定到不同的reactor上面
	virtual int open(void *acceptor_or_connector = 0) override;
};
