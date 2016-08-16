#include "ProxyServiceHandle.h"
#include "DMMessageParser.h"
#include "DMBrokerProxy.h"
#include "ProxyRouter.h"
#include "ReactorPool.h"
#include "ProxySessionMgr.h"
#include <ace/Log_Msg.h>

void ProxyServiceHandle::handle(const AMQP::Message &message)
{
	//server message
	ACE_DEBUG((LM_INFO,"proxy recevie msg,route to app or others\n"));
}

int ProxyServiceHandle::handle_input(ACE_HANDLE fd /*= ACE_INVALID_HANDLE*/)
{
	ACE_DEBUG((LM_INFO,"app data, route to server!\n"));
	DMMessage client_msg;

	if (!recv_client_data(client_msg))
	{
		return -1;
	}

	switch (client_msg.head.msg_cmd)
	{
	case CLIENT_LOGIN_MSG:
		{
			ProxySessionMgr::instance()->add_session(fd, new ProxySession(this));//fd×÷Îªsessionid
				
			DMMessage server_msg;
			if (!trans_to_svr_msg(client_msg, server_msg))
			{
				return -1;
			}

			break;
		}
	case CLIENT_HEARTBEAT_MSG:
		{
			break;
		}
	case CLIENT_SERVICE_MSG:
		{
			break;
		}
	case CLIENT_NOTIFY_MSG:
		{
			break;
		}
	case CLIENT_MAINT_MSG:
		{
			break;
		}
	}

	return -1;
}
	
bool ProxyServiceHandle::trans_to_svr_msg(DMMessage &client_msg, DMMessage &server_msg)
{
	/*server_msg.head.id = client_msg.head.id;
	server_msg.head.from = PROXY_SERVER_MSG;
	server_msg.head.to = client_msg.head.type & SERVER_MASK;
	server_msg.head.type = client_msg.head.type;
	server_msg.head.sessionid;*/
	//server_msg.
	return true;
}

bool ProxyServiceHandle::recv_client_data(DMMessage &msg)
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

int ProxyServiceHandle::open(void *acceptor_or_connector /*= 0*/)
{
	ACE_DEBUG((LM_INFO,"proxy register_handler = %d\n",get_handle()));

	ACE_Reactor *pReactor = Reactor_Pool::instance()->pull();
	if ( -1 == get_handle() || nullptr == pReactor)
	{
		return -1;
	}

	if ( -1 == pReactor->register_handler(this,ACE_Event_Handler::READ_MASK))
	{
		ACE_DEBUG((LM_INFO,"register_handler failure,all reactor is full!\n"));
		return -1;
	}
	return 0;
}
