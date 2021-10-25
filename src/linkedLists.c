#include "linkedLists.h"

static Node *init_node(const void *data, uint32_t size)
{
    Node *node = malloc(sizeof(Node));
    node->data = malloc(size);
    memcpy(node->data, data, size);
    node->next = NULL;
    node->previous = NULL;
    return node;
}

static Node *get_node(LinkedList *list, uint32_t position)
{
    Node *temp = NULL;
    if (position >= list->size || list->size == 0)
    {
        return NULL;
    }

    if (position >= (int)(list->size / 2))
    {
        temp = list->tail;
        uint32_t i = list->size - 1;
        while (i != position)
        {
            temp = temp->previous;
            i--;
        }
    }
    else
    {
        temp = list->head;
        uint32_t i = 0;
        while (i != position)
        {
            temp = temp->next;
            i++;
        }
    }
    return temp;
}

static void *get_data(LinkedList *list, uint32_t position)
{
    return get_node(list, position)->data;
}

static void clear(LinkedList *list)
{
    for (uint32_t i = 0; i < list->size; i++)
    {
        free(list->get_node(list, i)->data);
        free(list->get_node(list, i));
    }
    list->size = 0;
    list->head = NULL;
    list->tail = NULL;
}

static void push_back(LinkedList *list, void* data, uint32_t size)
{
    Node *new_node = init_node(data, size);
    if (list->size == 0)
    {
        list->head = new_node;
        list->tail = new_node;
    }
    else
    {
        new_node->previous = list->tail;
        list->tail->next = new_node;
        list->tail = new_node;
    }
    list->size++;  
}

static void push_front(LinkedList *list, void* data, uint32_t size)
{
    Node *new_node = init_node(data, size);
    if (list->size == 0)
    {
        list->head = new_node;
        list->tail = new_node;
    }
    else
    {
        new_node->next = list->head;
        list->head->previous = new_node;
        list->head = new_node;
    }
    list->size++;    
}

static void* pop_back(LinkedList *list)
{
    if(list->size == 0)
    {
        return NULL;
    }
    void *temp = list->tail->data;
    Node *previous = list->tail->previous;
    free(list->tail);
    list->tail = previous;
    list->size--;
    return temp;
}

static void* pop_front(LinkedList *list)
{
    if(list->size == 0)
    {
        return NULL;
    }
    void *temp = list->head->data;
    Node *next = list->head->next;
    free(list->head);
    list->head = next;
    list->size--;
    return temp;
}

LinkedList *init_list(void)
{
    LinkedList *list = malloc(sizeof(LinkedList));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;

    list->push_back = push_back;
    list->push_front = push_front;
    list->pop_back = pop_back;
    list->pop_front = pop_front;

    list->get_node = get_node;
    list->get_data = get_data;
    list->clear = clear;
    return list;
}