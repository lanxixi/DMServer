#include "MemoryPool.h"
#include "string.h"
#include <ace/Log_Msg.h>

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

	memset(_head,0,size);
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
		ACE_DEBUG((LM_INFO,"memory pool have not enough free block\n"));
		return nullptr;
	}

	_unused += size;
	char *p = _free;
	_free = _free + size;
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

/*
   size²ÎÊý´óÐ¡±ØÐëÓëÉêÇë´óÐ¡±£³ÖÒ»ÖÂ
*/
void MemoryPool::release(int size,char* block)
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

MemoryPage::MemoryPage()
{
	_block.push_back(new MemoryBlock());
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
	std::vector<MemoryBlock*>::iterator it = _block.begin();
	for (; it != _block.end(); ++it)
	{
		if (!((*it)->get_block_state()))
		{
			return (*it)->require(_block_size);
		}
	}

	MemoryBlock* p = new MemoryBlock();
	_block.push_back(p);
	return p->require(_block_size);
}

void MemoryPage::release(char* block)
{
	std::vector<MemoryBlock*>::iterator it = _block.begin();
	for (; it != _block.end(); ++it)
	{
		if ((*it)->get_block_state())
		{
			if ((*it)->release(block))
			{
				break;
			}
		}
	}
}

MemoryBlock::MemoryBlock():_used(false),_block(nullptr)
{

}

void MemoryBlock::make_block(int size)
{
	_block = MemoryPool::instance()->alloc_memory(size);
}

char* MemoryBlock::require(int size)
{
	if (nullptr == _block)
	{
		make_block(size);

		if (nullptr == _block)
		{
			return nullptr;
		}
	}

	memset(_block,0,size);
	_used = true;

	return _block;
}

bool MemoryBlock::release(char* block)
{
	if (_block != block)
	{
		return false;
	}

	_used = false;
	
	return true;
}

bool MemoryBlock::get_block_state()
{
	return _used;
}

