#include <stringStruct.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define ASSERT_INIT(x) assert(x->isInitalised)

//! not tested yet
static void clear(String* str)
{
    ASSERT_INIT(str);
    free(str->value);
    str->size = 0;
    str->value = NULL;
}

//! not tested yet
static boolean append_cstr(String* str, const char* stringToAppend)
{
    ASSERT_INIT(str);
    ui32 sizeToAppend = strlen(stringToAppend);
    if(str->value == NULL)
    {
        void* newAddress = malloc(sizeof(char) * sizeToAppend);
        if(newAddress == NULL)
        {
            return false;
        }
    }
    else
    {
        void* newAddress = realloc(str->value, sizeToAppend + str->size + 1);
        if(newAddress == NULL)
        {
            return false;
        }
    }
    strcat(str->value, stringToAppend);
    str->size = sizeToAppend + str->size;
    return true;
}

//! not tested yet
static boolean append(String* str, const String* stringToAppend)
{
    assert(str->isInitalised == true && stringToAppend->isInitalised == true);
    if(str->value == NULL)
    {
        void* newAddress = malloc(sizeof(char) * stringToAppend->size + 1);
        if(newAddress == NULL)
        {
            return false;
        }
    }
    else
    {
        void* newAddress = realloc(str->value, stringToAppend->size + str->size + 1);
        if(newAddress == NULL)
        {
            return false;
        }
    }
    strcat(str->value, stringToAppend->value);
    str->size = stringToAppend->size + str->size;
    return true;
}

//! not tested yet
static boolean set_cstr(String* str, const char* stringToBeSet)
{
    ASSERT_INIT(str);
    ui32 sizeToBeSet = strlen(stringToBeSet);
    free(str->value);
    str->value = malloc(sizeToBeSet + 1);
    if(str->value == NULL)
    {
        return false;
    }
    strcpy(str->value, stringToBeSet);
    str->size = sizeToBeSet;
    return true;
}

//! not tested yet
static boolean set(String* str, const String* stringToBeSet)
{
    ASSERT_INIT(str);
    ASSERT_INIT(stringToBeSet);
    free(str->value);
    str->value = malloc(stringToBeSet->size + 1);
    if(str->value == NULL)
    {
        return false;
    }
    strcpy(str->value, stringToBeSet->value);
    str->size = stringToBeSet->size;
    return true;
}

//! not tested yet
static ui32 find_cstr(const String* str, const char* str1)
{
    ASSERT_INIT(str);
    if(str->value == NULL)
    {
        return INDEX_NOTFOUND;
    }
    return (ui32)(strstr(str->value, str1) - str->value);
}

//! not tested yet
static ui32 find(const String* str, const String* str1)
{
    ASSERT_INIT(str);
    ASSERT_INIT(str1);
    if(str->value == NULL)
    {
        return INDEX_NOTFOUND;
    }
    return (ui32)(strstr(str->value, str1->value) - str->value);
}

//! not tested yet
static boolean equal(const String* str, const String* str1)
{
    ASSERT_INIT(str);
    ASSERT_INIT(str1);
    return (boolean) !strcmp(str->value, str1->value);
}

//! not tested yet
static boolean equal_cstr(const String* str, const char* str1)
{
    ASSERT_INIT(str);
    return (boolean) !strcmp(str->value, str1);
}

//! not tested yet
static boolean insert(String* self, String* str, ui32 index)
{
    ASSERT_INIT(str);
    ASSERT_INIT(self);
    if(index >= self->size || str->size == 0)
    {
        return false;
    }
    char* copy = malloc(self->size);
    strncpy(copy, self->value, index);
    strcat(copy, str->value);
    strcat(copy, self->value[index]);
    self->size += str->size;
    char* newAddress = realloc(self->value, self->size);
    if(newAddress == NULL)
    {
        return false;
    }
    strcpy(self->value, copy);
    free(copy);
    return true;
}

//! not tested yet
static char* subString(const String* str, ui32 position1, ui32 position2)
{
    ASSERT_INIT(str);
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

//! not tested yet
static String* copy_heap(const String* str)
{
    ASSERT_INIT(str);
    String* newString = init_string_heap(str->value);
    return newString;
}

//! not tested yet
static String copy_stack(const String* str)
{
    ASSERT_INIT(str);
    String newString = init_string_stack(str->value);
    return newString;
}

static void assignMethods(String* str)
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

String* init_string_heap(const char* value)
{
    ui32 size = strlen(value);
    String* newString = malloc(sizeof(String));
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

String init_string_stack(const char* value)
{
    ui32 size = strlen(value);
    String newString;
    newString.value = malloc(size + 1);
    strcpy(newString.value, value);
    newString.size = size;
    assignMethods(&newString);
    newString.isInitalised = true;
    return newString;
}