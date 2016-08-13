#include "DMMessageParser.h"
#include <ace/Log_Msg.h>

DMMessageHead DMMessageParser::parse(char * begin)
{
	DMMessageHead msg_head;

	DMGetBitData(begin,&msg_head.msg_id,0,16);
	DMGetBitData(begin,&msg_head.user_id,16,32);
	DMGetBitData(begin,&msg_head.msg_cmd,32,48);
	DMGetBitData(begin,&msg_head.length,48,64);
	DMGetBitData(begin,&msg_head.from,64,72);
	DMGetBitData(begin,&msg_head.to,72,80);
	DMGetBitData(begin,&msg_head.cluster_id,80,88);
	DMGetBitData(begin,&msg_head.node_id,88,96);
	DMGetBitData(begin,&msg_head.wait_time,96,104);
	DMGetBitData(begin,&msg_head.flag,104,112);

	return msg_head;
}

int DMMessageParser::parse(DMMessage& out, const AMQP::Message &in)
{
	DMMessageHead msg_head;
    
	if (in.bodySize() < HEAD_CHAR_LEN)
	{
		return 0;
	}

	const char* msg = in.body();

	DMGetBitData(msg,&msg_head.msg_id,0,16);
	DMGetBitData(msg,&msg_head.user_id,16,32);
	DMGetBitData(msg,&msg_head.msg_cmd,32,48);
	DMGetBitData(msg,&msg_head.length,48,64);
	DMGetBitData(msg,&msg_head.from,64,72);
	DMGetBitData(msg,&msg_head.to,72,80);
	DMGetBitData(msg,&msg_head.cluster_id,80,88);
	DMGetBitData(msg,&msg_head.node_id,88,96);
	DMGetBitData(msg,&msg_head.wait_time,96,104);
	DMGetBitData(msg,&msg_head.flag,104,112);
    
	const char *body = msg + HEAD_CHAR_LEN;
	out.body = new char[in.bodySize() - HEAD_CHAR_LEN];
	memcpy(out.body,body,(in.bodySize() - HEAD_CHAR_LEN));

	return 1;
}

template <typename T>
void DMMessageParser::DMGetBitData(char *src,T *dsc,int bit_s,int bit_e)
{
	char *head_info = src;
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

template <typename T>
void DMMessageParser::DMGetBitData(const char *src, T *dsc, int bit_s, int bit_e)
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
