//
// Created by wolfgang on 11.11.2021.
//

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <keyMap.h>

static void add_keymap(KeyMap* self, KeyPair* pair)
{
    assert(self->isInitialised == true);
    self->count++;
    if(self->count == 1)
    {
        self->pairs = (KeyPair**)malloc(self->count * sizeof(KeyPair*));
    }
    else
    {
        self->pairs = (KeyPair**)realloc(self->pairs, self->count * sizeof(KeyPair*));
    }
    self->pairs[self->count - 1] = init_keypair_heap(&pair->key, pair->data, pair->size);
}

static void remove_index(KeyMap* self, ui32 index)
{
    assert(self->isInitialised == true);
}

static void remove_key(KeyMap* self, string key)
{
    assert(self->isInitialised == true);
}

static void remove_last(KeyMap* self)
{
    assert(self->isInitialised == true);
}

static void clear_keymap(KeyMap* self)
{
    for(ui32 i = 0; i < self->count; ++i)
    {
        KeyPair* pair = *self->pairs;
        pair->key.clear(&pair->key);
        free(pair->data);
        free(pair);
    }
    free(self->pairs);
    self->count = 0;
}


static KeyPair* at (KeyMap* self, ui32 index)
{
    assert(self->isInitialised == true);
    KeyPair* pair = self->pairs[index];
    return pair;
}

static KeyMap* assign_methods_keymap(KeyMap* map)
{
    map->add = add_keymap;
    map->remove_index = remove_index;
    map->remove_key = remove_key;
    map->remove_last = remove_last;
    map->clear = clear_keymap;
    map->at = at;
    return map;
}

KeyMap* init_keyMap_heap()
{
    KeyMap* map = (KeyMap*)malloc(sizeof(KeyMap));
    map->count = 0;
    map = assign_methods_keymap(map);
    map->isInitialised = true;
    return map;
}

KeyMap init_keyMap_stack()
{
    KeyMap map;
    map.count = 0;
    assign_methods_keymap(&map);
    map.isInitialised = true;
    return map;
}

static void clear_keypair(KeyPair* pair)
{
    pair->key.clear(&pair->key);
    free(pair->data);
}

static KeyPair* assign_methods_keypair(KeyPair* pair)
{
    pair->clear = clear_keypair;
    return pair;
}

KeyPair* init_keypair_heap(string* key, void* data, size_t size)
{
    KeyPair* newKeyPair = (KeyPair*) malloc(sizeof(KeyPair));
    assert(newKeyPair != NULL);
    newKeyPair->size = size;
    newKeyPair->data = malloc(size);
    memcpy(newKeyPair->data, data, size);
    newKeyPair->key = init_string_stack(key->value);
    assign_methods_keypair(newKeyPair);
    return newKeyPair;
}

KeyPair* init_keypair_heap_cstr(const char* key, void* data, size_t size)
{
    KeyPair* newKeyPair = (KeyPair*) malloc(sizeof(KeyPair));
    assert(newKeyPair != NULL);
    newKeyPair->size = size;
    newKeyPair->data = malloc(size);
    memcpy(newKeyPair->data, data, size);
    newKeyPair->key = init_string_stack(key);
    assign_methods_keypair(newKeyPair);
    return newKeyPair;
}

KeyPair init_keypair_stack(string* key, void* data, size_t size)
{
    KeyPair newKeyPair;
    newKeyPair.size = size;
    newKeyPair.data = malloc(size);
    memcpy(newKeyPair.data, data, size);
    newKeyPair.key = init_string_stack(key->value);
    assign_methods_keypair(&newKeyPair);
    return newKeyPair;
}

KeyPair init_keypair_stack_cstr(const char* key, void* data, size_t size)
{
    KeyPair newKeyPair;
    newKeyPair.size = size;
    newKeyPair.data = malloc(size);
    memcpy(newKeyPair.data, data, size);
    newKeyPair.key = init_string_stack(key);
    assign_methods_keypair(&newKeyPair);
    return newKeyPair;
}