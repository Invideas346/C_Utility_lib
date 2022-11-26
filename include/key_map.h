//
// Created by wolfgang on 11.11.2021.
//

#ifndef __CUTILITY_KEYMAP_H__
#define __CUTILITY_KEYMAP_H__

#include "string_struct.h"

/**
 * @brief Enum which represents every possible error which can occure with keypairs.
 */
typedef enum KEYPAIR_ERROR_CODE {
    KEYPAIR_OK = 0,
    KEYPAIR_GENERAL_ERROR = 1,
    KEYPAIR_NOT_INITIALIZED = 2 | KEYPAIR_GENERAL_ERROR,
    KEYPAIR_MEMORY_ALLOCATION_ERROR = 3 | KEYPAIR_GENERAL_ERROR
} KEYPAIR_ERROR_CODE;

/**
 * @brief This struct represents a Keypair. A keypair is used in a so-called keymap and matches
 * a string with a value (data type can be arbitrarly).
 */
typedef struct KeyPair {
    String key;
    size_t size;
    void* data;

    uint8_t is_initialized;

    /**
     * @brief Clear a KeyPair and effecticly frees all allocated memory.
     */
    void (*clear)(KeyPair* pair, KEYPAIR_ERROR_CODE* error_code);
} KeyPair;

/**
 * @brief Creates a new KeyPair initalized with all function pointers.
 * @return KeyMap*
 */
KeyPair* init_keypair_heap(String* key, void* data, size_t size, KEYPAIR_ERROR_CODE* error_code);
/**
 * @brief Creates a new KeyPair initalized with all function pointers.
 * @return KeyMap
 */
KeyPair init_keypair_stack(String* key, void* data, size_t size, KEYPAIR_ERROR_CODE* error_code);

/**
 * @brief Creates a new KeyPair initalized with all function pointers.
 * @return KeyMap*
 */
KeyPair* init_keypair_heap_cstr(const char* key, void* data, size_t size,
                                KEYPAIR_ERROR_CODE* error_code);
/**
 * @brief Creates a new KeyMap initalized with all function pointers.
 * @return KeyMap
 */
KeyPair init_keypair_stack_cstr(const char* key, void* data, size_t size,
                                KEYPAIR_ERROR_CODE* error_code);

/**
 * @brief Enum which represents every possible error which can occure with keymaps.
 */
typedef enum KEYMAP_ERROR_CODE {
    KEYMAP_OK = 0,
    KEYMAP_GENERAL_ERROR = 1,
    KEYMAP_NOT_INITIALIZED = 2 | KEYPAIR_GENERAL_ERROR,
    KEYMAP_MEMORY_ALLOCATION_ERROR = 3 | KEYMAP_GENERAL_ERROR,
    KEYMAP_PAIR_NOT_FOUND = 4 | KEYMAP_GENERAL_ERROR
} KEYMAP_ERROR_CODE;

/**
 * @brief This struct represensts a keymap which is a collection of keypairs.
 */
typedef struct KeyMap {
    KeyPair** pairs;
    uint32_t length;

    uint8_t is_initialized;

    /**
     * @brief Adds an KeyPair to the array.
     * @return The Pointer onto the newly inserted KeyPair.
     */
    KeyPair* (*add)(KeyMap* self, KeyPair* pair, KEYMAP_ERROR_CODE* error_code);

    /**
     * @brief Removes a KeyPair from the array based on the index.
     * @return Returns the pointer onto the keymap is successful. If an error occured NULL is
     * returned.
     */
    void* (*remove_index)(KeyMap* self, uint32_t index, KEYMAP_ERROR_CODE* error_code);

    /**
     * @brief Removes a KeyPair based on a string.
     * @return Returns the pointer onto the keymap is successful. If an error occured NULL is
     * returned.
     */
    void* (*remove_key)(KeyMap* self, const String* key, KEYMAP_ERROR_CODE* error_code);

    /**
     * @brief Removes a KeyPair based on a string.
     * @return Returns the pointer onto the keymap is successful. If an error occured NULL is
     * returned.
     */
    void* (*remove_key_cstr)(KeyMap* self, const char* key, KEYMAP_ERROR_CODE* error_code);

    /**
     * @brief Finds a KeyPair based on a string.
     * @return Returns the pointer onto the Keypair matching the passed in string.
     * If an error occured or the key was not found NULL is returned.
     */
    KeyPair* (*find)(KeyMap* self, const String* key, KEYMAP_ERROR_CODE* error_code);

    /**
     * @brief Finds a KeyPair based on a string.
     * @return Returns the pointer onto the Keypair matching the passed in string.
     * If an error occured or the key was not found NULL is returned.
     */
    KeyPair* (*find_cstr)(KeyMap* self, const char* key, KEYMAP_ERROR_CODE* error_code);

    /**
     * @brief Clear the entire KeyMap.
     * @return Returns nothing.
     */
    void (*clear)(KeyMap* self, KEYMAP_ERROR_CODE* error_code);

    /**
     * @brief Returns a pointer onto the KeyPair residing on the specified index.
     * The pointer can be motified as neede but it should be kept in mind that this is not a copy
     * it's the actual pointer residing within the array.
     * @return Returns the pointer onto the Keypair located on the passed in index.
     * If an error occured or the index is invalid NULL is returned.
     */
    KeyPair* (*at)(KeyMap* self, uint32_t index, KEYMAP_ERROR_CODE* error_code);

    /**
     * @brief Creates a copy of itself.
     */
    KeyMap* (*copy_heap)(KeyMap* self, KEYMAP_ERROR_CODE* error_code);
    /**
     * @brief Creates a copy of itself.
     */
    KeyMap (*copy_stack)(KeyMap* self, KEYMAP_ERROR_CODE* error_code);
} KeyMap;

/**
 * @brief Creates a new KeyMap initalized with all function pointers.
 * @return KeyMap*
 */
KeyMap* init_keyMap_heap(KEYMAP_ERROR_CODE* error_code);
/**
 * @brief Creates a new KeyMap initalized with all function pointers.
 * @return KeyMap
 */
KeyMap init_keyMap_stack(KEYMAP_ERROR_CODE* error_code);

#endif  // __CUTILITY_KEYMAP_H__