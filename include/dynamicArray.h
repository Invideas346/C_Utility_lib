//
// Created by Wolfgang Aigner on 26.10.2021.
//

#ifndef _DYNAMICARRAY_H
#define _DYNAMICARRAY_H

#include <stdlib.h>
#include <typedef.h>

typedef struct dynamicArray dynamicArray;

struct dynamicArray
{
    void* data;
    ui32 objectSize;
    ui32 size;

    boolean initalized;

    /**
     * @brief Adds an item to the back of the array.
     * @param array
     * @param data
     * @return Returns the pointer to the added item. Null if not successfully.
     */
    void* (*push_back)(dynamicArray* array, const void* data);
    /**
     * @brief Adds an item to the front of the array.
     * @param array
     * @param data
     * @return Returns the pointer to the added item. Null if not successfully.
     */
    void* (*push_front)(dynamicArray* array, const void* data);

    /**
     * @brief Removes the last item of the array.
     * @param array
     * @return Returns a pointer to a heap allocated object containing the value of removes item.
     */
    void* (*pop_back)(dynamicArray* array);
    /**
     * @brief Removes the first item of the array.
     * @param array
     * @return Returns a pointer to a heap allocated object containing the value of removes item.
     */
    void* (*pop_front)(dynamicArray* array);

    /**
     * @brief Returns the pointer to the specified element within the array.
     * @note The pointer points directly to the element in the array.
     * @param array
     * @param position
     * @return Returns the pointer to the specified element within the array.
     */
    void* (*at)(dynamicArray* array, ui32 position);

    /**
     * @brief Resizes the array with the specified number of elements.
     * @param array
     * @param numElements
     * @return Returns whether the operation was successful.
     */
    boolean (*resize)(dynamicArray* array, ui32 numElements);
};

dynamicArray* init_dynamicArray(ui32 size, ui32 objectSize);
dynamicArray* init_dynamicArray_data(ui32 size, const void* data, ui32 objectSize);

#endif  // _DYNAMICARRAY_H