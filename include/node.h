#ifndef NODE_H
#define NODE_H

#include "galgo.h"

typedef struct _data_node {
    data_t data;
} DataNode;

typedef struct _list_node {
    DataNode father;
    struct _list_node *prev;
    struct _list_node *next;
} ListNode;

typedef struct _tree_node {
    DataNode father;
    struct _tree_node *left;
    struct _tree_node *right;
} TreeNode;

#define data(node) (((DataNode *)node)->data)
#define prev(node) (((ListNode *)node)->prev)
#define next(node) (((ListNode *)node)->next)
#define left(node) (((TreeNode *)node)->left)
#define right(node) (((TreeNode *)node)->right)
#define toPrev(node) (node = prev(node))
#define toNext(node) (node = next(node))
#define toLeft(node) (node = left(node))
#define toRight(node) (node = right(node))

#endif
