#pragma once
#include "DMMessage.h"
#include "amqpcpp/include/message.h"

class DMMessageParser
{
public:
	enum DataSize
	{
		HEAD_BIT_LEN = 128,
		HEAD_CHAR_LEN = 16,
		CHAR_BIT_LEN = 8
	};	
    
	DMMessageHead parse(char* begin);
    
    int parse(DMMessage& out, const AMQP::Message &in);
    
	int pack(DMMessage& mesg, char* buf);

protected:
private:
	template<typename T> void DMGetBitData(char *src,T *dsc,int bit_s,int bit_e);

    template<typename T> void DMGetBitData(const char *src, T *dsc, int bit_s, int bit_e);
};
