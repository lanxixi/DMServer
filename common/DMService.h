#pragma once
#include "amqpcpp/include/message.h"
#include "DMServiceHandle.h"
#include "DMRouter.h"

//������Ϊ���п���ʽ��service�Ǽ��п�������

class DMService
{
public:
	virtual int init()=0;
	virtual void dispatch(DMServerMessage& message) { _router->route(message); };
	virtual void receive(const AMQP::Message &message);
	
	virtual void stop(int reason) {};

	void setHandle(DMServiceHandle* hanle) { _handle = hanle; };
	void setRouter(DMRouter* router) { _router = router; };
protected:
	virtual void onStart(int reason) {};

	DMServiceHandle* _handle;
	DMRouter* _router;
};