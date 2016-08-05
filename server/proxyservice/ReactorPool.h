#pragma once
#include "ace/Reactor.h"
#include "ace/Singleton.h"
#include <vector>

class ReactorPool
{
public:
	void init(int reactor_count, int handle_max);

	//取出一个可用的reactor。 一个reactor限制挂载1000个handle
	ACE_Reactor* pull();

	void run_event_loop(int reactor_thread);
protected:
	//初始化固定数量的reactor
	std::vector<ACE_Reactor*> _reactor_pool;
	ACE_Thread_Mutex _mutex_lock;
	//ACE_Reactor** _pool;
private:
};

typedef ACE_Singleton<ReactorPool, ACE_Thread_Mutex> Reactor_Pool; 
