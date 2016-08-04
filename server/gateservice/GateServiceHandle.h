#pragma once
#include "DMServiceHandle.h"
#include "ace/Task_T.h"
#include "ace/Synch_Traits.h"
#include "ace/SOCK_Stream.h"
#include "ace/Svc_Handler.h"
#include "DMMessage.h"

enum msg_type
{
	ADD_PROXY_MSG = 1000,
	RMV_PROXY_MSG = 1001,
	STOP_SERVER	  = 1002	
};

class GateServiceHandle : public DMServiceHandle, public ACE_Svc_Handler<ACE_SOCK_Stream, ACE_MT_SYNCH>
{
public:
	GateServiceHandle();
	~GateServiceHandle();
	
	//主要是处理从消息服务器过来的维护、心跳、添加/删除proxy的消息
	virtual void handle(const AMQP::Message &message) override;

	//在连接上接收accountid，返回一个proxyserver的host
	virtual int handle_input(ACE_HANDLE fd = ACE_INVALID_HANDLE) override;
	
private:
	bool recv_client_data(DMClientMessage &msg);
	void send_client_data(DMClientMessage &msg);
};
