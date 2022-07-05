//
// Created by Wolfgang Aigner on 26.10.2021.
//

#include <linked_lists.h>
#include <stdlib.h>
#include <string.h>

inline static void assign_error_code(LINKED_LIST_ERROR_CODE *error_code,
                                     LINKED_LIST_ERROR_CODE value)
{
    if(error_code != NULL) *error_code = value;
}

static Node *init_node(const void *data, uint32_t size, LINKED_LIST_ERROR_CODE *error_code)
{
    Node *node = malloc(sizeof(Node));
    if(node == NULL) {
        assign_error_code(error_code, LINKED_LIST_MEMORY_ALLOCATION_ERROR);
        return NULL;
    }
    node->data = malloc(size);
    if(node->data == NULL) {
        assign_error_code(error_code, LINKED_LIST_MEMORY_ALLOCATION_ERROR);
        return NULL;
    }
    memcpy(node->data, data, size);
    node->next = NULL;
    node->previous = NULL;
    assign_error_code(error_code, LINKED_LIST_OK);
    return node;
}

static Node *get_node(LinkedList *list, uint32_t position, LINKED_LIST_ERROR_CODE *error_code)
{
    if(!list->is_initialized) {
        assign_error_code(error_code, LINKED_LIST_NOT_INITIALIZED);
        return NULL;
    }
    Node *temp = NULL;
    if(position >= list->length || list->length == 0) {
        assign_error_code(error_code, LINKED_LIST_INDEX_OUT_OF_BOUNDS);
        return NULL;
    }
    if(position >= (int) (list->length / 2)) {
        temp = list->tail;
        uint32_t i = list->length - 1;
        while(i != position) {
            temp = temp->previous;
            i--;
        }
    } else {
        temp = list->head;
        uint32_t i = 0;
        while(i != position) {
            temp = temp->next;
            i++;
        }
    }
    assign_error_code(error_code, LINKED_LIST_OK);
    return temp;
}

static void *get_data(LinkedList *list, uint32_t position, LINKED_LIST_ERROR_CODE *error_code)
{
    if(!list->is_initialized) {
        assign_error_code(error_code, LINKED_LIST_NOT_INITIALIZED);
        return NULL;
    }
    return get_node(list, position, error_code)->data;
}

static void clear(LinkedList *list, LINKED_LIST_ERROR_CODE *error_code)
{
    if(!list->is_initialized) {
        assign_error_code(error_code, LINKED_LIST_NOT_INITIALIZED);
        return;
    }
    for(uint32_t i = 0; i < list->length; i++) {
        Node* node = list->get_node(list, i, error_code);
        if(node == NULL) {
            assign_error_code(error_code, LINKED_LIST_ELEMENT_NULL);
            return;
        }
        if(error_code != LINKED_LIST_OK)
            return;
        free(node->data);
        free(node);
    }
    list->length = 0;
    list->head = NULL;
    list->tail = NULL;
    assign_error_code(error_code, LINKED_LIST_OK);
}

static void push_back(LinkedList *list, void *data, uint32_t size, LINKED_LIST_ERROR_CODE *error_code)
{
    if(!list->is_initialized) {
        assign_error_code(error_code, LINKED_LIST_NOT_INITIALIZED);
        return;
    }
    Node *new_node = init_node(data, size, error_code);
    if(error_code != LINKED_LIST_OK) return;
    if(list->length == 0) {
        list->head = new_node;
        list->tail = new_node;
    } else {
        new_node->previous = list->tail;
        list->tail->next = new_node;
        list->tail = new_node;
    }
    list->length++;
    assign_error_code(error_code, LINKED_LIST_OK);
}

static void push_front(LinkedList *list, void *data, uint32_t size, LINKED_LIST_ERROR_CODE *error_code)
{
    if(!list->is_initialized) {
        assign_error_code(error_code, LINKED_LIST_NOT_INITIALIZED);
        return;
    }
    Node *new_node = init_node(data, size, error_code);
    if(error_code != LINKED_LIST_OK) return;
    if(list->length == 0) {
        list->head = new_node;
        list->tail = new_node;
    } else {
        new_node->next = list->head;
        list->head->previous = new_node;
        list->head = new_node;
    }
    list->length++;
    assign_error_code(error_code, LINKED_LIST_OK);
}

static void *pop_back(LinkedList *list, LINKED_LIST_ERROR_CODE *error_code)
{
    if(!list->is_initialized) {
        assign_error_code(error_code, LINKED_LIST_NOT_INITIALIZED);
        return NULL;
    }
    if(list->length == 0) {
        return NULL;
    }
    void *temp = list->tail->data;
    Node *previous = list->tail->previous;
    free(list->tail);
    list->tail = previous;
    list->length--;
    assign_error_code(error_code, LINKED_LIST_OK);
    return temp;
}

static void *pop_front(LinkedList *list, LINKED_LIST_ERROR_CODE *error_code)
{
    if(!list->is_initialized) {
        assign_error_code(error_code, LINKED_LIST_NOT_INITIALIZED);
        return NULL;
    }
    if(list->length == 0) {
        return NULL;
    }
    void *temp = list->head->data;
    Node *next = list->head->next;
    free(list->head);
    list->head = next;
    list->length--;
    assign_error_code(error_code, LINKED_LIST_OK);
    return temp;
}

inline static void assign_methods(LinkedList *list)
{
    list->push_back = push_back;
    list->push_front = push_front;
    list->pop_back = pop_back;
    list->pop_front = pop_front;
    list->get_node = get_node;
    list->get_data = get_data;
    list->clear = clear;
}

LinkedList *init_list_heap(LINKED_LIST_ERROR_CODE *error_code)
{
    LinkedList *list = (LinkedList *) malloc(sizeof(LinkedList));
    if(list == NULL) {
        assign_error_code(error_code, LINKED_LIST_MEMORY_ALLOCATION_ERROR);
        return NULL;
    }
    list->head = NULL;
    list->tail = NULL;
    list->length = 0;
    assign_methods(list);
    list->is_initialized = TRUE;
    assign_error_code(error_code, LINKED_LIST_OK);
    return list;
}

LinkedList init_list_stack(LINKED_LIST_ERROR_CODE *error_code)
{
    LinkedList list;
    list.head = NULL;
    list.tail = NULL;
    list.length = 0;
    assign_methods(&list);
    list.is_initialized = TRUE;
    assign_error_code(error_code, LINKED_LIST_OK);
    return list;
}