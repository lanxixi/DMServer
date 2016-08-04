#pragma once
#include "amqpcpp.h"
#include "DMBrokerMessageHandle.h"

//rabitmq服务器连接代理，供service的dispatch使用
class DMBrokerProxy
{
public:
	static DMBrokerProxy* getInstance()
	{
		if (NULL == _instance)
		{
			_instance = new DMBrokerProxy();
		}
		return _instance;
	}

	int init(std::string host, int port, std::string username,std::string userpasswd,int svrid);

	void publish(const std::string &exchange, const std::string &routingKey, const char *message, size_t size);

	void runEvents();

	void destroy();
	//AMQP::Channel& getChannel();
	//AMQP::Exchange AgetExchange();
protected:
	DMBrokerProxy(){};
	virtual ~DMBrokerProxy();
private:
	DMBrokerMessageHandle* _handle;
	AMQP::TcpChannel* _channel;
	AMQP::TcpConnection* _connection;
	static DMBrokerProxy *_instance;
};
