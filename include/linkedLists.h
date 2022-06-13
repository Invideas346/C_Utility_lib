#ifndef __LINKEDLISTS_H__
#define __LINKEDLISTS_H__

#include <typedef.h>

typedef struct Node Node;

struct Node {
    Node* previous;
    void* data;
    Node* next;
};

typedef enum LINKED_LIST_ERROR_CODE {
    LINKED_LIST_OK = 0,
    LINKED_LIST_GENERAL_ERROR = 1,
    LINKED_LIST_NOT_INITIALIZED = 2 | LINKED_LIST_GENERAL_ERROR,
    LINKED_LIST_MEMORY_ALLOCATION_ERROR = 3 | LINKED_LIST_GENERAL_ERROR,
    LINKED_LIST_ELEMENT_NULL = 4 | LINKED_LIST_GENERAL_ERROR,
    LINKED_LIST_INDEX_OUT_OF_BOUNDS = 5 | LINKED_LIST_GENERAL_ERROR,
} LINKED_LIST_ERROR_CODE;

typedef struct LinkedList LinkedList;

struct LinkedList {
    Node* head;
    Node* tail;
    ui32 length;

    boolean is_initialized;

    /**
     * @brief Adds a new element at the end of the array.
     * @param list
     * @param data
     * @param size
     */
    void (*push_back)(LinkedList* list, void* data, ui32 size, LINKED_LIST_ERROR_CODE* error_code);

    /**
     * @brief Adds a new element at the beginning of the array.
     * @param list
     * @param data
     * @param size
     */
    void (*push_front)(LinkedList* list, void* data, ui32 size, LINKED_LIST_ERROR_CODE* error_code);

    /**
     * @brief Removes a element from the end of the array.
     * @param list
     * @return A pointer to a newly created pointer with the removes value. Null if unsuccessful.
     * Free has to be called on the returend pointer.
     */
    void* (*pop_back)(LinkedList* list, LINKED_LIST_ERROR_CODE* error_code);
    /**
     * @brief Removes a element from the beginning of the array.
     * @param list
     * @return A pointer to a newly created pointer with the removes value. Null if unsuccessful.
     * Free has to be called on the returend pointer.
     */
    void* (*pop_front)(LinkedList* list, LINKED_LIST_ERROR_CODE* error_code);

    /**
     * @brief Gets the entire node from a specific position.
     * @param list
     * @param position
     * @return The corresponding node. Null if the position is invalid.
     */
    Node* (*get_node)(LinkedList* list, ui32 position, LINKED_LIST_ERROR_CODE* error_code);

    /**
     * @brief Creates a new pointer with the value at the position in the linked list.
     * @param list
     * @param position
     * @return The value stored at the specified position in the linked list.
     */
    void* (*get_data)(LinkedList* list, ui32 position, LINKED_LIST_ERROR_CODE* error_code);

    /**
     * @brief Deallocates the memory.
     * @param list
     */
    void (*clear)(LinkedList* list, LINKED_LIST_ERROR_CODE* error_code);
};

LinkedList init_list_stack(LINKED_LIST_ERROR_CODE* error_code);
LinkedList* init_list_heap(LINKED_LIST_ERROR_CODE* error_code);

#endif  // __LINKEDLISTS_H__