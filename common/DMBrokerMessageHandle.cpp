#include "DMBrokerMessageHandle.h"
#include "ace/Reactor.h"
#include <ace/Log_Msg.h>

void DMBrokerMessageHandle::onConnected(AMQP::TcpConnection *connection)
{
	// @todo
	//  add your own implementation, for example by creating a channel
	//  instance, and start publishing or consuming
}

void DMBrokerMessageHandle::onError(AMQP::TcpConnection *connection, const char *message)
{
	// @todo
	//  add your own implementation, for example by reporting the error
	//  to the user of your program, log the error, and destruct the
	//  connection object because it is no longer in a usable state
}

void DMBrokerMessageHandle::onClosed(AMQP::TcpConnection *connection)
{

}

void DMBrokerMessageHandle::monitor(AMQP::TcpConnection *connection, int fd, int flags)
{
	// @todo
	//  add your own implementation, for example by adding the file
	//  descriptor to the main application event loop (like the select() or
	//  poll() loop). When the event loop reports that the descriptor becomes
	//  readable and/or writable, it is up to you to inform the AMQP-CPP
	//  library that the filedescriptor is active by calling the 
	//  connection->process(fd, flags) method.
	_handler = new DMBrokerMessageSvcHandle(connection);
	ACE_Reactor::instance()->register_handler(fd, _handler, ACE_Event_Handler::READ_MASK/*|ACE_Event_Handler::WRITE_MASK*/);

}

DMBrokerMessageSvcHandle::DMBrokerMessageSvcHandle(AMQP::TcpConnection *connection):_connection(connection)
{

}

int DMBrokerMessageSvcHandle::handle_input(ACE_HANDLE fd)
{
	// tell the connection that its filedescriptor is active
	_connection->process(fd, AMQP::readable);
	return 0;
}

int DMBrokerMessageSvcHandle::handle_output(ACE_HANDLE fd /*= ACE_INVALID_HANDLE*/)
{
	// tell the connection that its filedescriptor is active
	//_connection->process(fd, AMQP::writable);
	return 0;
}
