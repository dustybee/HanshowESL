
#include "mempool.h"
#include "utility.h"

mem_pool_t* mempool_init(mem_pool_t* pool, void* mem, int itemsize, int itemcount)
{
    if (!pool || !mem) 	
		return (0);
	
	pool->free_list = (mem_block_t*)mem;

    u32 block_size = (u32)(MEMPOOL_ITEMSIZE_2_BLOCKSIZE(itemsize));
	mem_block_t* tmp = (mem_block_t*)mem;
	int i;
	for(i = 0; i < itemcount - 1; ++i){
		tmp = tmp->next_block = (mem_block_t*)(((u32)tmp) + block_size);
	}
	tmp->next_block = 0;
	return pool;
}

mem_block_t* mempool_header(char* pd){
	return (mem_block_t*)(pd - OFFSETOF(mem_block_t, data));
}

void* mempool_alloc(mem_pool_t* pool)
{
	if(!pool->free_list)
		return 0;
	mem_block_t* tmp = pool->free_list;
	pool->free_list = tmp->next_block;
	return &tmp->data;
}

void mempool_free(mem_pool_t* pool, void* p)
{
	mem_block_t* tmp = mempool_header((char*)p);
	tmp->next_block = pool->free_list;
	pool->free_list = tmp;
}
