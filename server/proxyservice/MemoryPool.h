#pragma once

//内存池管理。主要提供消息的创建用。
//根据申请内存的大小划分几个档次，建立相应的内存桶
//可参考或直接使用开源库。 https://github.com/emeryberger/Hoard

class MemoryPool
{
public:
	char* require(size_t size);
	void release(char* block);
protected:
private:

};