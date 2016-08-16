#include "DMServerMessageParser.h"
#include <stdlib.h>
#include "string.h"
#include <ace/Log_Msg.h>
#include <ctype.h>
#include <stdio.h>

template <typename T>
void DMServerMessageParser::DMGetBitData(const char *src, T *dsc, int bit_s, int bit_e)
{
	const char *head_info = src;
	short bit_info = 0x0;

	for (int i = 0;i < HEAD_CHAR_LEN; ++i)
	{
		short char_info = 0x0;
		char_info = char_info | (*(head_info++) & 0xFF);
		char_info = char_info << (CHAR_BIT_LEN * i);
		bit_info = bit_info | char_info;
	}

	bit_info = bit_info << (HEAD_BIT_LEN - bit_e);
	bit_info = bit_info >> (HEAD_BIT_LEN - bit_e + bit_s);

	*dsc =  *dsc | bit_info;
}

int DMServerMessageParser::parse(DMServerMessage& out, const AMQP::Message &in)
{
	if (in.bodySize() < HEAD_CHAR_LEN)
	{
		return 0;
	}

	const char* msg = in.body();

	DMGetBitData(msg,&out.head.id,0,16);
	DMGetBitData(msg,&out.head.from,16,24);
	DMGetBitData(msg,&out.head.to,24,32);
	DMGetBitData(msg,&out.head.sessionid,32,48);
	DMGetBitData(msg,&out.head.type,48,64);

	const char *body = msg + HEAD_CHAR_LEN;
	out.body = new char[in.bodySize() - HEAD_CHAR_LEN];
	memcpy(out.body,body,(in.bodySize() - HEAD_CHAR_LEN));

	return 1;
}

int DMServerMessageParser::pack(DMServerMessage& in, char* out_buf, size_t size)
{
	typedef struct HeadMsg
	{
		int id:16;
		int from:8;
		int to:8;
		int sessionid:16;
		int type:16;
	}HeadMsg;
	
	HeadMsg head;
	head.id = in.head.id;
	head.from = in.head.from;
	head.to = in.head.to;
	head.sessionid = in.head.sessionid;
	head.type = in.head.type;

	memcpy(out_buf,&head,sizeof(HeadMsg));
	memcpy(out_buf + sizeof(HeadMsg),in.body,size - sizeof(HeadMsg));

	return 0;
}