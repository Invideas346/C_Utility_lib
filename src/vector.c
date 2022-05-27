//
// Created by Wolfgang Aigner on 26.10.2021.
//

#include <vector.h>
#include <string.h>
#include <assert.h>

#define ARRAY_INDEX(index) ((index) * (array->object_size))
#define ASSERT_INIT(x) assert(x->is_initialized)

static void* push_back(Vector* array, const void* data)
{
    ASSERT_INIT(array);
    if(array->object_size == 0)
    {
        return NULL;
    }
    array->length += 1;
    void* newAddress = realloc(array->data, array->length * array->object_size);
    if(newAddress == NULL)
    {
        return NULL;
    }
    memcpy(array->data + ARRAY_INDEX(array->length - 1), data, array->object_size);
    return array->data + ARRAY_INDEX(array->length - 1);
}

static void* push_front(Vector* array, const void* data)
{
    ASSERT_INIT(array);
    if(array->object_size == 0)
    {
        return NULL;
    }
    array->length += 1;
    void* newAddress = realloc(array->data, array->length * array->object_size);
    if(newAddress == NULL)
    {
        return NULL;
    }
    if(array->length != 1)
    {
        memcpy(array->data + ARRAY_INDEX(1), array->data + ARRAY_INDEX(0),
               array->object_size * (array->length - 1));
    }
    memcpy(array->data + ARRAY_INDEX(0), data, array->object_size);
    return array->data + ARRAY_INDEX(0);
}

static boolean pop_back(Vector* array)
{
    ASSERT_INIT(array);
    if(array->length == 0 || array->object_size <= 0)
    {
        return FALSE;
    }
    array->length -= 1;
    void* newAddress = realloc(array->data, array->length * array->object_size);
    if(newAddress == NULL)
    {
        return FALSE;
    }
    return TRUE;
}

static boolean pop_front(Vector* array)
{
    ASSERT_INIT(array);
    if(array->length == 0 || array->object_size <= 0)
    {
        return FALSE;
    }
    array->length -= 1;
    void* temp = malloc(array->object_size * array->length);
    if(temp == NULL)
    {
        return FALSE;
    }
    memcpy(temp, array->data + ARRAY_INDEX(1), array->length * array->object_size);
    void* newAddress = realloc(array->data, array->length * array->object_size);
    if(newAddress == NULL)
    {
        free(temp);
        return FALSE;
    }
    memcpy(array->data, temp, array->length * array->object_size);
    free(temp);
    return TRUE;
}

static void* at(Vector* array, ui32 position)
{
    ASSERT_INIT(array);
    if(array->length == 0 || array->object_size <= 0)
    {
        return NULL;
    }
    return array->data + ARRAY_INDEX(position);
}

boolean resize(Vector* array, ui32 numElements)
{
    ASSERT_INIT(array);
    if(array->object_size <= 0 || numElements < 0)
    {
        return FALSE;
    }
    void* newAddress = realloc(array->data, array->object_size * numElements);
    if(newAddress == NULL)
    {
        return FALSE;
    }
    array->length = numElements;
    return TRUE;
}

static Vector* copy_heap(Vector* array)
{
    ASSERT_INIT(array);
    Vector* copy = init_vector_heap_data(array->length, array->data, array->object_size);
    return copy;
}

static Vector copy_stack(Vector* array)
{
    ASSERT_INIT(array);
    Vector copy = init_vector_stack_data(array->length, array->data, array->object_size);
    return copy;
}

static void clear(Vector* array)
{
    ASSERT_INIT(array);
    free(array->data);
    array->data = NULL;
    array->length = 0;
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
}

Vector* init_vector_heap(ui32 size, ui32 objectSize)
{
    Vector* array = (Vector*) malloc(sizeof(Vector));
    if(array == NULL)
    {
        return NULL;
    }
    array->length = size;
    array->object_size = objectSize;
    array->data = malloc(size * objectSize);
    if(array->data == NULL)
    {
        return array;
    }
    assign_methods(array);
    array->is_initialized = TRUE;
    return array;
}

Vector* init_vector_heap_data(ui32 size, const void* data, ui32 objectSize)
{
    Vector* array = (Vector*) malloc(sizeof(Vector));
    if(array == NULL)
    {
        return NULL;
    }
    array->length = size;
    array->object_size = objectSize;
    array->data = malloc(size * objectSize);
    if(array->data == NULL)
    {
        return array;
    }
    memcpy(array->data, data, size * objectSize);
    assign_methods(array);
    array->is_initialized = TRUE;
    return array;
}

Vector init_vector_stack(ui32 size, ui32 objectSize)
{
    Vector array;
    array.length = size;
    array.object_size = objectSize;
    array.data = malloc(size * objectSize);
    if(array.data == NULL)
    {
        return array;
    }
    assign_methods(&array);
    array.is_initialized = TRUE;
    return array;
}

Vector init_vector_stack_data(ui32 size, const void* data, ui32 objectSize)
{
    Vector array;
    array.length = size;
    array.object_size = objectSize;
    array.data = malloc(size * objectSize);
    if(array.data == NULL)
    {
        return array;
    }
    memcpy(array.data, data, size * objectSize);
    assign_methods(&array);
    array.is_initialized = TRUE;
    return array;
}