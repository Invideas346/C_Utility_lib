#include <stdio.h>
#include <keyMap.h>
#include <manchester.h>
#include <dynamicArray.h>
#include <string.h>

// TODO: Figure out whether to store pointer referneces in the data structs or make copies of them

int main(void)
{
    String name = init_string_stack("Wolfgang Aigner");
    name.append_cstr(&name, "123");
    printf("My name is %s", name.value);
    name.clear(&name);
    return EXIT_SUCCESS;
}