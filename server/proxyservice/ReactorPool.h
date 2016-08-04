#pragma once
#include "ace/Reactor.h"

class ReactorPool
{
public:
	static ReactorPool* getInstance();

	//取出一个可用的reactor。 一个reactor限制挂载1000个handle
	ACE_Reactor* pull();
protected:
	//初始化固定数量的reactor
	ACE_Reactor** _pool;
private:
};