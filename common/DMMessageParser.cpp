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
	char *head_info = src;  //头地址
	short bit_info = 0x0;   //结果数据

	for (int i = 0; i < HEAD_CHAR_LEN; ++i)  //16 * 8 = 128
	{     
		bit_info = bit_info | (*(head_info++) & 0xFF);    //只取8位防止高位为1编译器转32位做取反操作
        
        if (bit_s == (CHAR_BIT_LEN * i))
        { 
    		break;
        }   
        
        bit_info = 0x0;
	}

    if (CHAR_BIT_LEN != (bit_e - bit_s))    //取16位
    {
        bit_info = bit_info | ((*head_info & 0xFF) << CHAR_BIT_LEN);
    }
        
	*dsc =  *dsc | bit_info;
}

template <typename T>
void DMMessageParser::DMGetBitData(const char *src, T *dsc, int bit_s, int bit_e)
{
	const char *head_info = src;
	short bit_info = 0x0;

	for (int i = 0; i < HEAD_CHAR_LEN; ++i)
	{     
		bit_info = bit_info | (*(head_info++) & 0xFF);
        
        if (bit_s == (CHAR_BIT_LEN * i))
        { 
    		break;
        }   
                
        bit_info = 0x0;
	}

    if (CHAR_BIT_LEN != (bit_e - bit_s))
    {
        bit_info = bit_info | ((*head_info & 0xFF) << CHAR_BIT_LEN);
    }
        
	*dsc =  *dsc | bit_info;
}

int DMMessageParser::pack(DMMessage & mesg, char * buf)
{
	DMMessageHead head;

    head = mesg.head;

	memcpy(buf,&head,sizeof(head));
	memcpy(buf + sizeof(head),mesg.body,head.length);

	return 0;
}
