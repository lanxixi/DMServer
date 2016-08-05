#pragma once
#include "../Common/DSRouter.h"

class ProxyRouter:public DSRouter
{
public:

	//添加路由消息到客户端的能力,服务器间路由基类实现
	virtual void route(DSServerMessage& message) override
	{
		//throw std::exception("The method or operation is not implemented.");
	}

protected:
private:
};