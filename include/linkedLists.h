#ifndef __LINKEDLISTS_H__
#define __LINKEDLISTS_H__

#include <typedef.h>

typedef struct Node Node;

struct Node
{
    Node* previous;
    void* data;
    Node* next;
};

typedef struct LinkedList LinkedList;

struct LinkedList
{
    Node* head;
    Node* tail;
    ui32 size;

    boolean initalized;

    /**
     * @brief Adds a new element at the end of the array.
     * @param list
     * @param data
     * @param size
     */
    void (*push_back)(LinkedList* list, void* data, ui32 size);

    /**
     * @brief Adds a new element at the beginning of the array.
     * @param list
     * @param data
     * @param size
     */
    void (*push_front)(LinkedList* list, void* data, ui32 size);

    /**
     * @brief Removes a element from the end of the array.
     * @param list
     * @return A pointer to a newly created pointer with the removes value. Null if unsuccessful.
     */
    void* (*pop_back)(LinkedList* list);
    /**
     * @brief Removes a element from the beginning of the array.
     * @param list
     * @return A pointer to a newly created pointer with the removes value. Null if unsuccessful.
     */
    void* (*pop_front)(LinkedList* list);

    /**
     * @brief Gets the entire node from a specific position.
     * @param list
     * @param position
     * @return The corresponding node. Null if the position is invalid.
     */
    Node* (*get_node)(LinkedList* list, ui32 position);

    /**
     * @brief Creates a new pointer with the value at the position in the linked list.
     * @param list
     * @param position
     * @return The value stored at the specified position in the linked list.
     */
    void* (*get_data)(LinkedList* list, ui32 position);

    /**
     * @brief Deallocates the memory.
     * @param list
     */
    void (*clear)(LinkedList* list);
};

LinkedList* init_list(void);

#endif  // __LINKEDLISTS_H__