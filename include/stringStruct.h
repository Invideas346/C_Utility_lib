#ifndef __STRINGSTRUCT_H__
#define __STRINGSTRUCT_H__

#include <typedef.h>
#include <stdint.h>

typedef struct String String;

struct String
{
    char* value;
    ui32 size;

    boolean isInitalised;

    /**
     * @brief Resizes the array to 0 effectively freeing the memory.
     * @param str
     */
    void (*clear)(String* str);

    /**
     * @brief Appends a char-array to the end of the string.
     * @param str
     * @param stringToAppend
     */
    boolean (*append_cstr)(String* str, const char* stringToAppend);
    /**
     * @brief Appends a string to the end of the string.
     * @param str
     * @param otherString
     */
    boolean (*append)(String* str, const String* otherString);

    /**
     * @brief Sets the string with the passed in char-array.
     * @param str
     * @param stringToBeSet
     */
    boolean (*set_cstr)(String* str, const char* stringToBeSet);
    /**
     * @brief Sets the string with the passed in string.
     * @param str
     * @param otherString
     */
    boolean (*set)(String* str, const String* otherString);

    /**
     * @brief Finds a series of characters in the string.
     * @param str
     * @param str1
     * @return Returns the position in the string if found. A negative number if not found.
     */
    ui32 (*find_cstr)(const String* str, const char* str1);
    /**
     * @brief Finds a series of characters in the string.
     * @param str
     * @param str1
     * @return Returns the position in the string if found. A negative number if not found.
     */
    ui32 (*find)(const String* str, const String* str1);

    /**
     * @brief Compares two strings for equality.
     * @param str
     * @param str1
     * @return Whether the two strings are equal.
     */
    boolean (*equal_cstr)(const String* str, const char* str1);
    /**
     * @brief Compares two strings for equality.
     * @param str
     * @param str1
     * @return Whether the two strings are equal.
     */
    boolean (*equal)(const String* str, const String* str1);

    /**
     * @brief Returns a new string with the corresponding string.
     * @param str
     * @param position1
     * @param position2
     * @return Returns a new string with the corresponding string.
     * Null gets returned if the position are not valid.
     */
    char* (*subString)(const String* str, ui32 position1, ui32 position2);

    /**
     * @brief Returns a copy of the string struct.
     * @param str
     * @return Returns a copy of itself.
     */
    String* (*copy_heap)(const String* str);

    /**
     * @brief Returns a copy of the string struct.
     * @param str
     * @return Returns a copy of itself.
     */
    String (*copy_stack)(const String* str);
};

String* init_string_heap(const char* value);
String init_string_stack(const char* value);

#endif  // __STRINGSTRUCT_H__