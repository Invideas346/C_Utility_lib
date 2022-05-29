//
// Created by Wolfgang Aigner on 26.10.2021.
//

#include <vector.h>
#include <string.h>

#define ARRAY_INDEX(index) ((index) * (array->object_size))

inline static void assign_error_code(VECTOR_ERROR_CODE* code, VECTOR_ERROR_CODE value)
{
    if(code != NULL) *code = value;
}

static void* push_back(Vector* array, const void* data, VECTOR_ERROR_CODE* code)
{
    if(!array->is_initialized)
    {
        assign_error_code(code, VECTOR_NOT_INITIALIZED);
        return NULL;
    }
    if(array->object_size == 0)
    {
        return NULL;
    }
    array->length += 1;
    void* newAddress = realloc(array->data, array->length * array->object_size);
    if(newAddress == NULL)
    {
        assign_error_code(code, MEMORY_ALLOCATION_ERROR);
        return NULL;
    }
    memcpy(array->data + ARRAY_INDEX(array->length - 1), data, array->object_size);
    assign_error_code(code, OK);
    return array->data + ARRAY_INDEX(array->length - 1);
}

static void* push_front(Vector* array, const void* data, VECTOR_ERROR_CODE* code)
{
    if(!array->is_initialized)
    {
        assign_error_code(code, VECTOR_NOT_INITIALIZED);
        return NULL;
    }
    if(array->object_size == 0)
    {
        return NULL;
    }
    array->length += 1;
    void* newAddress = realloc(array->data, array->length * array->object_size);
    if(newAddress == NULL)
    {
        assign_error_code(code, MEMORY_ALLOCATION_ERROR);
        return NULL;
    }
    if(array->length != 1)
    {
        memcpy(array->data + ARRAY_INDEX(1), array->data + ARRAY_INDEX(0),
               array->object_size * (array->length - 1));
    }
    memcpy(array->data + ARRAY_INDEX(0), data, array->object_size);
    assign_error_code(code, OK);
    return array->data + ARRAY_INDEX(0);
}

static boolean pop_back(Vector* array, VECTOR_ERROR_CODE* code)
{
    if(!array->is_initialized)
    {
        assign_error_code(code, VECTOR_NOT_INITIALIZED);
        return FALSE;
    }
    if(array->length == 0 || array->object_size <= 0)
    {
        return FALSE;
    }
    array->length -= 1;
    void* newAddress = realloc(array->data, array->length * array->object_size);
    if(newAddress == NULL)
    {
        assign_error_code(code, MEMORY_ALLOCATION_ERROR);
        return FALSE;
    }
    assign_error_code(code, OK);
    return TRUE;
}

static boolean pop_front(Vector* array, VECTOR_ERROR_CODE* code)
{
    if(!array->is_initialized)
    {
        assign_error_code(code, VECTOR_NOT_INITIALIZED);
        return FALSE;
    }
    if(array->length == 0 || array->object_size <= 0)
    {
        return FALSE;
    }
    array->length -= 1;
    void* temp = malloc(array->object_size * array->length);
    if(temp == NULL)
    {
        assign_error_code(code, MEMORY_ALLOCATION_ERROR);
        return FALSE;
    }
    memcpy(temp, array->data + ARRAY_INDEX(1), array->length * array->object_size);
    void* newAddress = realloc(array->data, array->length * array->object_size);
    if(newAddress == NULL)
    {
        assign_error_code(code, MEMORY_ALLOCATION_ERROR);
        free(temp);
        return FALSE;
    }
    memcpy(array->data, temp, array->length * array->object_size);
    free(temp);
    assign_error_code(code, OK);
    return TRUE;
}

static void* at(Vector* array, ui32 position, VECTOR_ERROR_CODE* code)
{
    if(!array->is_initialized)
    {
        assign_error_code(code, VECTOR_NOT_INITIALIZED);
        return NULL;
    }
    if(array->length == 0 || array->object_size <= 0)
    {
        return NULL;
    }
    assign_error_code(code, OK);
    return array->data + ARRAY_INDEX(position);
}

boolean resize(Vector* array, ui32 numElements, VECTOR_ERROR_CODE* code)
{
    if(!array->is_initialized)
    {
        assign_error_code(code, VECTOR_NOT_INITIALIZED);
        return FALSE;
    }
    if(array->object_size <= 0 || numElements < 0)
    {
        return FALSE;
    }
    void* newAddress = realloc(array->data, array->object_size * numElements);
    if(newAddress == NULL)
    {
        assign_error_code(code, MEMORY_ALLOCATION_ERROR);
        return FALSE;
    }
    array->length = numElements;
    assign_error_code(code, OK);
    return TRUE;
}

static Vector* copy_heap(Vector* array, VECTOR_ERROR_CODE* code)
{
    if(!array->is_initialized)
    {
        assign_error_code(code, VECTOR_NOT_INITIALIZED);
        return NULL;
    }
    Vector* copy = init_vector_heap_data(array->length, array->data, array->object_size, code);
    assign_error_code(code, OK);
    return copy;
}

static Vector copy_stack(Vector* array, VECTOR_ERROR_CODE* code)
{
    if(!array->is_initialized)
    {
        assign_error_code(code, VECTOR_NOT_INITIALIZED);
        return *array;
    }
    Vector copy = init_vector_stack_data(array->length, array->data, array->object_size, code);
    assign_error_code(code, OK);
    return copy;
}

static void clear(Vector* array, VECTOR_ERROR_CODE* code)
{
    if(!array->is_initialized)
    {
        assign_error_code(code, VECTOR_NOT_INITIALIZED);
        return;
    }
    free(array->data);
    array->data = NULL;
    array->length = 0;
    assign_error_code(code, OK);
}

static void for_each(Vector* array, void (*func)(void* data, ui32 index, ui32 object_size),
                     VECTOR_ERROR_CODE* code)
{
    if(!array->is_initialized)
    {
        assign_error_code(code, VECTOR_NOT_INITIALIZED);
        return;
    }
    for(ui32 i = 0; i < array->length; ++i)
    {
        func(array->at(array, i, code), i, array->object_size);
        if(code != NULL)
            if(*code != OK) break;
    }
}

static void assign_methods(Vector* array)
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

Vector* init_vector_heap(ui32 size, ui32 objectSize, VECTOR_ERROR_CODE* code)
{
    Vector* array = (Vector*) malloc(sizeof(Vector));
    if(array == NULL)
    {
        assign_error_code(code, MEMORY_ALLOCATION_ERROR);
        return NULL;
    }
    array->length = size;
    array->object_size = objectSize;
    array->data = malloc(size * objectSize);
    if(array->data == NULL)
    {
        assign_error_code(code, MEMORY_ALLOCATION_ERROR);
        return array;
    }
    assign_methods(array);
    array->is_initialized = TRUE;
    assign_error_code(code, OK);
    return array;
}

Vector* init_vector_heap_data(ui32 size, const void* data, ui32 objectSize, VECTOR_ERROR_CODE* code)
{
    Vector* array = (Vector*) malloc(sizeof(Vector));
    if(array == NULL)
    {
        assign_error_code(code, MEMORY_ALLOCATION_ERROR);
        return NULL;
    }
    array->length = size;
    array->object_size = objectSize;
    array->data = malloc(size * objectSize);
    if(array->data == NULL)
    {
        assign_error_code(code, MEMORY_ALLOCATION_ERROR);
        return array;
    }
    memcpy(array->data, data, size * objectSize);
    assign_methods(array);
    array->is_initialized = TRUE;
    assign_error_code(code, OK);
    return array;
}

Vector init_vector_stack(ui32 size, ui32 objectSize, VECTOR_ERROR_CODE* code)
{
    Vector array;
    array.length = size;
    array.object_size = objectSize;
    array.data = malloc(size * objectSize);
    if(array.data == NULL)
    {
        assign_error_code(code, MEMORY_ALLOCATION_ERROR);
        return array;
    }
    assign_methods(&array);
    array.is_initialized = TRUE;
    assign_error_code(code, OK);
    return array;
}

Vector init_vector_stack_data(ui32 size, const void* data, ui32 objectSize, VECTOR_ERROR_CODE* code)
{
    Vector array;
    array.length = size;
    array.object_size = objectSize;
    array.data = malloc(size * objectSize);
    if(array.data == NULL)
    {
        assign_error_code(code, MEMORY_ALLOCATION_ERROR);
        return array;
    }
    memcpy(array.data, data, size * objectSize);
    assign_methods(&array);
    array.is_initialized = TRUE;
    assign_error_code(code, OK);
    return array;
}