#include <linkedLists.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define ASSERT_INIT(x) assert(x->isInitalised)

static Node *init_node(const void *data, ui32 size)
{
    Node *node = malloc(sizeof(Node));
    node->data = malloc(size);
    memcpy(node->data, data, size);
    node->next = NULL;
    node->previous = NULL;
    return node;
}

//! not tested yet
static Node *get_node(LinkedList *list, ui32 position)
{
    ASSERT_INIT(list);
    Node *temp = NULL;
    if(position >= list->size || list->size == 0)
    {
        return NULL;
    }
    if(position >= (int) (list->size / 2))
    {
        temp = list->tail;
        ui32 i = list->size - 1;
        while(i != position)
        {
            temp = temp->previous;
            i--;
        }
    }
    else
    {
        temp = list->head;
        ui32 i = 0;
        while(i != position)
        {
            temp = temp->next;
            i++;
        }
    }
    return temp;
}

//! not tested yet
static void *get_data(LinkedList *list, ui32 position)
{
    ASSERT_INIT(list);
    return get_node(list, position)->data;
}

//! not tested yet
static void clear(LinkedList *list)
{
    ASSERT_INIT(list);
    for(ui32 i = 0; i < list->size; i++)
    {
        free(list->get_node(list, i)->data);
        free(list->get_node(list, i));
    }
    list->size = 0;
    list->head = NULL;
    list->tail = NULL;
}

//! not tested yet
static void push_back(LinkedList *list, void *data, ui32 size)
{
    ASSERT_INIT(list);
    Node *new_node = init_node(data, size);
    if(list->size == 0)
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

//! not tested yet
static void push_front(LinkedList *list, void *data, ui32 size)
{
    ASSERT_INIT(list);
    Node *new_node = init_node(data, size);
    if(list->size == 0)
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

//! not tested yet
static void *pop_back(LinkedList *list)
{
    ASSERT_INIT(list);
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

//! not tested yet
static void *pop_front(LinkedList *list)
{
    ASSERT_INIT(list);
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

static void assignMethods(LinkedList *list)
{
    list->push_back = push_back;
    list->push_front = push_front;
    list->pop_back = pop_back;
    list->pop_front = pop_front;
    list->get_node = get_node;
    list->get_data = get_data;
    list->clear = clear;
}

LinkedList *init_list(void)
{
    LinkedList *list = (LinkedList *) malloc(sizeof(LinkedList));
    if(list == NULL)
    {
        return NULL;
    }
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    assignMethods(list);
    list->isInitalised = true;
    return list;
}