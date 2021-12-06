//
// Created by wolfgang on 11.11.2021.
//

#ifndef CUTILITY_KEYMAP_H
#define CUTILITY_KEYMAP_H

#include <typedef.h>
#include <stringStruct.h>

typedef struct KeyPair KeyPair;
struct KeyPair
{
    string key;
    size_t size;
    void* data;

    boolean isInitialised;

    /**
     * @brief Clear a KeyPair and effecticly frees all allocated memory.
     */
    void (*clear)(KeyPair* pair);
};

/**
 * @brief Creates a new KeyPair initalized with all function pointers.
 * @return KeyMap*
 */
KeyPair* init_keypair_heap(string* key, void* data, size_t size);
/**
 * @brief Creates a new KeyPair initalized with all function pointers.
 * @return KeyMap
 */
KeyPair init_keypair_stack(string* key, void* data, size_t size);

/**
 * @brief Creates a new KeyPair initalized with all function pointers.
 * @return KeyMap*
 */
KeyPair* init_keypair_heap_cstr(const char* key, void* data, size_t size);
/**
 * @brief Creates a new KeyMap initalized with all function pointers.
 * @return KeyMap
 */
KeyPair init_keypair_stack_cstr(const char* key, void* data, size_t size);

typedef struct KeyMap KeyMap;
struct KeyMap
{
    KeyPair** pairs;
    ui32 count;

    boolean isInitialised;

    /**
     * @brief Adds an KeyPair to the array.
     * @return The Pointer onto the newly inserted KeyPair.
     */
    KeyPair* (*add)(KeyMap* self, KeyPair* pair);

    /**
     * @brief Removes a KeyPair from the array based on the index.
     * @return Returns the pointer onto the keymap is successful. If a error occured NULL is
     * returned.
     */
    void* (*remove_index)(KeyMap* self, ui32 index);

    /**
     * @brief Removes a KeyPair based on a string.
     * @return Returns the pointer onto the keymap is successful. If a error occured NULL is
     * returned.
     */
    void* (*remove_key)(KeyMap* self, const string* key);

    /**
     * @brief Removes a KeyPair based on a string.
     * @return Returns the pointer onto the keymap is successful. If a error occured NULL is
     * returned.
     */
    void* (*remove_key_cstr)(KeyMap* self, const char* key);

    /**
     * @brief Finds a KeyPair based on a string.
     * @return Returns the pointer onto the Keypair matching the passed in string.
     * If a error occured or the key was not found NULL is returned.
     */
    KeyPair* (*find)(KeyMap* self, const string* key);

    /**
     * @brief Finds a KeyPair based on a string.
     * @return Returns the pointer onto the Keypair matching the passed in string.
     * If a error occured or the key was not found NULL is returned.
     */
    KeyPair* (*find_cstr)(KeyMap* self, const char* key);

    /**
     * @brief Clear the entire KeyMap.
     * @return Returns nothing.
     */
    void (*clear)(KeyMap* self);

    /**
     * @brief Returns a pointer onto the KeyPair residing on the specified index.
     * The pointer can be motified as neede but it should be kept in mind that this is not a copy
     * it's the actual pointer residing within the array.
     * @return Returns the pointer onto the Keypair located on the passed in index.
     * If a error occured or the index is invalid NULL is returned.
     */
    KeyPair* (*at)(KeyMap* self, ui32 index);
};

/**
 * @brief Creates a new KeyMap initalized with all function pointers.
 * @return KeyMap*
 */
KeyMap* init_keyMap_heap();
/**
 * @brief Creates a new KeyMap initalized with all function pointers.
 * @return KeyMap
 */
KeyMap init_keyMap_stack();

#endif  // CUTILITY_KEYMAP_H