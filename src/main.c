#include <stdlib.h>
#include <stdio.h>
#include <vector.h>

void print(void* data, ui32 index, ui32 object_size)
{
    printf("Data: %u\n", *(ui32*) data);
    printf("Index: %u\n", index);
    printf("\n");
}

int main(void)
{
    return EXIT_SUCCESS;
}