#pragma once

/*-------------------------------------------------------------------------------
            msg head:
            --------------------------------------------------
            |       message id       |        user id        |
            --------------------------------------------------
            |       message cmd      |      body length      |
            --------------------------------------------------
            |    from    |     to    | cluster id | node id  |
            --------------------------------------------------
            | wait time  |    flag   |       reserve         |
            --------------------------------------------------

            flag:
                    bit 0:  req/resp
                    bit 1:  login
                    bit 2:  FE-service
                    bit 3:  notify
                    bit 4:  maintain
                    bit 5:  heartbeat
                    bit 6:  timeout 
                    bit 7:  reserve
---------------------------------------------------------------------------------*/

class DMMessageHead
{
public:
	DMClientMessageHead():id(0),user_id(0),msg_cmd(0),length(0),reserved(0){};
	short id;
	short user_id;
	short msg_cmd;
	short length;
	char from;
    char to;
    char cluster_id;
    char node_id;
    char wait_time;
    char flag;
    short reserved;
};

class DMMessage
{
   	DMMessage()
	{
		body = nullptr;
	}
	~DMMessage()
	{
		if (nullptr != body)
		{
			delete[] body;
		}
	}

	DMMessageHead head;
	char* body;
}; 
}

class DMClientMessageHead
{
public:
	DMClientMessageHead():id(0),type(0),len(0),svrid(0),reserved(0){};
	short id;
	short type;
	int len;
	short svrid;
	char reserved;
};

class DMServerMessageHead
{
public:
	DMServerMessageHead():id(0),from(0),to(0),sessionid(0),type(0){};
	short id;
	char from;
	char to;
	short sessionid;
	short type;
};


class DMClientMessage
{
public:
	DMClientMessage()
	{
		body = nullptr;
	}
	~DMClientMessage()
	{
		if (nullptr != body)
		{
			delete[] body;
		}
	}

	DMClientMessageHead head;
	char* body;
};

class DMServerMessage
{
public:
	DMServerMessage()
	{
		body = nullptr;
	}
	~DMServerMessage()
	{
		if (nullptr != body)
		{
			delete[] body;
		}
	}

	DMServerMessageHead head;
	char* body;
};