#include <stringStruct.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

static void clear(string* str)
{
    assert(str->isInitalised == true);
    free(str->value);
    str->size = 0;
    str->value = NULL;
}

static void* append_cstr(string* str, const char* stringToAppend)
{
    assert(str->isInitalised == true);
    ui32 sizeToAppend = strlen(stringToAppend);
    if(str->value == NULL)
    {
        void* newAddress = malloc(sizeof(char) * sizeToAppend);
        if(newAddress == NULL)
        {
            return NULL;
        }
    }
    else
    {
        void* newAddress = realloc(str->value, sizeToAppend + str->size + 1);
        if(newAddress == NULL)
        {
            return NULL;
        }
    }
    strcat(str->value, stringToAppend);
    str->size = sizeToAppend + str->size;
}

static void* append(string* str, const string* stringToAppend)
{
    assert(str->isInitalised == true && stringToAppend->isInitalised == true);
    if(str->value == NULL)
    {
        void* newAddress = malloc(sizeof(char) * stringToAppend->size + 1);
        if(newAddress == NULL)
        {
            return NULL;
        }
    }
    else
    {
        void* newAddress = realloc(str->value, stringToAppend->size + str->size + 1);
        if(newAddress == NULL)
        {
            return NULL;
        }
    }
    strcat(str->value, stringToAppend->value);
    str->size = stringToAppend->size + str->size;
}

static void* set_cstr(string* str, const char* stringToBeSet)
{
    assert(str->isInitalised == true);
    ui32 sizeToBeSet = strlen(stringToBeSet);
    free(str->value);
    str->value = malloc(sizeToBeSet + 1);
    strcpy(str->value, stringToBeSet);
    str->size = sizeToBeSet;
}

static void* set(string* str, const string* stringToBeSet)
{
    assert(str->isInitalised == true && stringToBeSet->isInitalised == true);
    free(str->value);
    str->value = malloc(stringToBeSet->size + 1);
    strcpy(str->value, stringToBeSet->value);
    str->size = stringToBeSet->size;
}

static ui32 find_cstr(const string* str, const char* str1)
{
    assert(str->isInitalised == true);
    if(str->value == NULL)
    {
        return INDEX_NOTFOUND;
    }
    return (ui32)(strstr(str->value, str1) - str->value);
}

static ui32 find(const string* str, const string* str1)
{
    assert(str->isInitalised == true && str1->isInitalised == true);
    if(str->value == NULL)
    {
        return INDEX_NOTFOUND;
    }
    return (ui32)(strstr(str->value, str1->value) - str->value);
}

static boolean equal(const string* str, const string* str1)
{
    assert(str->isInitalised == true && str1->isInitalised == true);
    return (boolean) !strcmp(str->value, str1->value);
}

static boolean equal_cstr(const string* str, const char* str1)
{
    assert(str->isInitalised == true);
    return (boolean) !strcmp(str->value, str1);
}

static char* subString(const string* str, ui32 position1, ui32 position2)
{
    assert(str->isInitalised == true);
    if(position1 >= position2)
    {
        return NULL;
    }
    size_t size = (position2 - position1);
    char* temp = (char*) malloc(size + 1);
    memcpy(temp, str->value + position1, position2 - position1);
    temp[size] = '\0';
    return temp;
}

static string* copy_heap(const string* str)
{
    string* newString = init_string_heap(str->value);
    return newString;
}

static string copy_stack(const string* str)
{
    string newString = init_string_stack(str->value);
    return newString;
}

static void assignMethods(string* str)
{
    str->clear = clear;
    str->append = append;
    str->append_cstr = append_cstr;
    str->set = set;
    str->set_cstr = set_cstr;
    str->find_cstr = find_cstr;
    str->find = find;
    str->equal_cstr = equal_cstr;
    str->equal = equal;
    str->subString = subString;
    str->copy_heap = copy_heap;
    str->copy_stack = copy_stack;
}

string* init_string_heap(const char* value)
{
    ui32 size = strlen(value);
    string* newString = malloc(sizeof(string));
    if(newString == NULL)
    {
        return NULL;
    }
    newString->value = malloc(size + 1);
    strcpy(newString->value, value);
    newString->size = size;
    assignMethods(newString);
    newString->isInitalised = true;
    return newString;
}

string init_string_stack(const char* value)
{
    ui32 size = strlen(value);
    string newString;
    newString.value = malloc(size + 1);
    strcpy(newString.value, value);
    newString.size = size;
    assignMethods(&newString);
    newString.isInitalised = true;
    return newString;
}