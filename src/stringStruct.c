#include <stringStruct.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

static void clear(string* str)
{
    assert(str->initalized == true);
    free(str->value);
    str->size = 0;
}

static void append_cstr(string* str, const char* stringToAppend)
{
    assert(str->initalized == true);
    ui32 sizeToAppend = strlen(stringToAppend);
    realloc(str->value, sizeToAppend + str->size + 1);
    strcat(str->value, stringToAppend);
    str->size = sizeToAppend + str->size;
}

static void append(string* str, const string* stringToAppend)
{
    assert(str->initalized == true && stringToAppend->initalized == true);
    realloc(str->value, stringToAppend->size + str->size + 1);
    strcat(str->value, stringToAppend->value);
    str->size = stringToAppend->size + str->size;
}

static void set_cstr(string* str, const char* stringToBeSet)
{
    assert(str->initalized == true);
    ui32 sizeToBeSet = strlen(stringToBeSet);
    free(str->value);
    str->value = malloc(sizeToBeSet + 1);
    strcpy(str->value, stringToBeSet);
    str->size = sizeToBeSet;
}

static void set(string* str, const string* stringToBeSet)
{
    assert(str->initalized == true && stringToBeSet->initalized == true);
    free(str->value);
    str->value = malloc(stringToBeSet->size + 1);
    strcpy(str->value, stringToBeSet->value);
    str->size = stringToBeSet->size;
}

static ui32 find_cstr(const string* str, const char* str1)
{
    assert(str->initalized == true);
    return (ui32) (strstr(str->value, str1) - str->value);
}

static ui32 find(const string* str, const string* str1)
{
    assert(str->initalized == true && str1->initalized == true);
    return (ui32) (strstr(str->value, str1->value) - str->value);
}

static boolean equal(const string* str, const string* str1)
{
    assert(str->initalized == true && str1->initalized == true);
    return (boolean) !strcmp(str->value, str1->value);
}

static boolean equal_cstr(const string* str, const char* str1)
{
    assert(str->initalized == true);
    return (boolean) !strcmp(str->value, str1);
}

string* init_string(const char* value)
{
    ui32 size = strlen(value);
    string* newString = malloc(sizeof(string));

    newString->value = malloc(size + 1);
    strcpy(newString->value, value);
    newString->size = size;

    newString->clear = clear;

    newString->append = append;
    newString->append_cstr = append_cstr;

    newString->set = set;
    newString->set_cstr = set_cstr;

    newString->find_cstr = find_cstr;
    newString->find = find;

    newString->equal_cstr = equal_cstr;
    newString->equal = equal;

    newString->initalized = true;
    return newString;
}