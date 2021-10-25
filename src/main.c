#include <stdio.h>
#include <stdlib.h>

#include <linkedLists.h>
#include <stringStruct.h>

int main(int argc, const char *argv[])
{
    string *aa = init_string("Hallo");
    printf("%s\n", aa->value);

    printf("%d", aa->equal_cstr(aa, "Hallo"));

    LinkedList *list = init_list();
    free(list);

    aa->clear(aa);
    free(aa);
    return 0;
}