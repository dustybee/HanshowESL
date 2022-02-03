#ifndef _TN_MM_H_
#define _TN_MM_H_

#define STR_CONCAT(s1, s2) s1##s2

#define TN_MEM_DEF(name, type, num) \
        static char STR_CONCAT(name,_memb_count)[num]; \
        static type STR_CONCAT(name,_memb_mem)[num]; \
        static struct mem_desc name = {sizeof(type), num, \
                                   STR_CONCAT(name,_memb_count), \
                                   (void *)STR_CONCAT(name,_memb_mem)}

struct mem_desc {
    unsigned short size;
    unsigned short num;
    char *count;
    void *mem;
};

void tn_mem_init(struct mem_desc *m);
void *tn_mem_alloc(struct mem_desc *m);
char tn_mem_free(struct mem_desc *m, void *ptr);
int tn_mem_inmemb(struct mem_desc *m, void *ptr);
int tn_mem_numfree(struct mem_desc *m);

#endif /* _TN_MM_H_ */
