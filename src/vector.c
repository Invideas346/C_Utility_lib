//
// Created by Wolfgang Aigner on 26.10.2021.
//

#include <vector.h>
#include <string.h>

#define ARRAY_INDEX(index) ((index) * (array->object_size))

inline static void assign_error_code(VECTOR_ERROR_CODE* error_code, VECTOR_ERROR_CODE value)
{
    if(error_code != NULL) *error_code = value;
}

static void* push_back(Vector* array, const void* data, VECTOR_ERROR_CODE* error_code)
{
    if(!array->is_initialized) {
        assign_error_code(error_code, VECTOR_NOT_INITIALIZED);
        return NULL;
    }
    if(array->object_size == 0) {
        return NULL;
    }
    array->length += 1;
    void* newAddress = realloc(array->data, array->length * array->object_size);
    if(newAddress == NULL) {
        assign_error_code(error_code, VECTOR_MEMORY_ALLOCATION_ERROR);
        return NULL;
    }
    memcpy(array->data + ARRAY_INDEX(array->length - 1), data, array->object_size);
    assign_error_code(error_code, VECTOR_OK);
    return array->data + ARRAY_INDEX(array->length - 1);
}

static void* push_front(Vector* array, const void* data, VECTOR_ERROR_CODE* error_code)
{
    if(!array->is_initialized) {
        assign_error_code(error_code, VECTOR_NOT_INITIALIZED);
        return NULL;
    }
    if(array->object_size == 0) {
        return NULL;
    }
    array->length += 1;
    void* newAddress = realloc(array->data, array->length * array->object_size);
    if(newAddress == NULL) {
        assign_error_code(error_code, VECTOR_MEMORY_ALLOCATION_ERROR);
        return NULL;
    }
    if(array->length != 1) {
        memcpy(array->data + ARRAY_INDEX(1), array->data + ARRAY_INDEX(0),
               array->object_size * (array->length - 1));
    }
    memcpy(array->data + ARRAY_INDEX(0), data, array->object_size);
    assign_error_code(error_code, VECTOR_OK);
    return array->data + ARRAY_INDEX(0);
}

static uint8_t pop_back(Vector* array, VECTOR_ERROR_CODE* error_code)
{
    if(!array->is_initialized) {
        assign_error_code(error_code, VECTOR_NOT_INITIALIZED);
        return FALSE;
    }
    if(array->length == 0 || array->object_size <= 0) {
        return FALSE;
    }
    array->length -= 1;
    void* newAddress = realloc(array->data, array->length * array->object_size);
    if(newAddress == NULL) {
        assign_error_code(error_code, VECTOR_MEMORY_ALLOCATION_ERROR);
        return FALSE;
    }
    assign_error_code(error_code, VECTOR_OK);
    return TRUE;
}

static uint8_t pop_front(Vector* array, VECTOR_ERROR_CODE* error_code)
{
    if(!array->is_initialized) {
        assign_error_code(error_code, VECTOR_NOT_INITIALIZED);
        return FALSE;
    }
    if(array->length == 0 || array->object_size <= 0) {
        return FALSE;
    }
    array->length -= 1;
    void* temp = malloc(array->object_size * array->length);
    if(temp == NULL) {
        assign_error_code(error_code, VECTOR_MEMORY_ALLOCATION_ERROR);
        return FALSE;
    }
    memcpy(temp, array->data + ARRAY_INDEX(1), array->length * array->object_size);
    void* newAddress = realloc(array->data, array->length * array->object_size);
    if(newAddress == NULL) {
        assign_error_code(error_code, VECTOR_MEMORY_ALLOCATION_ERROR);
        free(temp);
        return FALSE;
    }
    memcpy(array->data, temp, array->length * array->object_size);
    free(temp);
    assign_error_code(error_code, VECTOR_OK);
    return TRUE;
}

static void* at(Vector* array, uint32_t position, VECTOR_ERROR_CODE* error_code)
{
    if(!array->is_initialized) {
        assign_error_code(error_code, VECTOR_NOT_INITIALIZED);
        return NULL;
    }
    if(array->length == 0 || array->object_size <= 0) {
        return NULL;
    }
    assign_error_code(error_code, VECTOR_OK);
    return array->data + ARRAY_INDEX(position);
}

uint8_t resize(Vector* array, uint32_t num_elements, VECTOR_ERROR_CODE* error_code)
{
    if(!array->is_initialized) {
        assign_error_code(error_code, VECTOR_NOT_INITIALIZED);
        return FALSE;
    }
    if(array->object_size <= 0 || num_elements < 0) {
        return FALSE;
    }
    void* newAddress = realloc(array->data, array->object_size * num_elements);
    if(newAddress == NULL) {
        assign_error_code(error_code, VECTOR_MEMORY_ALLOCATION_ERROR);
        return FALSE;
    }
    array->length = num_elements;
    assign_error_code(error_code, VECTOR_OK);
    return TRUE;
}

static Vector* copy_heap(Vector* array, VECTOR_ERROR_CODE* error_code)
{
    if(!array->is_initialized) {
        assign_error_code(error_code, VECTOR_NOT_INITIALIZED);
        return NULL;
    }
    Vector* copy =
        init_vector_heap_data(array->length, array->data, array->object_size, error_code);
    assign_error_code(error_code, VECTOR_OK);
    return copy;
}

static Vector copy_stack(Vector* array, VECTOR_ERROR_CODE* error_code)
{
    if(!array->is_initialized) {
        assign_error_code(error_code, VECTOR_NOT_INITIALIZED);
        return *array;
    }
    Vector copy =
        init_vector_stack_data(array->length, array->data, array->object_size, error_code);
    assign_error_code(error_code, VECTOR_OK);
    return copy;
}

static void clear(Vector* array, VECTOR_ERROR_CODE* error_code)
{
    if(!array->is_initialized) {
        assign_error_code(error_code, VECTOR_NOT_INITIALIZED);
        return;
    }
    free(array->data);
    array->data = NULL;
    array->length = 0;
    assign_error_code(error_code, VECTOR_OK);
}

static void for_each(Vector* array, void (*func)(void* data, uint32_t index, uint32_t object_size),
                     VECTOR_ERROR_CODE* error_code)
{
    if(!array->is_initialized) {
        assign_error_code(error_code, VECTOR_NOT_INITIALIZED);
        return;
    }
    for(uint32_t i = 0; i < array->length; ++i) {
        func(array->at(array, i, error_code), i, array->object_size);
        if(error_code != NULL)
            if(*error_code != VECTOR_OK) break;
    }
}

inline static void assign_methods(Vector* array)
{
    array->push_back = push_back;
    array->push_front = push_front;
    array->pop_back = pop_back;
    array->pop_front = pop_front;
    array->at = at;
    array->resize = resize;
    array->copy_heap = copy_heap;
    array->copy_stack = copy_stack;
    array->clear = clear;
    array->for_each = for_each;
}

Vector* init_vector_heap(uint32_t size, uint32_t object_size, VECTOR_ERROR_CODE* error_code)
{
    Vector* array = (Vector*) malloc(sizeof(Vector));
    if(array == NULL) {
        assign_error_code(error_code, VECTOR_MEMORY_ALLOCATION_ERROR);
        return NULL;
    }
    array->length = size;
    array->object_size = object_size;
    array->data = malloc(size * object_size);
    if(array->data == NULL) {
        assign_error_code(error_code, VECTOR_MEMORY_ALLOCATION_ERROR);
        return array;
    }
    assign_methods(array);
    array->is_initialized = TRUE;
    assign_error_code(error_code, VECTOR_OK);
    return array;
}

Vector* init_vector_heap_data(uint32_t size, const void* data, uint32_t object_size,
                              VECTOR_ERROR_CODE* error_code)
{
    Vector* array = (Vector*) malloc(sizeof(Vector));
    if(array == NULL) {
        assign_error_code(error_code, VECTOR_MEMORY_ALLOCATION_ERROR);
        return NULL;
    }
    array->length = size;
    array->object_size = object_size;
    array->data = malloc(size * object_size);
    if(array->data == NULL) {
        assign_error_code(error_code, VECTOR_MEMORY_ALLOCATION_ERROR);
        return array;
    }
    memcpy(array->data, data, size * object_size);
    assign_methods(array);
    array->is_initialized = TRUE;
    assign_error_code(error_code, VECTOR_OK);
    return array;
}

Vector init_vector_stack(uint32_t size, uint32_t object_size, VECTOR_ERROR_CODE* error_code)
{
    Vector array;
    array.length = size;
    array.object_size = object_size;
    array.data = malloc(size * object_size);
    if(array.data == NULL) {
        assign_error_code(error_code, VECTOR_MEMORY_ALLOCATION_ERROR);
        return array;
    }
    assign_methods(&array);
    array.is_initialized = TRUE;
    assign_error_code(error_code, VECTOR_OK);
    return array;
}

Vector init_vector_stack_data(uint32_t size, const void* data, uint32_t object_size,
                              VECTOR_ERROR_CODE* error_code)
{
    Vector array;
    array.length = size;
    array.object_size = object_size;
    array.data = malloc(size * object_size);
    if(array.data == NULL) {
        assign_error_code(error_code, VECTOR_MEMORY_ALLOCATION_ERROR);
        return array;
    }
    memcpy(array.data, data, size * object_size);
    assign_methods(&array);
    array.is_initialized = TRUE;
    assign_error_code(error_code, VECTOR_OK);
    return array;
}