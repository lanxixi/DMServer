#pragma once
#include "DMMessage.h"
#include "amqpcpp/include/message.h"

class DMServerMessageParser
{
public:
	enum DataSize
	{
		HEAD_BIT_LEN = 128,
		HEAD_CHAR_LEN = 8,
		CHAR_BIT_LEN = 8
	};
	int parse(DMServerMessage& out, const AMQP::Message &in);

	int pack(DMServerMessage& in, char* out_buf, size_t size);
protected:
private:
	template<typename T> void DMGetBitData(const char *src,T *dsc,int bit_s,int bit_e);
};
