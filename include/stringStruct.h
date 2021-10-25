#ifndef __STRING_H__
#define __STRING_H__

#include <typedef.h>
#include <stdint.h>

typedef struct string string;

struct string
{
    char* value;
    ui32 size;

    boolean initalized;

    void (*clear)(string* str);

    void (*append_cstr)(string* str, const char* stringToAppend);
    void (*append)(string* str, const string* otherString);

    void (*set_cstr)(string* str, const char* stringToBeSet);
    void (*set)(string* str, const string* otherString);

    ui32 (*find_cstr)(const string* str, const char* str1);
    ui32 (*find)(const string* str, const string* str1);

    boolean (*equal_cstr)(const string* str, const char* str1);
    boolean (*equal)(const string* str, const string* str1);
};

string* init_string(const char* value);

#endif  // __STRING_H__