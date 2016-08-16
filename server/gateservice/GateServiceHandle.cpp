#include <ace/Reactor.h>
#include <ace/Log_Msg.h>
#include "GateServiceHandle.h"
#include "ProxyMapManager.h"
#include "DMMessageParser.h"
#include "GateServiceMsg.pb.h"
#include "GateService.h"
#include <string>

GateServiceHandle::GateServiceHandle()
{

}

GateServiceHandle::~GateServiceHandle()
{

}

void GateServiceHandle::handle(const AMQP::Message &message)
{
	ACE_DEBUG((LM_INFO,"recived msg from server!\n"));
	DMMessageParser parser;

	//parse message
	DMMessage req_msg;
	if (!parser.parse(req_msg,message))
	{
		ACE_DEBUG((LM_INFO,"parse AMQP::Message error!\n"));
		return;
	}
		
	//pb decode
	PBServerMsg msg_pb;
	//std::string pb_data(req_msg.body,req_msg.head.len);

	if (!msg_pb.ParseFromString(req_msg.body))
	{
		ACE_DEBUG((LM_INFO,"ParseFromString error!\n"));
		return;
	}

	std::string key = msg_pb.key();
	std::string proxy = msg_pb.proxy();
	
	switch (req_msg.head.msg_cmd)
	{
	case ADD_PROXY_MSG:
		{
			//添加proxy规则
			ProxyMapManager::getInstance()->update(key.at(0),proxy);
			break;
		}
	case RMV_PROXY_MSG:
		{
			//屏蔽proxy。自动向下更新规则
			ProxyMapManager::getInstance()->remove(key.at(0));
		}
	case STOP_SERVER:
		{
			ACE_Reactor::instance()->end_reactor_event_loop();
		}
		//停服
	default:
		break;
	}
}

int GateServiceHandle::handle_input(ACE_HANDLE fd /*= ACE_INVALID_HANDLE*/)
{
	//recevie msg
	DMMessage req_msg;

	if (!recv_client_data(req_msg))
	{
		return -1;
	}

	//pb decode
	PBClientMsg msg_pb;
	std::string pb_data(req_msg.body,req_msg.head.length);

	if(!msg_pb.ParseFromString(pb_data))
	{
		ACE_DEBUG((LM_INFO,"ParseFromString error!\n"));
		return false;
	}

	//get proxy
	std::string accountid = msg_pb.accountid();
	std::string proxy = ProxyMapManager::getInstance()->hash(accountid.at(accountid.length() - 1)); //传入最后一位hash

	//response app
	DMMessage resp_msg;
	//resp_msg.head.id = req_msg.head.id;
	//resp_msg.head.svrid = req_msg.head.svrid;
	//resp_msg.head.reserved = req_msg.head.reserved;
	//resp_msg.head.type = req_msg.head.type;

	//pb encode
	std::string strBody;
	msg_pb.set_proxy(proxy.c_str(),proxy.length());

	if (!msg_pb.SerializeToString(&strBody))
	{
		return -1;
	}

	resp_msg.head.length = msg_pb.ByteSize();
	resp_msg.body = new char[msg_pb.ByteSize()];

	memcpy(resp_msg.body,strBody.c_str(),strBody.length());

	//send
	send_client_data(resp_msg);

	//close
	return -1;
}

bool GateServiceHandle::recv_client_data(DMMessage &msg)
{
	char head[DMMessageParser::HEAD_CHAR_LEN] = {0};
	peer().recv(head,DMMessageParser::HEAD_CHAR_LEN);
	
	DMMessageParser parser;
	DMMessageHead head_info;
	//parse head
	head_info = parser.parse(head);

	if ( head_info.length <= 0 )
	{
		return false;
	}

	//recive body
	msg.body = new char[head_info.length];
	memset(msg.body,0,head_info.length);
	peer().recv(msg.body,head_info.length);

	msg.head = head_info;

	return true;
}

void GateServiceHandle::send_client_data(DMMessage &msg)
{
	DMMessageParser parser;
	char *buf = new char[DMMessageParser::HEAD_CHAR_LEN + msg.head.length];

	//pack msg
	parser.pack(msg,buf);

	//send
	peer().send_n(buf,DMMessageParser::HEAD_CHAR_LEN + msg.head.length);

	delete[] buf;
}
