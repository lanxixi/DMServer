#pragma once
#include "DMMessage.h"
//消息路由器。将服务器消息路由到消息服务器
//对于普通服务，直接使用就可。 对于proxyServer，需要重载，添加路由到客户端的能力。

class DMRouter
{
public:
	virtual void route(DMMessage& message);
protected:
private:
};