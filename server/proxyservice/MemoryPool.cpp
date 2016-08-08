#include "MemoryPool.h"
#include <iostream>

MemoryPool* MemoryPool::_instance = nullptr;

MemoryPool* MemoryPool::instance()
{
	if (nullptr == _instance)
	{
		_instance = new MemoryPool();
	}
	return _instance;
}

int MemoryPool::init_memory_poll(int size)
{
	_size = size;
	_unused = size;
	_head = new char[size];
	_free = _head;
	init_page();
	return 0;
}

void MemoryPool::init_page()
{
	//8 byte -> 32 byte
	MemoryPage* pPage_info;

	pPage_info = new MemoryPage;
	pPage_info->set_block_size(8);
	_page.push_back(pPage_info);

	pPage_info = new MemoryPage;
	pPage_info->set_block_size(16);
	_page.push_back(pPage_info);

	pPage_info = new MemoryPage;
	pPage_info->set_block_size(24);
	_page.push_back(pPage_info);

	pPage_info = new MemoryPage;
	pPage_info->set_block_size(32);
	_page.push_back(pPage_info);
}

char* MemoryPool::alloc_memory(int size)
{
	if (_unused < size)
	{
		return nullptr;
	}

	char *p = _free;
	_free = _free + size;
	std::cout<<"alloc:"<<size<<std::endl;
	return p;
}

char* MemoryPool::require(int size)
{
	std::vector<MemoryPage*>::iterator it = _page.begin();
	for (; it != _page.end(); ++it)
	{
		if ((*it)->get_block_size() > size)
		{
			return (*it)->require();
		}
	}

	return nullptr;
}

void MemoryPool::release(int size,char** block)
{
	std::vector<MemoryPage*>::iterator it = _page.begin();
	for (; it != _page.end(); ++it)
	{
		if ((*it)->get_block_size() > size)
		{
			(*it)->release(block);
			break;
		}
	}
}

MemoryPage::MemoryPage():_block(nullptr)
{

}

void MemoryPage::set_block_size(int size)
{
	_block_size = size;
}

int MemoryPage::get_block_size()
{
	return _block_size;
}

char* MemoryPage::require()
{
	if (nullptr == _block)
	{
		_block = new MemoryBlock();
	}
	return _block->require(_block_size);
}

void MemoryPage::release(char** block)
{
	_block->release(block);
}

MemoryBlock::MemoryBlock():_used(false),_block(nullptr)
{

}

void MemoryBlock::init_block(int size)
{
	_next = new MemoryBlock();
	_block = MemoryPool::instance()->alloc_memory(size);
}

char* MemoryBlock::require(int size)
{
	if (nullptr == _block)
	{
		init_block(size);
	}

	if (true == _used)
	{
		return _next->require(size);
	}

	_used = true;

	return  _block;
}

void MemoryBlock::release(char** block)
{
	if (_block != *block)
	{
		_next->release(block);
	}
	_used = false;
}
