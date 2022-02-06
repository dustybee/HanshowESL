
#pragma once

#include "../common/types.h"

typedef struct mem_block_t
{
	struct mem_block_t*	next_block;
    char        	data[4];		// must 4 or 8 aligned, padding
}mem_block_t;

typedef struct mem_pool_t
{
    mem_block_t* 	free_list;
}mem_pool_t;

#define MEMPOOL_ALIGNMENT 	4
#define MEMPOOL_ITEMSIZE_2_BLOCKSIZE(s)		((s + (MEMPOOL_ALIGNMENT - 1)) & ~(MEMPOOL_ALIGNMENT-1))

#define MEMPOOL_DECLARE(pool_name, pool_mem, itemsize, itemcount)	\
	mem_pool_t pool_name;											\
	u8 pool_mem[MEMPOOL_ITEMSIZE_2_BLOCKSIZE(itemsize) * itemcount];

mem_pool_t* mempool_init(mem_pool_t* pool, void* mem, int itemsize, int itemcount);
void* mempool_alloc(mem_pool_t* pool);
void mempool_free(mem_pool_t* pool, void* p);
mem_block_t* mempool_header(char* pd);


