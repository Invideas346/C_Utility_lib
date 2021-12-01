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

    void (*clear)(KeyPair* pair);
};

KeyPair* init_keypair_heap(string* key, void* data, size_t size);
KeyPair init_keypair_stack(string* key, void* data, size_t size);

typedef struct KeyMap KeyMap;
struct KeyMap
{
    KeyPair** pairs;
    ui32 count;

    boolean isInitialised;

    KeyPair* (*add)(KeyMap* self, KeyPair* pair);
    void* (*remove_index)(KeyMap* self, ui32 index);
    void* (*remove_key)(KeyMap* self, const string* key);
    void* (*remove_key_cstr)(KeyMap* self, const char* key);
    KeyPair* (*find)(KeyMap* self, const string* key);
    KeyPair* (*find_cstr)(KeyMap* self, const char* key);

    void (*clear)(KeyMap* self);
    KeyPair* (*at)(KeyMap* self, ui32 index);
};

KeyMap* init_keyMap_heap();
KeyMap init_keyMap_stack();

KeyPair* init_keypair_heap_cstr(const char* key, void* data, size_t size);
KeyPair init_keypair_stack_cstr(const char* key, void* data, size_t size);

#endif  // CUTILITY_KEYMAP_H