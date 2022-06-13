//
// Created by wolfgang on 11.11.2021.
//

#ifndef __CUTILITY_KEYMAP_H__
#define __CUTILITY_KEYMAP_H__

#include <typedef.h>
#include <stringStruct.h>

typedef struct KeyPair KeyPair;
struct KeyPair {
    String key;
    size_t size;
    void* data;

    boolean is_initialized;

    /**
     * @brief Clear a KeyPair and effecticly frees all allocated memory.
     */
    void (*clear)(KeyPair* pair);
};

/**
 * @brief Creates a new KeyPair initalized with all function pointers.
 * @return KeyMap*
 */
KeyPair* init_keypair_heap(String* key, void* data, size_t size);
/**
 * @brief Creates a new KeyPair initalized with all function pointers.
 * @return KeyMap
 */
KeyPair init_keypair_stack(String* key, void* data, size_t size);

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
struct KeyMap {
    KeyPair** pairs;
    ui32 length;

    boolean is_initialized;

    /**
     * @brief Adds an KeyPair to the array.
     * @return The Pointer onto the newly inserted KeyPair.
     */
    KeyPair* (*add)(KeyMap* self, KeyPair* pair);

    /**
     * @brief Removes a KeyPair from the array based on the index.
     * @return Returns the pointer onto the keymap is successful. If an error occured NULL is
     * returned.
     */
    void* (*remove_index)(KeyMap* self, ui32 index);

    /**
     * @brief Removes a KeyPair based on a string.
     * @return Returns the pointer onto the keymap is successful. If an error occured NULL is
     * returned.
     */
    void* (*remove_key)(KeyMap* self, const String* key);

    /**
     * @brief Removes a KeyPair based on a string.
     * @return Returns the pointer onto the keymap is successful. If an error occured NULL is
     * returned.
     */
    void* (*remove_key_cstr)(KeyMap* self, const char* key);

    /**
     * @brief Finds a KeyPair based on a string.
     * @return Returns the pointer onto the Keypair matching the passed in string.
     * If an error occured or the key was not found NULL is returned.
     */
    KeyPair* (*find)(KeyMap* self, const String* key);

    /**
     * @brief Finds a KeyPair based on a string.
     * @return Returns the pointer onto the Keypair matching the passed in string.
     * If an error occured or the key was not found NULL is returned.
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
     * If an error occured or the index is invalid NULL is returned.
     */
    KeyPair* (*at)(KeyMap* self, ui32 index);

    /**
     * @brief Creates a copy of itself.
     */
    KeyMap* (*copy_heap)(KeyMap* self);
    /**
     * @brief Creates a copy of itself.
     */
    KeyMap (*copy_stack)(KeyMap* self);
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

#endif  // __CUTILITY_KEYMAP_H__