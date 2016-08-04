#pragma once
#include "DMMessage.h"

class DMClientMessageParser
{
public:
	enum DataSize
	{
		HEAD_BIT_LEN = 64,
		HEAD_CHAR_LEN = 8,
		CHAR_BIT_LEN = 8
	};	
	DMClientMessageHead parseHead(char* begin);

	int pack(DMClientMessage& mesg, char* buf);

protected:
private:
	template<typename T> void DMGetBitData(char *src,T *dsc,int bit_s,int bit_e);
};