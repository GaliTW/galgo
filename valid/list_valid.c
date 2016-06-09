#include <stdio.h>
#include "galgo.h"
#include "list.h"

static ListNode *createListNode(data_t value)
{
    ListNode *t = malloc(sizeof(ListNode));
    ((DataNode *)t)->data = value;
    return t;
}

typedef struct _gali_node {
    ListNode father;
    int number;
    char flag;
} GaliNode;

static GaliNode *createGaliNode(data_t value, int number, char flag)
{
    GaliNode *t = malloc(sizeof(GaliNode));
    ((DataNode *)t)->data = value;
    t->number = number;
    t->flag = flag;
    return t;
}

int main(int argc, char **argv)
{
    List *a = list->init(0);
    int sum = 0;
    list->push_back(a, createListNode(100));
    list->push_back(a, createListNode(200));
    list->push_back(a, createListNode(300));

    while (!list->empty(a)) {
        sum += ((DataNode *)list->back(a))->data;
        list->pop_back(a);
    }

    printf("sum: %d\n", sum);
    printf("%ld\n", list->size(a));

    puts("");
    List *b = list->init(sizeof(GaliNode));
    list->push_back(a, createGaliNode(1, 1111, 0));
    list->push_back(a, createGaliNode(2, 2222, 1));
    list->push_back(a, createGaliNode(3, 3333, 1));

    while (!list->empty(a)) {
        GaliNode *n = (GaliNode *)list->back(a);
        list->pop_back(a);

        printf("data: %lld, number: %d, flag: %d\n", ((DataNode *)n)->data, n->number, n->flag);
    }
    printf("%ld\n\n", list->size(b));

    list->destroy(b);

    list->insert(a, list->begin(a), createListNode(100));
    list->insert(a, list->end(a), createListNode(200));
    list->insert(a, list->end(a), createListNode(300));
    list->insert(a, list->begin(a), createListNode(400));
    b = list->copy(a);

    while (!list->empty(a)) {
        DataNode *n = (void *)list->back(a);
        printf("data: %lld\n", n->data);

        list->pop_back(a);
    }
    puts("");

    for (ListNode *it = list->begin(b); it != list->end(b); toNext(it)) {
        it->father.data *= 2;
    }

    for (ListNode *it = list->begin(b); it != list->end(b); toNext(it)) {
        printf("data: %lld\n", it->father.data);
    }
    puts("");

    for (ListNode *it = list->rbegin(b); it != list->rend(b); toPrev(it)) {
        printf("data: %lld\n", it->father.data);
    }
    puts("");

    list->destroy(a);
    list->destroy(b);
    return 0;
}
