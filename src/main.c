#include <stdlib.h>
#include <stdio.h>
#include <vector.h>

void print(void* data, ui32 index, ui32 object_size)
{
    printf("Data: %u\n", *(ui32 *)data);
    printf("Index: %u\n", index);
    printf("\n");
}

int main(void)
{
    int data = 4;
    Vector array = init_vector_stack(0, sizeof(ui32), NULL);
    array.push_back(&array, &data, NULL);
    array.push_back(&array, &data, NULL);
    data = 10;
    array.push_back(&array, &data, NULL);
    array.for_each(&array, print, NULL);
    array.clear(&array, NULL);
    return EXIT_SUCCESS;
}