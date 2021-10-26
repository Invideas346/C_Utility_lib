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

    void* (*push_back)(dynamicArray* array, const void* data);
    void* (*push_front)(dynamicArray* array, const void* data);

    void* (*pop_back)(dynamicArray* array);
    void* (*pop_front)(dynamicArray* array);

    void* (*at)(dynamicArray* array, ui32 position);

    boolean (*resize)(dynamicArray* array, ui32 numElements);
};

dynamicArray* init_dynamicArray(ui32 size, ui32 objectSize);
dynamicArray* init_dynamicArray_data(ui32 size, const void* data, ui32 objectSize);

#endif  // _DYNAMICARRAY_H