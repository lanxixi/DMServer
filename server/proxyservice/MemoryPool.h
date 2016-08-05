#pragma once

//内存池管理。主要提供消息的创建用。
//根据申请内存的大小划分几个档次，建立相应的内存桶
//可参考或直接使用开源库。 https://github.com/emeryberger/Hoard
/*
*-------------------*
|					|
|					|        *----------*		 *----------*
|	  memorypool	|------->|memorypage|------->|memorypage|-------> ... + sizeof(int) = 4 byte
|					|		 |----------|		 |----------|
|					|		 |		    |		 |		    |
*-------------------*		 |		    |		 |		    |
							 | 8 - byte |		 | 12 - byte|
	*--------------*		 |		    |		 |		    |
	|			   |		 |		    |		 |		    |
	|     block	   |<------- |		    |		 |		    |
	|			   |		 |		    |		 |		    |
	*--------------*		 *----------*		 *----------*
*/
#define MEMORY_POLL_SIZE 4096

class MemoryPage;
class MemoryBlock;

typedef struct Pool_Info
{
	MemoryPage* _page;
	int _page_num;
	int _page_size;
}poll_info;

typedef struct Page_Info
{
	struct Page_Info* _next_page;
	MemoryBlock* _block;
	int _block_size;
}page_info;

typedef struct Block_Info
{
	struct Block_Info* _next_block;
	char* _data;
	bool used;
}block_info;

class MemoryPool
{
public:
	int init_memory_poll(int size);

	char* require(int size);

	void release(int size,char* block);

protected:
private:
	int _size;
	char* _head;
	char* _free;
	page_info* _page;
};

class MemoryPage
{

};

class MemoryBlock
{

};
