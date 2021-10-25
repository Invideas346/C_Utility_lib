#include <stdio.h>

#include "linkedLists.h"

int main(int argc, const char *argv[])
{
    int a[] = {0, 1, 2, 3};
    LinkedList *list = init_list();
    list->push_back(list, a, sizeof(int));
    list->push_back(list, a + 1, sizeof(int));
    printf("1. %d\n", (int*)list->pop_front(list));
    printf("2. %d\n", (int*)list->pop_front(list));
    printf("3. %d\n", (int*)list->pop_front(list));
    printf("4. %d\n", (int*)list->pop_front(list));
    free(list);
    return 0;
}