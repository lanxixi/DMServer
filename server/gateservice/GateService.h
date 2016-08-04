#pragma once
#include "DMService.h"
#include "GateAcceptor.h"
#include "ace/INET_Addr.h"

typedef struct server_config_info
{
	std::string host_name;
	std::string host_ip;
	int host_port;
}Server_info;

typedef struct broker_config_info
{
	std::string broker_ip;
	int broker_port;
	std::string broker_user;
	std::string broker_passwd;
	int broker_svrid;
}Broker_info;

class GateService: public DMService
{
public:
	static GateService* instance();

    virtual int init() override;
    	
	virtual void dispatch(DMServerMessage& message) override;

	void receive(const AMQP::Message &message) override;

	virtual void stop(int reason) override;

protected:

	virtual void onStart(int reason) override;

private:
	GateService();

	Server_info _svr_info;
	Broker_info _brk_info;
	GateAcceptor _acceptor;
	static GateService* _instance;
};
