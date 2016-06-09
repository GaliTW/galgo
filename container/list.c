#include "list.h"
#include <assert.h>

//-- list function
static List *_list_init(size_t sizeOfNode)
{
    sizeOfNode = sizeOfNode ? sizeOfNode : sizeof(ListNode);

    List *z = malloc(sizeof(List));
    assert(z);

    z->_head = malloc(sizeof(ListNode));
    assert(z->_head);

    z->_tail = malloc(sizeof(ListNode));
    assert(z->_tail);

    z->_head->prev = z->_tail->next = 0;
    z->_head->next = z->_tail;
    z->_tail->prev = z->_head;
    z->_size = 0;
    z->_sizeOfNode = sizeOfNode;
    return z;
}

static int _list_destroy(List *const this)
{
    assert(this);

    for (ListNode *i = this->_head, *j; i; j = i, i = i->next, free(j));
    this->_head = this->_tail = 0;

    free(this);
    return 0;
}

static List *_list_copy(List *const this)
{
    assert(this);

    List *z = malloc(sizeof(List));
    assert(z);

    z->_head = malloc(sizeof(ListNode));
    assert(z->_head);

    z->_tail = malloc(sizeof(ListNode));
    assert(z->_tail);

    z->_head->prev = z->_tail->next = 0;

    const size_t sizeOfNode = this->_sizeOfNode;
    ListNode *prev = z->_head, *cur;
    for (ListNode *i = this->_head->next; i != this->_tail; i = i->next) {
        cur = malloc(sizeOfNode);
        memcpy(cur, i, sizeOfNode);
        cur->prev = prev;
        prev = prev->next = cur;
    }
    cur->next = z->_tail;
    z->_tail->prev = cur;

    z->_size = this->_size;
    z->_sizeOfNode = sizeOfNode;
    return z;
}

static ListNode *_list_begin(const List *const this)
{
    assert(this);
    return this->_head->next;
}

static ListNode *_list_end(const List *const this)
{
    assert(this);
    return this->_tail;
}

static ListNode *_list_rbegin(const List *const this)
{
    assert(this);
    return this->_tail->prev;
}

static ListNode *_list_rend(const List *const this)
{
    assert(this);
    return this->_head;
}

static size_t _list_size(const List *const this)
{
    assert(this);
    return this->_size;
}

static size_t _list_sizeOfNode(const List *const this)
{
    assert(this);
    return this->_sizeOfNode;
}

static int _list_empty(const List *const this)
{
    assert(this);
    return !this->_size;
}

static ListNode * _list_front(const List *const this)
{
    assert(this);
    assert(this->_size);

    return this->_head->next;
}

static ListNode * _list_back(const List *const this)
{
    assert(this);
    assert(this->_size);
    return this->_tail->prev;
}

static int _list_push_back(List *const this, void *const node)
{
    assert(this);
    assert(node);

    ListNode *next = this->_tail, *cur = node, *prev = next->prev;
    next->prev = prev->next = cur;
    cur->prev = prev;
    cur->next = next;
    ++this->_size;
    return 0;
}

static void _list_pop_back(List *const this)
{
    assert(this);
    assert(this->_size);

    ListNode *next = this->_tail, *cur = next->prev, *prev = cur->prev;
    next->prev = prev;
    prev->next = next;
    --this->_size;
    free(cur);
}

static int _list_push_front(List *const this, void *const node)
{
    assert(this);
    assert(node);

    ListNode *prev = this->_head, *cur = node, *next = prev->next;
    next->prev = prev->next = cur;
    cur->prev = prev;
    cur->next = next;
    ++this->_size;
    return 0;
}

static void _list_pop_front(List *const this)
{
    assert(this);
    assert(this->_size);

    ListNode *prev = this->_head, *cur = prev->next, *next = cur->next;
    next->prev = prev;
    prev->next = next;
    --this->_size;
    free(cur);
}

static int _list_insert(List *const this, ListNode *const position, void *const node)
{
    assert(this);
    assert(position);
    assert(node);
    ListNode *cur = node, *next = position, *prev = next->prev;

    if (prev) {
        prev->next = cur;
    }

    next->prev = cur;
    cur->prev = prev;
    cur->next = next;

    ++this->_size;
    return 0;
}

static int _list_erase(List *const this, ListNode *cur, ListNode *const next)
{
    assert(this);
    assert(cur && next);
    assert(cur != this->_head);

    ListNode *prev = cur->prev, *t;
    while (cur != next) {
        assert(this->_size);

        t = cur;
        cur = cur->next;

        free(t);
        --this->_size;
    }

    if (prev) {
        prev->next = next;
    }

    next->prev = prev;
    return 0;
}

static int _list_swap(List *const a, List *const b)
{
    assert(a && b);
    size_t s = a->_size;
    a->_size = b->_size;
    b->_size = s;

    s = a->_sizeOfNode;
    a->_sizeOfNode = b->_sizeOfNode;
    b->_sizeOfNode = s;

    ListNode *n = a->_head;
    a->_head = b->_head;
    b->_head = n;

    n = a->_tail;
    a->_tail = b->_tail;
    b->_tail = n;

    return 0;
}

static int _list_clear(List *const this)
{
    assert(this);

    for (ListNode *cur = this->_head, *t; cur != this->_tail; ) {
        t = cur;
        cur = cur->next;
        free(t);
    }
    this->_head->next = this->_tail;
    this->_tail->prev = this->_head;
    this->_size = 0;
    return 0;
}

List_OP *list = &(List_OP) {
    .init        = _list_init,
    .destroy     = _list_destroy,
    .copy        = _list_copy,

    .begin       = _list_begin,
    .end         = _list_end,
    .rbegin      = _list_rbegin,
    .rend        = _list_rend,

    .size        = _list_size,
    .sizeOfNode  = _list_sizeOfNode,
    .empty       = _list_empty,

    .front       = _list_front,
    .back        = _list_back,

    .push_back   = _list_push_back,
    .pop_back    = _list_pop_back,
    .push_front  = _list_push_front,
    .pop_front   = _list_pop_front,
    .insert      = _list_insert,
    .erase       = _list_erase,
    .swap        = _list_swap,
    .clear       = _list_clear,
};
