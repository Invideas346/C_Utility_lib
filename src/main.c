#include <stdio.h>
#include <keyMap.h>
#include <manchester.h>
#include <vector.h>
#include <linkedLists.h>
#include <string.h>

int main(void)
{
    String str = init_string_stack("Test");
    str.append_cstr(&str, "123");
    str.insert_cstr(&str, "insert", 4);
    printf("%s\n", str.value);
    printf("%d\n", str.find_cstr(&str, "123"));
    printf("%d\n", str.equal_cstr(&str, "Test123"));
    printf("%d", str.length);
    str.clear(&str);
    return EXIT_SUCCESS;
}