//
// Created by Wolfgang Aigner on 26.10.2021.
//

#ifndef __Vector_H__
#define __Vector_H__

#include <stdlib.h>
#include <typedef.h>

// TODO: Maybe implement a foreach methode into which a function gets passed like void (*)(void*data, ui32 index)
// TODO: Maybe implement a toString function (not sure it is really ever gonna be needed)
// TODO: Implement a remove via index function.

typedef struct Vector Vector;

struct Vector
{
    void* data;
    ui32 objectSize;
    ui32 length;

    boolean isInitalised;

    /**
     * @brief Removes all indecies and frees the occupied heap memory.
     *
     */
    void (*clear)(Vector* array);
    /**
     * @brief Adds an item to the back of the array.
     * @param array
     * @param data
     * @return Returns the pointer to the added item.
     * Returns NULL if a error occured.
     */
    void* (*push_back)(Vector* array, const void* data);
    /**
     * @brief Adds an item to the front of the array.
     * @param array
     * @param data
     * @return Returns the pointer to the added item.
     * Returns NULL if a error occured.
     */
    void* (*push_front)(Vector* array, const void* data);

    /**
     * @brief Removes the last item of the array.
     * @param array
     * @return Returns a pointer to a heap allocated object containing the value of removes item.
     * Returns NULL if a error occured.
     */
    boolean (*pop_back)(Vector* array);
    /**
     * @brief Removes the first item of the array.
     * @param array
     * @return Returns a pointer to a heap allocated object containing the value of removes item.
     * Returns NULL if a error occured.
     */
    boolean (*pop_front)(Vector* array);

    /**
     * @brief Returns the pointer to the specified element within the array.
     * @note The pointer points directly to the element in the array.
     * @param array
     * @param position
     * @return Returns the pointer to the specified element within the array.
     * Returns NULL if a error occured.
     */
    void* (*at)(Vector* array, ui32 position);

    /**
     * @brief Resizes the array with the specified number of elements.
     * @param array
     * @param numElements
     * @return Returns whether the operation was successful. Returns NULL if a error occured.
     */
    boolean (*resize)(Vector* array, ui32 numElements);

    /**
     * @brief Returns a copy of itself.
     */
    Vector* (*copy_heap)(Vector* array);
    /**
     * @brief Returns a copy of itself.
     */
    Vector (*copy_stack)(Vector* array);
};

/**
 * @brief Creates a new dynamic array initalized with all function pointers.
 * @return Vector*
 */
Vector* init_vector_heap(ui32 size, ui32 objectSize);
/**
 * @brief Creates a new dynamic array initalized with all function pointers.
 * @return Vector*
 */
Vector* init_vector_heap_data(ui32 size, const void* data, ui32 objectSize);

/**
 * @brief Creates a new dynamic array initalized with all function pointers.
 * @return Vector*
 */
Vector init_vector_stack(ui32 size, ui32 objectSize);
/**
 * @brief Creates a new dynamic array initalized with all function pointers.
 * @return Vector*
 */
Vector init_vector_stack_data(ui32 size, const void* data, ui32 objectSize);

#endif  // __Vector_H__