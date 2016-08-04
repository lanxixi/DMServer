#pragma once
//#include "ace/RW_Mutex.h"
#include <map>

//匹配规则为accountid的最后一位(数字或者字符)对应一个proxy.

class ProxyMapManager
{
public:
	static ProxyMapManager* getInstance();
	std::string hash(char accountid);

	//更新配置
	void update(char key, std::string proxy);
	//删除配置
	void remove(char key);
	//从配置文件中读取配置关系
	void load();

protected:
	ProxyMapManager();


private:
	static ProxyMapManager* _instance;

	std::map<char, std::string> _map;

	//ACE_RW_Mutex _mutex;
};

