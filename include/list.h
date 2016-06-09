#ifndef LIST_H
#define LIST_H

#include "galgo.h"

/*
 * List are implements as doubly-linked list,
 * allow constant time insert and erase operations.
 *
 */

typedef struct _struct_list {
    size_t _size;
    size_t _sizeOfNode;
    ListNode *_head;
    ListNode *_tail;
} List;

typedef struct _list_operation {
    List *(* init)(size_t);
    int (* destroy)(List *const);
    List *(* copy)(List *const);

    ListNode *(* begin)(const List *const);
    ListNode *(* end)(const List *const);
    ListNode *(* rbegin)(const List *const);
    ListNode *(* rend)(const List *const);

    size_t (* size)(const List *const);
    size_t (* sizeOfNode)(const List *const);
    int (* empty)(const List *const);
    size_t (* resize)(List *const, const size_t, void *const);

    ListNode *(* front)(const List *const);
    ListNode *(* back)(const List *const);

    int (* push_back)(List *const, void *const);
    void (* pop_back)(List *const);
    int (* push_front)(List *const, void *const);
    void (* pop_front)(List *const);
    int (* insert)(List *const, ListNode *const, void *const);
    int (* erase)(List *const, ListNode *, ListNode *const);
    int (* swap)(List *const, List *const);
    int (* clear)(List *const);

} List_OP;

extern List_OP *list;

#endif
