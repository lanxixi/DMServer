#pragma once
#include "amqpcpp.h"
#include "ace/Event_Handler.h"

class DMBrokerMessageSvcHandle :public ACE_Event_Handler
{
public:
	DMBrokerMessageSvcHandle(AMQP::TcpConnection *connection);

	//virtual int handle_close(ACE_HANDLE, ACE_Reactor_Mask);

	//接收到socket上的数据。 需要调用ampq的parse
	/**
	*  Parse data that was recevied from RabbitMQ
	*
	*  Every time that data comes in from RabbitMQ, you should call this method to parse
	*  the incoming data, and let it handle by the AMQP-CPP library. This method returns
	*  the number of bytes that were processed.
	*
	*  If not all bytes could be processed because it only contained a partial frame,
	*  you should call this same method later on when more data is available. The
	*  AMQP-CPP library does not do any buffering, so it is up to the caller to ensure
	*  that the old data is also passed in that later call.
	*
	*  @param  buffer      buffer to decode
	*  @param  size        size of the buffer to decode
	*  @return             number of bytes that were processed
	
	size_t parse(char *buffer, size_t size)
	*/

	virtual int handle_input(ACE_HANDLE fd);


	virtual int handle_output(ACE_HANDLE fd = ACE_INVALID_HANDLE);

protected:
private:
	AMQP::TcpConnection *_connection;
};


class DMBrokerMessageHandle : public AMQP::TcpHandler
{
public:

	/**
	*  Method that is called by the AMQP library when the login attempt
	*  succeeded. After this method has been called, the connection is ready
	*  to use.
	*  @param  connection      The connection that can now be used
	*/
	virtual void onConnected(AMQP::TcpConnection *connection);

	/**
	*  Method that is called by the AMQP library when a fatal error occurs
	*  on the connection, for example because data received from RabbitMQ
	*  could not be recognized.
	*  @param  connection      The connection on which the error occured
	*  @param  message         A human readable error message
	*/
	virtual void onError(AMQP::TcpConnection *connection, const char *message);

	/**
	*  Method that is called when the connection was closed. This is the
	*  counter part of a call to Connection::close() and it confirms that the
	*  connection was correctly closed.
	*
	*  @param  connection      The connection that was closed and that is now unusable
	*/
	virtual void onClosed(AMQP::TcpConnection *connection);

	/**
	*  Method that is called by the AMQP-CPP library when it wants to interact
	*  with the main event loop. The AMQP-CPP library is completely non-blocking,
	*  and only make "write()" or "read()" system calls when it knows in advance
	*  that these calls will not block. To register a filedescriptor in the
	*  event loop, it calls this "monitor()" method with a filedescriptor and
	*  flags telling whether the filedescriptor should be checked for readability
	*  or writability.
	*
	*  @param  connection      The connection that wants to interact with the event loop
	*  @param  fd              The filedescriptor that should be checked
	*  @param  flags           Bitwise or of AMQP::readable and/or AMQP::writable
	*/
	virtual void monitor(AMQP::TcpConnection *connection, int fd, int flags);

protected:
	ACE_Event_Handler* _handler;

};
