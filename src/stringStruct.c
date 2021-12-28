//
// Created by Wolfgang Aigner on 26.10.2021.
//

#include <stringStruct.h>
#include <linkedLists.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define ASSERT_INIT(x) assert(x->isInitalised)

static void clear(String* str)
{
    ASSERT_INIT(str);
    free(str->value);
    str->length = 0;
    str->value = NULL;
}

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
        void* newAddress = realloc(str->value, sizeToAppend + str->length + 1);
        if(newAddress == NULL)
        {
            return false;
        }
    }
    strcat(str->value, stringToAppend);
    str->length = sizeToAppend + str->length;
    return true;
}

//! not tested yet
static boolean append(String* str, const String* stringToAppend)
{
    assert(str->isInitalised == true && stringToAppend->isInitalised == true);
    if(str->value == NULL)
    {
        void* newAddress = malloc(sizeof(char) * stringToAppend->length + 1);
        if(newAddress == NULL)
        {
            return false;
        }
    }
    else
    {
        void* newAddress = realloc(str->value, stringToAppend->length + str->length + 1);
        if(newAddress == NULL)
        {
            return false;
        }
    }
    strcat(str->value, stringToAppend->value);
    str->length = stringToAppend->length + str->length;
    return true;
}

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
    str->length = sizeToBeSet;
    return true;
}

//! not tested yet
static boolean set(String* str, const String* stringToBeSet)
{
    ASSERT_INIT(str);
    ASSERT_INIT(stringToBeSet);
    free(str->value);
    str->value = malloc(stringToBeSet->length + 1);
    if(str->value == NULL)
    {
        return false;
    }
    strcpy(str->value, stringToBeSet->value);
    str->length = stringToBeSet->length;
    return true;
}

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
    if(index >= self->length || str->length == 0)
    {
        return false;
    }
    char* copy = malloc(self->length);
    strncpy(copy, self->value, index);
    strcat(copy, str->value);
    strcat(copy, &self->value[index]);
    self->length += str->length;
    char* newAddress = realloc(self->value, self->length);
    if(newAddress == NULL)
    {
        return false;
    }
    strcpy(self->value, copy);
    free(copy);
    return true;
}

static boolean insert_cstr(String* self, const char* str, ui32 index)
{
    ASSERT_INIT(self);
    ui32 strLen = strlen(str);
    if(index >= self->length || strLen == 0)
    {
        return false;
    }
    char* copy = malloc(self->length + strLen + 1);
    strncpy(copy, self->value, index);
    copy[index] = 0;
    strcat(copy, str);
    strcat(copy, &self->value[index]);
    copy[self->length + strLen] = 0;
    self->length += strLen;
    char* newAddress = realloc(self->value, self->length);
    if(newAddress == NULL)
    {
        return false;
    }
    strcpy(self->value, copy);
    free(copy);
    return true;
}

//! not tested yet
static char* sub_string(const String* str, ui32 position1, ui32 position2)
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
    str->sub_string = sub_string;
    str->copy_heap = copy_heap;
    str->copy_stack = copy_stack;
    str->insert = insert;
    str->insert_cstr = insert_cstr;
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
    newString->length = size;
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
    newString.length = size;
    assignMethods(&newString);
    newString.isInitalised = true;
    return newString;
}