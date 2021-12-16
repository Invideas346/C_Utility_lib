//
// Created by Wolfgang Aigner on 26.10.2021.
//

#include <dynamicArray.h>
#include <string.h>
#include <assert.h>

#define ARRAY_INDEX(index) ((index) * (array->objectSize))

static void* push_back(DynamicArray* array, const void* data)
{
    assert(array->isInitalised == true);
    if(array->objectSize == 0)
    {
        return NULL;
    }
    array->size += 1;
    void* success = realloc(array->data, array->size * array->objectSize);
    memcpy(array->data + ARRAY_INDEX(array->size - 1), data, array->objectSize);
    return array->data + ARRAY_INDEX(array->size - 1);
}

static void* push_front(DynamicArray* array, const void* data)
{
    assert(array->isInitalised == true);
    if(array->objectSize == 0)
    {
        return NULL;
    }
    array->size += 1;
    void* newAddress = realloc(array->data, array->size * array->objectSize);
    if(newAddress == NULL)
    {
        return NULL;
    }
    memcpy(array->data + ARRAY_INDEX(1), array->data + ARRAY_INDEX(0), array->objectSize);
    memcpy(array->data + ARRAY_INDEX(0), data, array->objectSize);
    return array->data + ARRAY_INDEX(0);
}

static boolean pop_back(DynamicArray* array)
{
    assert(array->isInitalised == true);
    if(array->size == 0 || array->objectSize <= 0)
    {
        return false;
    }
    array->size -= 1;
    void* newAddress = realloc(array->data, array->size * array->objectSize);
    if(newAddress == NULL)
    {
        return false;
    }
    return true;
}

static boolean pop_front(DynamicArray* array)
{
    assert(array->isInitalised == true);
    if(array->size == 0 || array->objectSize <= 0)
    {
        return false;
    }
    array->size -= 1;
    void* temp = malloc(array->objectSize * array->size);
    memcpy(temp, array->data + ARRAY_INDEX(1), array->size * array->objectSize);
    void* newAddress = realloc(array->data, array->size * array->objectSize);
    if(newAddress == NULL)
    {
        free(temp);
        return false;
    }
    memcpy(array->data, temp, array->size * array->objectSize);
    free(temp);
    return true;
}

static void* at(DynamicArray* array, ui32 position)
{
    assert(array->isInitalised == true);
    if(array->size == 0 || array->objectSize <= 0)
    {
        return NULL;
    }
    return array->data + ARRAY_INDEX(position);
}

boolean resize(DynamicArray* array, ui32 numElements)
{
    assert(array->isInitalised == true);
    if(array->size == 0 || array->objectSize <= 0 || numElements < 0)
    {
        return false;
    }
    void* newAddress = realloc(array->data, array->objectSize * numElements);
    if(newAddress == NULL)
    {
        return false;
    }
    return true;
}

static DynamicArray* copy_heap(DynamicArray* array)
{
    assert(array->isInitalised == true);
    DynamicArray* copy =
        init_DYNAMICARRAY_Heap_data(array->size, array->data, array->objectSize);
    return copy;
}

static DynamicArray copy_stack(DynamicArray* array)
{
    assert(array->isInitalised == true);
    DynamicArray copy = init_dynamicArray_stack_data(array->size, array->data, array->objectSize);
    return copy;
}

static void clear(DynamicArray* array)
{
    free(array->data);
    array->size = 0;
}

static void assignMethods(DynamicArray* array)
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

DynamicArray* init_DYNAMICARRAY_Heap(ui32 size, ui32 objectSize)
{
    DynamicArray* array = (DynamicArray*) malloc(sizeof(DynamicArray));
    if(array == NULL)
    {
        return NULL;
    }
    array->size = size;
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

DynamicArray* init_DYNAMICARRAY_Heap_data(ui32 size, const void* data, ui32 objectSize)
{
    DynamicArray* array = (DynamicArray*) malloc(sizeof(DynamicArray));
    if(array == NULL)
    {
        return NULL;
    }
    array->size = size;
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

DynamicArray init_dynamicArray_stack(ui32 size, ui32 objectSize)
{
    DynamicArray array;
    array.size = size;
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

DynamicArray init_dynamicArray_stack_data(ui32 size, const void* data, ui32 objectSize)
{
    DynamicArray array;
    array.size = size;
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