//
// Created by Wolfgang Aigner on 26.10.2021.
//

#ifndef __Vector_H__
#define __Vector_H__

#include <stdlib.h>
#include <typedef.h>

// TODO: Maybe implement a toString function (not sure it is really ever gonna be needed)
// TODO: Implement a remove via index function.

typedef enum VECTOR_ERROR_CODE {
    OK = 0,
    GENERAL_ERROR = 1,
    VECTOR_NOT_INITIALIZED = 2 | GENERAL_ERROR,
    MEMORY_ALLOCATION_ERROR = 3 | GENERAL_ERROR
} VECTOR_ERROR_CODE;

typedef struct Vector Vector;

struct Vector {
    void* data;
    ui32 object_size;
    ui32 length;

    boolean is_initialized;

    /**
     * @brief Removes all indices and frees the occupied heap memory.
     * @param array
     * @param error_code
     */
    void (*clear)(Vector* array, VECTOR_ERROR_CODE* error_code);

    /**
     * @brief Adds an item to the back of the array.
     * @param array
     * @param data
     * @param error_code
     * @return Returns the pointer to the added item.
     * Returns NULL if a error occurred.
     */
    void* (*push_back)(Vector* array, const void* data, VECTOR_ERROR_CODE* error_code);

    /**
     * @brief Adds an item to the front of the array.
     * @param array
     * @param data
     * @param error_code
     * @return Returns the pointer to the added item.
     * Returns NULL if a error occurred.
     */
    void* (*push_front)(Vector* array, const void* data, VECTOR_ERROR_CODE* error_code);

    /**
     * @brief Removes the last item of the array.
     * @param array
     * @param error_code
     * @return Returns whether the operation was successful.
     */
    boolean (*pop_back)(Vector* array, VECTOR_ERROR_CODE* error_code);

    /**
     * @brief Removes the first item of the array.
     * @param array
     * @param error_code
     * @return Returns whether the operation was successful.
     */
    boolean (*pop_front)(Vector* array, VECTOR_ERROR_CODE* error_code);

    /**
     * @brief Returns the pointer to the specified element within the array.
     * @note The pointer returned points directly to the element in the array.
     * @param array
     * @param position
     * @param error_code
     * @return Returns the pointer to the specified element within the array.
     * Returns NULL if a error occurred.
     */
    void* (*at)(Vector* array, ui32 position, VECTOR_ERROR_CODE* error_code);

    /**
     * @brief Resizes the array with the specified number of elements.
     * @param array
     * @param numElements
     * @param error_code
     * @return Returns whether the operation was successful.
     */
    boolean (*resize)(Vector* array, ui32 numElements, VECTOR_ERROR_CODE* error_code);

    /**
     * @brief Returns a copy of itself.
     * @param array
     * @param error_code
     */
    Vector* (*copy_heap)(Vector* array, VECTOR_ERROR_CODE* error_code);

    /**
     * @brief Returns a copy of itself.
     * @param array
     * @param rror_code
     */
    Vector (*copy_stack)(Vector* array, VECTOR_ERROR_CODE* error_code);

    /**
     * @brief Simple implementation of a higher order function.
     * @param array
     * @param func
     * @param code
     * @param error_code
     */
    void (*for_each)(Vector* array, void (*func)(void* data, ui32 index, ui32 objectSize),
                     VECTOR_ERROR_CODE* error_code);
};

/**
 * @brief Creates a new dynamic array initialized with all function pointers.
 * @return Vector*
 */
Vector* init_vector_heap(ui32 size, ui32 object_size, VECTOR_ERROR_CODE* error_code);
/**
 * @brief Creates a new dynamic array initialized with all function pointers.
 * @return Vector*
 */
Vector* init_vector_heap_data(ui32 size, const void* data, ui32 object_size,
                              VECTOR_ERROR_CODE* error_code);

/**
 * @brief Creates a new dynamic array initialized with all function pointers.
 * @return Vector*
 */
Vector init_vector_stack(ui32 size, ui32 object_size, VECTOR_ERROR_CODE* error_code);
/**
 * @brief Creates a new dynamic array initialized with all function pointers.
 * @return Vector*
 */
Vector init_vector_stack_data(ui32 size, const void* data, ui32 object_size,
                              VECTOR_ERROR_CODE* error_code);

#endif  // __Vector_H__