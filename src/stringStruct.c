//
// Created by Wolfgang Aigner on 26.10.2021.
//

#include <stringStruct.h>
#include <string.h>
#include <stdlib.h>

inline static void assign_error_code(STRING_ERROR_CODE* error_code, STRING_ERROR_CODE value)
{
    if(error_code != NULL) *error_code = value;
}

static void clear(String* str, STRING_ERROR_CODE* error_code)
{
    if(!str->is_initialized) {
        assign_error_code(error_code, STRING_NOT_INITIALIZED);
        return;
    }
    free(str->value);
    str->length = 0;
    str->value = NULL;
    assign_error_code(error_code, STRING_OK);
}

static boolean append_cstr(String* str, const char* string_to_append, STRING_ERROR_CODE* error_code)
{
    if(!str->is_initialized) {
        assign_error_code(error_code, STRING_NOT_INITIALIZED);
        return FALSE;
    }
    ui32 size_to_append = strlen(string_to_append);
    if(str->value == NULL) {
        void* new_address = malloc(sizeof(char) * size_to_append);
        if(new_address == NULL) {
            assign_error_code(error_code, STRING_MEMORY_ALLOCATION_ERROR);
            return FALSE;
        }
    } else {
        void* new_address = realloc(str->value, size_to_append + str->length + 1);
        if(new_address == NULL) {
            assign_error_code(error_code, STRING_MEMORY_ALLOCATION_ERROR);
            return FALSE;
        }
    }
    strncat(str->value, string_to_append, size_to_append);
    str->length = size_to_append + str->length;
    str->value[str->length] = 0;
    assign_error_code(error_code, STRING_OK);
    return TRUE;
}

static boolean append(String* str, const String* string_to_append, STRING_ERROR_CODE* error_code)
{
    if(!str->is_initialized) {
        assign_error_code(error_code, STRING_NOT_INITIALIZED);
        return FALSE;
    }
    if(str->value == NULL) {
        void* new_address = malloc(sizeof(char) * string_to_append->length + 1);
        if(new_address == NULL) {
            assign_error_code(error_code, STRING_MEMORY_ALLOCATION_ERROR);
            return FALSE;
        }
    } else {
        void* new_address = realloc(str->value, string_to_append->length + str->length + 1);
        if(new_address == NULL) {
            assign_error_code(error_code, STRING_MEMORY_ALLOCATION_ERROR);
            return FALSE;
        }
    }
    strncat(str->value, string_to_append->value, string_to_append->length);
    str->length = string_to_append->length + str->length;
    str->value[str->length] = 0;
    assign_error_code(error_code, STRING_OK);
    return TRUE;
}

static boolean set_cstr(String* str, const char* string_to_be_set, STRING_ERROR_CODE* error_code)
{
    if(!str->is_initialized) {
        assign_error_code(error_code, STRING_NOT_INITIALIZED);
        return FALSE;
    }
    ui32 size_to_be_set = strlen(string_to_be_set);
    free(str->value);
    str->value = malloc(size_to_be_set + 1);
    if(str->value == NULL) {
        assign_error_code(error_code, STRING_MEMORY_ALLOCATION_ERROR);
        return FALSE;
    }
    strncpy(str->value, string_to_be_set, size_to_be_set);
    str->length = size_to_be_set;
    str->value[str->length] = 0;
    assign_error_code(error_code, STRING_OK);
    return TRUE;
}

static boolean set(String* str, const String* string_to_be_set, STRING_ERROR_CODE* error_code)
{
    if(!str->is_initialized || !string_to_be_set->is_initialized) {
        assign_error_code(error_code, STRING_NOT_INITIALIZED);
        return FALSE;
    }
    free(str->value);
    str->value = malloc(string_to_be_set->length + 1);
    if(str->value == NULL) {
        assign_error_code(error_code, STRING_MEMORY_ALLOCATION_ERROR);
        return FALSE;
    }
    strncpy(str->value, string_to_be_set->value, string_to_be_set->length);
    str->length = string_to_be_set->length;
    str->value[str->length] = 0;
    assign_error_code(error_code, STRING_OK);
    return TRUE;
}

static ui32 find_cstr(const String* str, const char* str1, STRING_ERROR_CODE* error_code)
{
    if(!str->is_initialized) {
        assign_error_code(error_code, STRING_NOT_INITIALIZED);
        return INDEX_NOTFOUND;
    }
    if(str->value == NULL) {
        return INDEX_NOTFOUND;
    }
    assign_error_code(error_code, STRING_OK);
    const char* index = strstr(str->value, str1);
    return (index == NULL) ? (ui32) INDEX_NOTFOUND : (ui32) (index - str->value);
}

static ui32 find(const String* str, const String* str1, STRING_ERROR_CODE* error_code)
{
    if(!str->is_initialized || !str1->is_initialized) {
        assign_error_code(error_code, STRING_NOT_INITIALIZED);
        return INDEX_NOTFOUND;
    }
    if(str->value == NULL) {
        return INDEX_NOTFOUND;
    }
    assign_error_code(error_code, STRING_OK);
    const char* index = strstr(str->value, str1->value);
    return (index == NULL) ? (ui32) INDEX_NOTFOUND : (ui32) (index - str->value);
}

static boolean equal(const String* str, const String* str1, STRING_ERROR_CODE* error_code)
{
    if(!str->is_initialized || !str1->is_initialized) {
        assign_error_code(error_code, STRING_NOT_INITIALIZED);
        return FALSE;
    }
    assign_error_code(error_code, STRING_OK);
    return (boolean) !strcmp(str->value, str1->value);
}

static boolean equal_cstr(const String* str, const char* str1, STRING_ERROR_CODE* error_code)
{
    if(!str->is_initialized || str1 == NULL) {
        assign_error_code(error_code, STRING_NOT_INITIALIZED);
        return FALSE;
    }
    assign_error_code(error_code, STRING_OK);
    return (boolean) !strcmp(str->value, str1);
}

static boolean insert(String* self, String* str, ui32 index, STRING_ERROR_CODE* error_code)
{
    if(!str->is_initialized || !self->is_initialized) {
        assign_error_code(error_code, STRING_NOT_INITIALIZED);
        return FALSE;
    }
    if(index >= self->length || str->length == 0 || index < 0) {
        return FALSE;
    }
    char* copy = malloc(self->length);
    strncpy(copy, self->value, index);
    strncat(copy, str->value, strlen(str->value));
    strncat(copy, &self->value[index], strlen(str->value) - index);
    self->length += str->length;
    char* new_address = realloc(self->value, self->length);
    if(new_address == NULL) {
        assign_error_code(error_code, STRING_MEMORY_ALLOCATION_ERROR);
        return FALSE;
    }
    strncpy(self->value, copy, self->length);
    free(copy);
    assign_error_code(error_code, STRING_OK);
    return TRUE;
}

static boolean insert_cstr(String* self, const char* str, ui32 index, STRING_ERROR_CODE* error_code)
{
    if(!self->is_initialized) {
        assign_error_code(error_code, STRING_NOT_INITIALIZED);
        return FALSE;
    }
    ui32 str_len = strlen(str);
    if(index >= self->length || str_len == 0 || index < 0) {
        return FALSE;
    }
    char* copy = malloc(self->length + str_len + 1);
    strncpy(copy, self->value, index);
    copy[index] = 0;
    strcat(copy, str);
    strcat(copy, &self->value[index]);
    copy[self->length + str_len] = 0;
    self->length += str_len;
    char* new_address = realloc(self->value, self->length);
    if(new_address == NULL) {
        assign_error_code(error_code, STRING_MEMORY_ALLOCATION_ERROR);
        return FALSE;
    }
    strncpy(self->value, copy, self->length);
    free(copy);
    assign_error_code(error_code, STRING_OK);
    return TRUE;
}

static char* sub_string(const String* str, ui32 position1, ui32 position2,
                        STRING_ERROR_CODE* error_code)
{
    if(!str->is_initialized) {
        assign_error_code(error_code, STRING_NOT_INITIALIZED);
        return NULL;
    }
    if(position1 >= position2 || position1 > str->length || position2 > str->length) {
        return NULL;
    }
    size_t size = (position2 - position1);
    char* temp = (char*) malloc(size + 1);
    if(temp == NULL) {
        assign_error_code(error_code, STRING_MEMORY_ALLOCATION_ERROR);
        return NULL;
    }
    memcpy(temp, str->value + position1, position2 - position1);
    temp[size] = '\0';
    assign_error_code(error_code, STRING_OK);
    return temp;
}

static String* copy_heap(const String* str, STRING_ERROR_CODE* error_code)
{
    if(!str->is_initialized) {
        assign_error_code(error_code, STRING_NOT_INITIALIZED);
        return NULL;
    }
    String* new_string = init_string_heap(str->value, error_code);
    return new_string;
}

static String copy_stack(const String* str, STRING_ERROR_CODE* error_code)
{
    if(!str->is_initialized) {
        assign_error_code(error_code, STRING_NOT_INITIALIZED);
        return *str;
    }
    String new_string = init_string_stack(str->value, error_code);
    return new_string;
}

inline static void assign_methods(String* str)
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

String* init_string_heap(const char* value, STRING_ERROR_CODE* error_code)
{
    ui32 size = strlen(value);
    String* new_string = malloc(sizeof(String));
    if(new_string == NULL) {
        assign_error_code(error_code, STRING_MEMORY_ALLOCATION_ERROR);
        return NULL;
    }
    new_string->value = malloc(size + 1);
    if(new_string->value == NULL) {
        assign_error_code(error_code, STRING_MEMORY_ALLOCATION_ERROR);
        return NULL;
    }
    strncpy(new_string->value, value, size);
    new_string->length = size;
    assign_methods(new_string);
    new_string->is_initialized = TRUE;
    assign_error_code(error_code, STRING_OK);
    return new_string;
}

String init_string_stack(const char* value, STRING_ERROR_CODE* error_code)
{
    ui32 size = strlen(value);
    String new_string;
    new_string.value = malloc(size + 1);
    if(new_string.value == NULL) {
        assign_error_code(error_code, STRING_MEMORY_ALLOCATION_ERROR);
        return new_string;
    }
    strncpy(new_string.value, value, size);
    new_string.length = size;
    assign_methods(&new_string);
    new_string.is_initialized = TRUE;
    assign_error_code(error_code, STRING_OK);
    return new_string;
}