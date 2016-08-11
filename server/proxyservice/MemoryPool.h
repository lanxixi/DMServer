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
#include "ace/Thread_Mutex.h"
#include <vector>

class MemoryPage;
class MemoryBlock;

class MemoryPool
{
	friend class MemoryBlock;
public:
	static MemoryPool* instance();

	int init_memory_pool(int size);

	char* require(int size);

	void release(int size,char* block);

private:
	void init_page();

	char* alloc_memory(int size);

private:
	int _size;
	int _unused;
	char* _head;
	char* _free;
	std::vector<MemoryPage*> _page;
	static MemoryPool* _instance;
	static ACE_Thread_Mutex _lock;
	ACE_Thread_Mutex _mutex_lock;
};

class MemoryPage
{
public:
	MemoryPage();

	void set_block_size(int size);

	int get_block_size();

	char* require();

	void release(char* block);

private:
	int _block_size;
	std::vector<MemoryBlock*> _block;
};

class MemoryBlock
{
public:
	MemoryBlock();

	char* require(int size);

	bool release(char* block);

	bool get_block_state();

private:
	void make_block(int size);
	
private:
	bool _used;
	char* _block;
};
