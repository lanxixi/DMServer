#include "DMMessageParser.h"
#include <ace/Log_Msg.h>

DMMessageHead DMMessageParser::parse(char * begin)
{
	DMMessageHead msg_head;

	//DMGetBitData(begin,&msg_head.id,0,16);
	//DMGetBitData(begin,&msg_head.svrid,16,24);
	//DMGetBitData(begin,&msg_head.reserved,24,32);
	//DMGetBitData(begin,&msg_head.type,32,43);
	//DMGetBitData(begin,&msg_head.len,43,64);

	return msg_head;
}

int DMMessageParser::parse(DMMessage& out, const AMQP::Message &in)
{
	DMMessageHead msg_head;

	//DMGetBitData(begin,&msg_head.id,0,16);
	//DMGetBitData(begin,&msg_head.svrid,16,24);
	//DMGetBitData(begin,&msg_head.reserved,24,32);
	//DMGetBitData(begin,&msg_head.type,32,43);
	//DMGetBitData(begin,&msg_head.len,43,64);

	return 1;
}

template <typename T>
void DMMessageParser::DMGetBitData(char *src,T *dsc,int bit_s,int bit_e)
{
	char *head_info = src;
	long long bit_info = 0x0;

	for (int i = 0;i < HEAD_CHAR_LEN; ++i)
	{
		long long char_info = 0x0;
		char_info = char_info | (*(head_info++) & 0xFF);
		char_info = char_info << (CHAR_BIT_LEN * i);
		bit_info = bit_info | char_info;
	}

	bit_info = bit_info << (HEAD_BIT_LEN - bit_e);
	bit_info = bit_info >> (HEAD_BIT_LEN - bit_e + bit_s);

	*dsc =  *dsc | bit_info;
}

int DMMessageParser::pack(DMMessage & mesg, char * buf)
{
	typedef struct HeadMsg
	{
		int id:16;
		int svrid:8;
		int reserved:8;
		int type:11;
		int len:21;
	}HeadMsg;

	HeadMsg head;
//	head.id = mesg.head.id;
//	head.svrid = mesg.head.svrid;
//	head.reserved = mesg.head.reserved;
//	head.type = mesg.head.type;
//	head.len = mesg.head.len;

	memcpy(buf,&head,sizeof(HeadMsg));
	memcpy(buf + sizeof(HeadMsg),mesg.body,head.len);

	return 0;
}
