//
// Created by Wolfgang Aigner on 26.10.2021.
//

#include <vector.h>
#include <string.h>
#include <assert.h>

#define ARRAY_INDEX(index) ((index) * (array->objectSize))
#define ASSERT_INIT(x) assert(x->isInitalised)

static void* push_back(Vector* array, const void* data)
{
    ASSERT_INIT(array);
    if(array->objectSize == 0)
    {
        return NULL;
    }
    array->length += 1;
    void* newAddress = realloc(array->data, array->length * array->objectSize);
    if(newAddress == NULL)
    {
        return NULL;
    }
    memcpy(array->data + ARRAY_INDEX(array->length - 1), data, array->objectSize);
    return array->data + ARRAY_INDEX(array->length - 1);
}

static void* push_front(Vector* array, const void* data)
{
    ASSERT_INIT(array);
    if(array->objectSize == 0)
    {
        return NULL;
    }
    array->length += 1;
    void* newAddress = realloc(array->data, array->length * array->objectSize);
    if(newAddress == NULL)
    {
        return NULL;
    }
    if(array->length != 1)
    {
        memcpy(array->data + ARRAY_INDEX(1), array->data + ARRAY_INDEX(0),
               array->objectSize * (array->length - 1));
    }
    memcpy(array->data + ARRAY_INDEX(0), data, array->objectSize);
    return array->data + ARRAY_INDEX(0);
}

static boolean pop_back(Vector* array)
{
    ASSERT_INIT(array);
    if(array->length == 0 || array->objectSize <= 0)
    {
        return false;
    }
    array->length -= 1;
    void* newAddress = realloc(array->data, array->length * array->objectSize);
    if(newAddress == NULL)
    {
        return false;
    }
    return true;
}

static boolean pop_front(Vector* array)
{
    ASSERT_INIT(array);
    if(array->length == 0 || array->objectSize <= 0)
    {
        return false;
    }
    array->length -= 1;
    void* temp = malloc(array->objectSize * array->length);
    if(temp == NULL)
    {
        return false;
    }
    memcpy(temp, array->data + ARRAY_INDEX(1), array->length * array->objectSize);
    void* newAddress = realloc(array->data, array->length * array->objectSize);
    if(newAddress == NULL)
    {
        free(temp);
        return false;
    }
    memcpy(array->data, temp, array->length * array->objectSize);
    free(temp);
    return true;
}

static void* at(Vector* array, ui32 position)
{
    ASSERT_INIT(array);
    if(array->length == 0 || array->objectSize <= 0)
    {
        return NULL;
    }
    return array->data + ARRAY_INDEX(position);
}

boolean resize(Vector* array, ui32 numElements)
{
    ASSERT_INIT(array);
    if(array->objectSize <= 0 || numElements < 0)
    {
        return false;
    }
    void* newAddress = realloc(array->data, array->objectSize * numElements);
    if(newAddress == NULL)
    {
        return false;
    }
    array->length = numElements;
    return true;
}

static Vector* copy_heap(Vector* array)
{
    ASSERT_INIT(array);
    Vector* copy = init_vector_heap_data(array->length, array->data, array->objectSize);
    return copy;
}

static Vector copy_stack(Vector* array)
{
    ASSERT_INIT(array);
    Vector copy = init_vector_stack_data(array->length, array->data, array->objectSize);
    return copy;
}

static void clear(Vector* array)
{
    ASSERT_INIT(array);
    free(array->data);
    array->data = NULL;
    array->length = 0;
}

static void assignMethods(Vector* array)
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
    array->objectSize = objectSize;
    array->data = malloc(size * objectSize);
    if(array->data == NULL)
    {
        return array;
    }
    assignMethods(array);
    array->isInitalised = true;
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
    array->objectSize = objectSize;
    array->data = malloc(size * objectSize);
    if(array->data == NULL)
    {
        return array;
    }
    memcpy(array->data, data, size * objectSize);
    assignMethods(array);
    array->isInitalised = true;
    return array;
}

Vector init_vector_stack(ui32 size, ui32 objectSize)
{
    Vector array;
    array.length = size;
    array.objectSize = objectSize;
    array.data = malloc(size * objectSize);
    if(array.data == NULL)
    {
        return array;
    }
    assignMethods(&array);
    array.isInitalised = true;
    return array;
}

Vector init_vector_stack_data(ui32 size, const void* data, ui32 objectSize)
{
    Vector array;
    array.length = size;
    array.objectSize = objectSize;
    array.data = malloc(size * objectSize);
    if(array.data == NULL)
    {
        return array;
    }
    memcpy(array.data, data, size * objectSize);
    assignMethods(&array);
    array.isInitalised = true;
    return array;
}