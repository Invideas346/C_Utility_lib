#ifndef __STRINGSTRUCT_H__
#define __STRINGSTRUCT_H__

#include <typedef.h>
#include <stdint.h>

typedef struct String String;

typedef enum STRING_ERROR_CODE {
    STRING_OK = 0,
    STRING_GENERAL_ERROR = 1,
    STRING_NOT_INITIALIZED = 2 | STRING_GENERAL_ERROR,
    STRING_MEMORY_ALLOCATION_ERROR = 3 | STRING_GENERAL_ERROR
} STRING_ERROR_CODE;

struct String {
    char* value;
    ui32 length;

    boolean is_initialized;

    /**
     * @brief Resizes the array to 0 effectively freeing the memory.
     * @param str
     * @param error_code Can be used to retrieve a error code
     */
    void (*clear)(String* str, STRING_ERROR_CODE* error_code);

    /**
     * @brief Inserts a given string at the specified index.
     * @param self
     * @param str
     * @param index
     * @param error_code Can be used to retrieve a error code
     */
    boolean (*insert)(String* self, String* str, ui32 index, STRING_ERROR_CODE* error_code);

    /**
     * @brief Inserts a given string at the specified index.
     * @param self
     * @param str
     * @param index
     * @param error_code Can be used to retrieve a error code
     */
    boolean (*insert_cstr)(String* self, const char* str, ui32 index,
                           STRING_ERROR_CODE* error_code);

    /**
     * @brief Appends a char-array to the end of the string.
     * @param str
     * @param string_to_append
     * @param error_code Can be used to retrieve a error code
     */
    boolean (*append_cstr)(String* str, const char* string_to_append,
                           STRING_ERROR_CODE* error_code);
    /**
     * @brief Appends a string to the end of the string.
     * @param str
     * @param other_string
     * @param error_code Can be used to retrieve a error code
     */
    boolean (*append)(String* str, const String* other_string, STRING_ERROR_CODE* error_code);

    /**
     * @brief Sets the string with the passed in char-array.
     * @param str
     * @param string_to_be_set
     * @param error_code Can be used to retrieve a error code
     */
    boolean (*set_cstr)(String* str, const char* string_to_be_set, STRING_ERROR_CODE* error_code);
    /**
     * @brief Sets the string with the passed in string.
     * @param str
     * @param other_string
     * @param error_code Can be used to retrieve a error code
     */
    boolean (*set)(String* str, const String* other_string, STRING_ERROR_CODE* error_code);

    /**
     * @brief Finds a series of characters in the string.
     * @param str
     * @param str1
     * @param error_code Can be used to retrieve a error code
     * @return Returns the position in the string if found. A negative number if not found.
     */
    ui32 (*find_cstr)(const String* str, const char* str1, STRING_ERROR_CODE* error_code);
    /**
     * @brief Finds a series of characters in the string.
     * @param str
     * @param str1
     * @param error_code Can be used to retrieve a error code
     * @return Returns the position in the string if found. A negative number if not found.
     */
    ui32 (*find)(const String* str, const String* str1, STRING_ERROR_CODE* error_code);

    /**
     * @brief Compares two strings for equality.
     * @param str
     * @param str1
     * @param error_code Can be used to retrieve a error code
     * @return Whether the two strings are equal.
     */
    boolean (*equal_cstr)(const String* str, const char* str1, STRING_ERROR_CODE* error_code);
    /**
     * @brief Compares two strings for equality.
     * @param str
     * @param str1
     * @param error_code Can be used to retrieve a error code
     * @return Whether the two strings are equal.
     */
    boolean (*equal)(const String* str, const String* str1, STRING_ERROR_CODE* error_code);

    /**
     * @brief Returns a new string with the corresponding string.
     * @param str
     * @param position1
     * @param position2
     * @param error_code Can be used to retrieve a error code
     * @return Returns a new string with the corresponding string.
     * Null gets returned if the position are not valid.
     */
    char* (*sub_string)(const String* str, ui32 position1, ui32 position2,
                        STRING_ERROR_CODE* error_code);

    /**
     * @brief Returns a copy of the string struct.
     * @param str
     * @param error_code Can be used to retrieve a error code
     * @return Returns a copy of itself.
     */
    String* (*copy_heap)(const String* str, STRING_ERROR_CODE* error_code);

    /**
     * @brief Returns a copy of the string struct.
     * @param str
     * @param error_code Can be used to retrieve a error code
     * @return Returns a copy of itself.
     */
    String (*copy_stack)(const String* str, STRING_ERROR_CODE* error_code);
};

String* init_string_heap(const char* value, STRING_ERROR_CODE* error_code);
String init_string_stack(const char* value, STRING_ERROR_CODE* error_code);

#endif  // __STRINGSTRUCT_H__