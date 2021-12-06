#ifndef __STRINGSTRUCT_H__
#define __STRINGSTRUCT_H__

#include <typedef.h>
#include <stdint.h>

typedef struct string string;

// TODO: Implement void* to most function to indicate whether the operation was successful.
struct string
{
    char* value;
    ui32 size;

    boolean isInitalised;

    /**
     * @brief Resizes the array to 0 effectively freeing the memory.
     * @param str
     */
    void (*clear)(string* str);

    /**
     * @brief Appends a char-array to the end of the string.
     * @param str
     * @param stringToAppend
     */
    void* (*append_cstr)(string* str, const char* stringToAppend);
    /**
     * @brief Appends a string to the end of the string.
     * @param str
     * @param otherString
     */
    void* (*append)(string* str, const string* otherString);

    /**
     * @brief Sets the string with the passed in char-array.
     * @param str
     * @param stringToBeSet
     */
    void* (*set_cstr)(string* str, const char* stringToBeSet);
    /**
     * @brief Sets the string with the passed in string.
     * @param str
     * @param otherString
     */
    void* (*set)(string* str, const string* otherString);

    /**
     * @brief Finds a series of characters in the string.
     * @param str
     * @param str1
     * @return Returns the position in the string if found. A negative number if not found.
     */
    ui32 (*find_cstr)(const string* str, const char* str1);
    /**
     * @brief Finds a series of characters in the string.
     * @param str
     * @param str1
     * @return Returns the position in the string if found. A negative number if not found.
     */
    ui32 (*find)(const string* str, const string* str1);

    /**
     * @brief Compares two strings for equality.
     * @param str
     * @param str1
     * @return Whether the two strings are equal.
     */
    boolean (*equal_cstr)(const string* str, const char* str1);
    /**
     * @brief Compares two strings for equality.
     * @param str
     * @param str1
     * @return Whether the two strings are equal.
     */
    boolean (*equal)(const string* str, const string* str1);

    /**
     * @brief Returns a new string with the corresponding string.
     * @param str
     * @param position1
     * @param position2
     * @return Returns a new string with the corresponding string.
     * Null gets returned if the position are not valid.
     */
    char* (*subString)(const string* str, ui32 position1, ui32 position2);

    /**
     * @brief Returns a copy of the string struct.
     * @param str
     * @return Returns a copy of itself.
     */
    string* (*copy_heap)(const string* str);

    /**
     * @brief Returns a copy of the string struct.
     * @param str
     * @return Returns a copy of itself.
     */
    string (*copy_stack)(const string* str);
};

string* init_string_heap(const char* value);
string init_string_stack(const char* value);

#endif  // __STRINGSTRUCT_H__