#include "tn_list.h"

struct list {
    struct list *next;
};

//Initialize a list
void tn_list_init(tn_list_t list)
{
    *list = 0;
}

//Get a pointer to the first element of a list
void *tn_list_head(tn_list_t list)
{
    return *list;
}

//Copy a list
void tn_list_copy(tn_list_t dest, tn_list_t src)
{
    *dest = *src;
}

//Get the tail of a list
void *tn_list_tail(tn_list_t list)
{
    struct list *ptr;

    if (*list == 0) {
        return 0;
    }

    for (ptr = *list; ptr->next != 0; ptr = ptr->next);

    return ptr;
}

//Add an item at the end of a list
void tn_list_add(tn_list_t list, void *item)
{
    struct list *ptr;

    tn_list_remove(list, item);/* Make sure not to add the same element twice */

    ((struct list *)item)->next = 0;

    ptr = tn_list_tail(list);

    if (ptr == 0) {
        *list = item;
    }
    else {
        ptr->next = item;
    }
}

//Add an item to the start of the list.
void tn_list_push(tn_list_t list, void *item)
{
    tn_list_remove(list, item);/* Make sure not to add the same element twice */

    ((struct list *)item)->next = *list;
    *list = item;
}

//Remove the last item from the list
void *tn_list_chop(tn_list_t list)
{
    struct list *ptr, *ptr2;

    if (*list == 0) {
        return 0;
    }

    if (((struct list *)*list)->next == 0) {
        ptr = *list;
        *list = 0;
        return ptr;
    }

    for (ptr = *list; ptr->next->next != 0; ptr = ptr->next);
    ptr2 = ptr->next;
    ptr->next = 0;

    return ptr2;
}

//Remove the first item from a list
void *tn_list_pop(tn_list_t list)
{
    struct list *ptr;
    ptr = *list;
    if (*list != 0) {
        *list = ((struct list *)*list)->next;
    }

    return ptr;
}

//Remove a specified item from a list
void tn_list_remove(tn_list_t list, void *item)
{
    struct list *ptr, *ptr2;

    if (*list == 0) {
        return;
    }

    ptr2 = 0;
    for (ptr = *list; ptr != 0; ptr = ptr->next) {
        if (ptr == item) {
            if (ptr2 == 0) {
                /* first on list */
                *list = ptr->next;
            }
            else {
                /* Not first on list */
                ptr2->next = ptr->next;
            }
            ptr->next = 0;
            return;
        }
        ptr2 = ptr;
    }
}

//Get the length of a list
int tn_list_length(tn_list_t list)
{
    struct list *ptr;
    int n = 0;

    for (ptr = *list; ptr != 0; ptr = ptr->next) {
        ++n;
    }

    return n;
}

//Insert an item after a specified item on the list
void tn_list_insert(tn_list_t list, void *previtem, void *newitem)
{
    if (previtem == 0) {
        tn_list_push(list, newitem);
    }
    else {
        ((struct list *)newitem)->next = ((struct list *)previtem)->next;
        ((struct list *)previtem)->next = newitem;
    }
}

//Get the item next to this item
void *tn_list_item_next(void *item)
{
    return item == 0 ? 0: ((struct list *)item)->next;
}
