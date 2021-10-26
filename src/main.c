#include <stdio.h>
#include <linkedLists.h>
#include <dynamicArray.h>

int main(void)
{
    int numbers[] = {1,2,3,4,5,6,7,8,9,10,11,12};
    dynamicArray* array = init_dynamicArray(0, sizeof(ui32));
    for(int i = 0; i < 12; ++i)
    {
        array->push_back(array, &numbers[i]);
    }
    for(int i = 0; i < 12; ++i)
    {
        ui32* testNum = array->at(array, i);
        printf("%d. Number: %d\n", i, *testNum);
        free(testNum);
    }
    free(array);
    return 0;
}