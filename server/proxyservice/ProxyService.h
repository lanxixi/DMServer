#pragma once
#include "DMService.h"
#include "DMBrokerProxy.h"
#include "ProxyAcceptor.h"

typedef struct server_config_info
{
	std::string host_name;
	std::string host_ip;
	int host_port;
}Server_info;

typedef struct reactor_config_info
{
	int reactor_thread;
	int reactor_count;
	int reactor_handle_max;
}Reactor_info;

typedef struct broker_config_info
{
	std::string broker_ip;
	int broker_port;
	std::string broker_user;
	std::string broker_passwd;
	int broker_svrid;
}Broker_info;

class ProxyService : public DMService
{
public:

	static ProxyService* instance();

	virtual int init();

	virtual void dispatch();

	virtual void receive(const AMQP::Message &message);

	virtual void stop(int reason);

	void run();

protected:

	virtual void onStart(int reason);

private:
	Server_info _svr_info;
	Reactor_info _reactor_info;
	Broker_info _brk_info;
	ProxyAcceptor _acceptor;
	static ProxyService* _instance;
};
