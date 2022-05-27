#include <stdlib.h>
#include <stdio.h>
#include <stringStruct.h>

int main(void)
{
    String* string1 = init_string_heap("Test", NULL);
    String* string2 = init_string_heap("Test", NULL);

    boolean index = string1->insert_cstr(string1, "string1", 1, NULL);
    printf("%u\n", index);
    printf("%s\n", string1->value);

    string1->clear(string1, NULL);
    free(string1);
    string2->clear(string2, NULL);
    free(string2);
    return EXIT_SUCCESS;
}