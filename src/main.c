#include <stdio.h>
#include <keyMap.h>
#include <manchester.h>
#include <dynamicArray.h>
#include <linkedLists.h>
#include <string.h>

// TODO: Go over all functions ever implemented and check the behaviour of them
// TODO: Figure out whether to store pointer referneces in the data structs or make copies of them

int main(void)
{
    ui32 test = 320;
    ui32 test1 = 321;
    LinkedList* list = init_list();
    list->push_front(list, &test, sizeof(ui32));
    list->push_front(list, &test1, sizeof(ui32));
    ui32 size = list->size;
    for(ui32 i = 0; i < size; i++)
    {
        ui32* number = (ui32*) list->get_data(list, i);
    }
    list->clear(list);
    free(list);
    return EXIT_SUCCESS;
}