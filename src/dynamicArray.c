//
// Created by Wolfgang Aigner on 26.10.2021.
//

#include <dynamicArray.h>
#include <string.h>
#include <assert.h>

#define ARRAY_INDEX(index) ((index) * (array->objectSize))

static void* push_back(dynamicArray* array, const void* data)
{
    assert(array->initalized == true);
    if(array->objectSize == 0)
    {
        return NULL;
    }
    array->size += 1;
    realloc(array->data, array->size * array->objectSize);
    memcpy(array->data + ARRAY_INDEX(array->size - 1), data, array->objectSize);
    return (array->data + ARRAY_INDEX(array->size - 1));

}

static void* push_front(dynamicArray* array, const void* data)
{
    assert(array->initalized == true);
    if(array->objectSize == 0)
    {
        return NULL;
    }
    array->size += 1;
    realloc(array->data, array->size * array->objectSize);
    memcpy(array->data + ARRAY_INDEX(1), array->data + ARRAY_INDEX(0), array->objectSize);
    memcpy(array->data + ARRAY_INDEX(0), data, array->objectSize);
    return array->data + ARRAY_INDEX(0);
}

static void* pop_back(dynamicArray* array)
{
    assert(array->initalized == true);
    if(array->size == 0 || array->objectSize <= 0)
    {
        return NULL;
    }
    void* data = malloc(array->objectSize);
    memcpy(data, array->data + ARRAY_INDEX(array->size - 1), array->objectSize);
    array->size -= 1;
    realloc(array->data, array->size * array->objectSize);
    return data;
}

static void* pop_front(dynamicArray* array)
{
    assert(array->initalized == true);
    if(array->size == 0 || array->objectSize <= 0)
    {
        return NULL;
    }
    void* data = malloc(array->objectSize);
    memcpy(data, array->data + ARRAY_INDEX(0), array->objectSize);
    array->size -= 1;
    void* temp = malloc(array->objectSize * array->size);
    memcpy(temp, array->data + ARRAY_INDEX(1), array->size * array->objectSize);
    realloc(array->data, array->size * array->objectSize);
    memcpy(array->data, temp, array->size * array->objectSize);
    free(temp);
    return data;
}

static void* at(dynamicArray* array, ui32 position)
{
    assert(array->initalized == true);
    if(array->size == 0 || array->objectSize <= 0)
    {
        return NULL;
    }
    void* data = malloc(array->objectSize);
    memcpy(data, array->data + ARRAY_INDEX(position), array->objectSize);
    return data;
}

boolean resize(dynamicArray* array, ui32 numElements)
{
    assert(array->initalized == true);
    if(array->size == 0 || array->objectSize <= 0 || numElements < 0)
    {
        return false;
    }
    realloc(array->data, array->objectSize * numElements);
    return true;
}

static void assignMethods(dynamicArray* array)
{
    array->push_back = push_back;
    array->push_front = push_front;
    array->pop_back = pop_back;
    array->pop_front = pop_front;
    array->at = at;
}

dynamicArray* init_dynamicArray(ui32 size, ui32 objectSize)
{
    dynamicArray* array = (dynamicArray*) malloc(sizeof(dynamicArray));
    if(array == NULL)
    {
        return NULL;
    }
    array->size = size;
    array->objectSize = objectSize;
    array->data = malloc(size * objectSize);
    assignMethods(array);
    array->initalized = true;
    return array;
}

dynamicArray* init_dynamicArray_data(ui32 size, const void* data, ui32 objectSize) {
    dynamicArray* array = (dynamicArray*) malloc(sizeof(dynamicArray));
    if(array == NULL)
    {
        return NULL;
    }
    array->size = size;
    array->objectSize = objectSize;
    array->data = malloc(size * objectSize);
    memcpy(array->data, data, size * objectSize);
    assignMethods(array);
    array->initalized = true;
    return array;
}