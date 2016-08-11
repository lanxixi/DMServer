#include "ProxyService.h"
#include "ace/INET_Addr.h"
#include "ace/Log_Msg.h"
#include <fstream>
#include "DMBrokerProxy.h"
#include "DMServiceHandle.h"
#include "json/json.h"
#include "ace/Dev_Poll_Reactor.h"
#include "ReactorPool.h"
#include "MemoryPool.h"

DMService* GetService()
{
	return ProxyService::instance();
}

ProxyService* ProxyService::_instance = nullptr;

ProxyService* ProxyService::instance()
{
	if (nullptr == _instance)
	{
		_instance = new ProxyService();
	}
	return _instance;
}

int ProxyService::init()
{
	std::ifstream cfg_file;
	cfg_file.open("config.json",std::ios::binary);

	if (!cfg_file.is_open())
	{ 
		return 0;
	}

	Json::Reader Reader;
	Json::Value Root;

	if (Reader.parse(cfg_file,Root))
	{
		_svr_info.host_name = Root["host_name"].asString();
		_svr_info.host_ip = Root["host_ip"].asString();
		_svr_info.host_port = Root["host_port"].asInt();

		Json::Value reactor_info = Root["reactor_info"];
		_reactor_info.reactor_thread = reactor_info["reactor_thread"].asInt();
		_reactor_info.reactor_count = reactor_info["reactor_count"].asInt();
		_reactor_info.reactor_handle_max = reactor_info["reactor_handle_max"].asInt();

		Json::Value broker_info = Root["broker_info"];
		_brk_info.broker_ip = broker_info["broker_ip"].asString();
		_brk_info.broker_port = broker_info["broker_port"].asInt();
		_brk_info.broker_user = broker_info["broker_user"].asString();
		_brk_info.broker_passwd = broker_info["broker_passwd"].asString();
		_brk_info.broker_svrid = broker_info["broker_svrid"].asInt();

		int memory_pool_size = Root["memory_pool"].asInt();
		MemoryPool::instance()->init_memory_pool(memory_pool_size);
	}
	
	cfg_file.close();

	Reactor_Pool::instance()->init(_reactor_info.reactor_count,_reactor_info.reactor_handle_max);

	ACE_INET_Addr addr(_svr_info.host_port, _svr_info.host_ip.c_str());
	_acceptor.open(addr,ACE_Reactor::instance());

	DMBrokerProxy::getInstance()->init(_brk_info.broker_ip.c_str(),_brk_info.broker_port, _brk_info.broker_user,_brk_info.broker_passwd , _brk_info.broker_svrid);

	return 1;
}


void ProxyService::dispatch()
{
	//throw std::exception("The method or operation is not implemented.");
}


void ProxyService::receive(const AMQP::Message &message)
{	
	ProxyServiceHandle ProxyHandle;
	ProxyHandle.handle(message);
}


void ProxyService::stop(int reason)
{
	//throw std::exception("The method or operation is not implemented.");
}

void ProxyService::onStart(int reason)
{
	//throw std::exception("The method or operation is not implemented.");
}

void ProxyService::run()
{
	Reactor_Pool::instance()->run_event_loop(_reactor_info.reactor_thread);
}
