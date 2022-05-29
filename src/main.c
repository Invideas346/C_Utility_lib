#include <stdlib.h>
#include <stdio.h>
#include <stringStruct.h>

int main(void)
{
    String* string1 = init_string_heap("Test", NULL);
    String string2 = string1->copy_stack(string1, NULL);
    printf("%s\n", string1->value);
    printf("%s\n", string2.value);
    string1->set_cstr(string1, "123", NULL);
    printf("%s\n", string1->value);
    printf("%s\n", string2.value);
    string1->clear(string1, NULL);
    string2.clear(&string2, NULL);
    free(string1);
    return EXIT_SUCCESS;
}