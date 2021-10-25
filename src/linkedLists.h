#ifndef __LINKEDLISTS_H__
#define __LINKEDLISTS_H__

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    struct Node *previous;
    void *data;
    struct Node *next;
} Node;

typedef struct LinkedList
{
    Node *head;
    Node *tail;
    uint32_t size;

    void (*push_back)(struct LinkedList* list, void* data, uint32_t size);
    void (*push_front)(struct LinkedList* list, void* data, uint32_t size);
    void* (*pop_back)(struct LinkedList *list);
    void* (*pop_front)(struct LinkedList *list);

    Node* (*get_node)(struct LinkedList* list, uint32_t position);
    void* (*get_data)(struct LinkedList* list, uint32_t position);
    void (*clear)(struct LinkedList *list);
} LinkedList;

LinkedList *init_list(void);

#endif // __LINKEDLISTS_H__