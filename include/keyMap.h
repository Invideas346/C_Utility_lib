//
// Created by wolfgang on 11.11.2021.
//

#ifndef CUTILITY_KEYMAP_H
#define CUTILITY_KEYMAP_H

#include <typedef.h>
#include <stringStruct.h>

typedef struct KeyPair KeyPair;
struct KeyPair{
    string key;
    size_t size;
    void* data;
};

KeyPair* init_keypair_heap(string* key, void* data, size_t size);
KeyPair init_keypair_stack(string* key, void* data, size_t size);

typedef struct KeyMap KeyMap;
struct KeyMap{
    KeyPair *pairs;
    ui32 count;

    boolean isInitialised;

    void (*add)(KeyMap* self, KeyPair* pair);
    void (*remove_index)(KeyMap* self, ui32 index);
    void (*remove_key)(KeyMap* self, string key);
    void (*remove_last)(KeyMap* self);

    void (*clear)(KeyMap* self);
};

KeyMap* init_keyMap_heap();
KeyMap init_keyMap_stack();

#endif  // CUTILITY_KEYMAP_H