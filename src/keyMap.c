//
// Created by wolfgang on 11.11.2021.
//

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <keyMap.h>

static void add(KeyMap* self, KeyPair* pair)
{
    assert(self->isInitialised == true);
    self->count++;
    if(self->count == 1)
    {
        self->pairs = malloc(self->count * sizeof(KeyPair));
    }
    else
    {
        self->pairs = realloc(self->pairs, self->count * sizeof(KeyPair));
    }
    self->pairs[self->count - 1] =
    memcpy(&self->pairs[self->count - 1], pair, sizeof(KeyPair));
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

static void clear(KeyMap* self)
{
    for(uint32_t i = 0; i < self->count; ++i)
    {
        self->pairs->key.clear(&self->pairs->key);
        free(self->pairs->data);
    }
    free(self->pairs);
}

static KeyMap* assign_methods(KeyMap* map)
{
    map->add = add;
    map->remove_index = remove_index;
    map->remove_key = remove_key;
    map->remove_last = remove_last;
    map->clear = clear;
    return map;
}

KeyMap* init_keyMap_heap()
{
    KeyMap* map = (KeyMap*)malloc(sizeof(KeyMap));
    map->count = 0;
    map = assign_methods(map);
    map->isInitialised = true;
    return map;
}

KeyMap init_keyMap_stack()
{
    KeyMap map;
    map.count = 0;
    assign_methods(&map);
    map.isInitialised = true;
    return map;
}

KeyPair* init_keypair_heap(string* key, void* data, size_t size)
{
    KeyPair* newKeyPair = (KeyPair*) malloc(sizeof(KeyPair));
    assert(newKeyPair != NULL);
    newKeyPair->size = size;
    newKeyPair->data = malloc(size);
    memcpy(newKeyPair->data, data, size);
    newKeyPair->key.size = key->size;
    newKeyPair->key.value = (char*)malloc(sizeof(key->size));
    memcpy(newKeyPair->key.value, key->value, key->size);
    return newKeyPair;
}

KeyPair init_keypair_stack(string* key, void* data, size_t size)
{
    KeyPair newKeyPair;
    newKeyPair.size = size;
    newKeyPair.data = malloc(size);
    memcpy(newKeyPair.data, data, size);
    newKeyPair.key.size = key->size;
    newKeyPair.key.value = (char*)malloc(sizeof(key->size));
    memcpy(newKeyPair.key.value, key->value, key->size);
    return newKeyPair;
}