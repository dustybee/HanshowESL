#include "tn_mm.h"
#include "string.h"

void tn_mem_init(struct mem_desc *m)
{
    memset(m->count, 0, m->num);
    memset(m->mem, 0, m->size*m->num);
}

void *tn_mem_alloc(struct mem_desc *m)
{
    int i;

    for(i = 0; i < m->num; ++i) {
        if(m->count[i] == 0) {
            ++(m->count[i]);
            return (void *)((char *)m->mem + (i * m->size));
        }
    }

    return 0;
}

char tn_mem_free(struct mem_desc *m, void *ptr)
{
    int i;
    char *ptr2;

    ptr2 = (char *)m->mem;
    for (i = 0; i < m->num; ++i) {
        if (ptr2 == (char *)ptr) {
            if (m->count[i] > 0) {
                --(m->count[i]);
            }
            return m->count[i];
        }
        ptr2 += m->size;
    }
    return -1;
}

int tn_mem_inmemb(struct mem_desc *m, void *ptr)
{
    return (char *)ptr >= (char *)m->mem &&
           (char *)ptr < (char *)m->mem + (m->num * m->size);
}

int tn_mem_numfree(struct mem_desc *m)
{
    int i;
    int num_free = 0;

    for(i = 0; i < m->num; ++i) {
        if(m->count[i] == 0) {
            ++num_free;
        }
    }

    return num_free;
}
