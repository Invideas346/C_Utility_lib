#ifndef __LINKEDLISTS_H__
#define __LINKEDLISTS_H__

#include <typedef.h>

typedef struct Node
{
    struct Node* previous;
    void* data;
    struct Node* next;
} Node;

typedef struct LinkedList
{
    Node* head;
    Node* tail;
    ui32 size;

    boolean initalized;

    void (*push_back)(struct LinkedList* list, void* data, ui32 size);
    void (*push_front)(struct LinkedList* list, void* data, ui32 size);
    void* (*pop_back)(struct LinkedList* list);
    void* (*pop_front)(struct LinkedList* list);

    Node* (*get_node)(struct LinkedList* list, ui32 position);
    void* (*get_data)(struct LinkedList* list, ui32 position);
    void (*clear)(struct LinkedList* list);
} LinkedList;

LinkedList* init_list(void);

#endif  // __LINKEDLISTS_H__