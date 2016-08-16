#include "GateService.h"
#include "ProxyMapManager.h"
#include "DMBrokerProxy.h"
#include "DMServiceHandle.h"
#include <ace/Log_Msg.h>
#include "json/json.h"
#include <fstream>

GateService* GateService::_instance = NULL;

GateService* GateService::instance()
{
	if (NULL == _instance)
		_instance = new GateService();
	return _instance;
}

DMService* GetService()
{
	return GateService::instance();
}

GateService::GateService()
{

}

int GateService::init()
{    
	ProxyMapManager::getInstance()->load();

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

		Json::Value broker_info = Root["broker_info"];
		_brk_info.broker_ip = broker_info["broker_ip"].asString();
		_brk_info.broker_port = broker_info["broker_port"].asInt();
		_brk_info.broker_user = broker_info["broker_user"].asString();
		_brk_info.broker_passwd = broker_info["broker_passwd"].asString();
		_brk_info.broker_svrid = broker_info["broker_svrid"].asInt();
	}
	
	cfg_file.close();

	ACE_INET_Addr addr(_svr_info.host_port, _svr_info.host_ip.c_str());
	_acceptor.open(addr,ACE_Reactor::instance());

	DMBrokerProxy::getInstance()->init(_brk_info.broker_ip.c_str(),_brk_info.broker_port, _brk_info.broker_user,_brk_info.broker_passwd , _brk_info.broker_svrid);

	return 1;
}

void GateService::receive(const AMQP::Message &message)
{
	GateServiceHandle BrokerHandle;
	BrokerHandle.handle(message);
}

void GateService::dispatch(DMMessage& message)
{
//	throw std::exception("The method or operation is not implemented.");
}

void GateService::stop(int reason)
{
//	throw std::exception("The method or operation is not implemented.");
}

void GateService::onStart(int reason)
{
//	throw std::exception("The method or operation is not implemented.");
}
