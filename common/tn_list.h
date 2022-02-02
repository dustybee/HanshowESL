#ifndef _TN_LIST_H_
#define _TN_LIST_H_

#define STRING_CONCAT(s1, s2) s1##s2

typedef void ** tn_list_t;

//Define a list
#define LIST_DEF(name) \
        static void *STRING_CONCAT(name,_list) = 0; \
        static tn_list_t name = (tn_list_t)&STRING_CONCAT(name,_list)

//Define a list inside a structure
#define LIST_STRUCT_DEF(name) \
        void *STRING_CONCAT(name,_list); \
        tn_list_t name

//Initialize a list that is a member of a structure
#define LIST_STRUCT_INIT(struct_ptr, name)                              \
    do {                                                                \
        (struct_ptr)->name = &((struct_ptr)->STRING_CONCAT(name,_list));   \
        (struct_ptr)->STRING_CONCAT(name,_list) = 0;                    \
        tn_list_init((struct_ptr)->name);                                   \
    } while(0)

void   tn_list_init(tn_list_t list);
void * tn_list_head(tn_list_t list);
void * tn_list_tail(tn_list_t list);
void * tn_list_pop (tn_list_t list);
void   tn_list_push(tn_list_t list, void *item);

void * tn_list_chop(tn_list_t list);

void   tn_list_add(tn_list_t list, void *item);
void   tn_list_remove(tn_list_t list, void *item);

int    tn_list_length(tn_list_t list);

void   tn_list_copy(tn_list_t dest, tn_list_t src);

void   tn_list_insert(tn_list_t list, void *previtem, void *newitem);

void * tn_list_item_next(void *item);

#endif /* _TN_LIST_H_ */
