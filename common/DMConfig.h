#pragma once
#include <string>

/* 读取服务的配置文件，管理各项配置。
*/
class DMConfig
{
public:
	static DMConfig* getInstance();

	virtual int load();

	std::string getString(std::string key);
protected:
	DMConfig();
	virtual ~DMConfig();
private:
	static DMConfig* _instance;
};

