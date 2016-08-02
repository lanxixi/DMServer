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

enum msg_type
{
    ADD_PROXY_MSG = 1000,
    RMV_PROXY_MSG = 1001,
    STOP_SERVER   = 1002    
};

class DMMessageHead
{
public:
	DMMessageHead():msg_id(0),user_id(0),msg_cmd(0),length(0),
        from(0),to(0),cluster_id(0),node_id(0),wait_time(0),flag(0),reserved(0){};
	short msg_id;
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
    
    DMMessageHead& operator=(DMMessageHead other)
    {
        this->msg_id = other.msg_id;
        this->user_id = other.user_id;
        this->msg_cmd = other.msg_cmd;
        this->length = other.length;
        this->from = other.from;
        this->to = other.to;
        this->cluster_id = other.cluster_id;
        this->node_id = other.node_id;
        this->wait_time = other.wait_time;
        this->flag = other.flag;   
        this->reserved = other.reserved;
        
        return *this;
    }
};

class DMMessage
{
public:
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
