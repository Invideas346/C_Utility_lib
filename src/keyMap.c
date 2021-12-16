//
// Created by wolfgang on 11.11.2021.
//

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <keyMap.h>

// TODO: Research whether 1 can be a valid pointer if not change the NULL to 0 or
// something like that
#define ASSERT_INIT(x) assert(x->isInitialised)

//! not tested yet
static ui32 find_index_keymap(KeyMap* self, const char* key)
{
    ASSERT_INIT(self);
    for(ui32 i = 0; i < self->count; i++)
    {
        if(self->at(self, i)->key.equal_cstr(&self->at(self, i)->key, key))
        {
            return i;
        }
    }
    return INDEX_NOTFOUND;
}

//! not tested yet
static KeyPair* add_keymap(KeyMap* self, KeyPair* pair)
{
    ASSERT_INIT(self);
    self->count++;
    if(self->count == 1)
    {
        self->pairs = (KeyPair**) malloc(self->count * sizeof(KeyPair*));
        if(self->pairs == NULL)
        {
            return NULL;
        }
    }
    else
    {
        self->pairs = (KeyPair**) realloc(self->pairs, self->count * sizeof(KeyPair*));
        if(self->pairs == NULL)
        {
            return NULL;
        }
    }
    self->pairs[self->count - 1] = init_keypair_heap(&pair->key, pair->data, pair->size);
    return self->pairs[self->count - 1];
}

//! not tested yet
static void* remove_index(KeyMap* self, ui32 index)
{
    ASSERT_INIT(self);
    if(self->count == 0)
    {
        return NULL;
    }
    KeyPair** pair = (KeyPair**) malloc(sizeof(KeyPair*) * self->count - 1);
    for(ui32 i = 0, k = 0; i < self->count; i++)
    {
        if(i != index)
        {
            pair[k] = self->pairs[i];
        }
        else
        {
            self->pairs[i]->clear(self->pairs[i]);
        }
    }
    void* newAddress = realloc(self->pairs, sizeof(KeyPair*) * self->count - 1);
    if(newAddress == NULL)
    {
        return NULL;
    }
    memcpy(self->pairs, pair, sizeof(KeyPair*) * self->count - 1);
    self->count--;
    return self->pairs;
}

//! not tested yet
static void* remove_key(KeyMap* self, const String* key)
{
    ASSERT_INIT(self);
    ui32 index = find_index_keymap(self, key->value);
    if(index == INDEX_NOTFOUND)
    {
        return NULL;
    }
    return self->remove_index(self, index);
}

//! not tested yet
static void clear_keymap(KeyMap* self)
{
    ASSERT_INIT(self);
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

//! not tested yet
static KeyPair* at(KeyMap* self, ui32 index)
{
    ASSERT_INIT(self);
    if(index >= self->count)
    {
        return NULL;
    }
    return self->pairs[index];
}

//! not tested yet
static void* remove_key_cstr(KeyMap* self, const char* key)
{
    ASSERT_INIT(self);
    ui32 index = find_index_keymap(self, key);
    if(index == INDEX_NOTFOUND)
    {
        return NULL;
    }
    return self->remove_index(self, index);
}

//! not tested yet
static KeyPair* find_cstr(KeyMap* self, const char* key)
{
    ASSERT_INIT(self);
    ui32 index = find_index_keymap(self, key);
    if(index == INDEX_NOTFOUND)
    {
        return NULL;
    }
    return self->at(self, index);
}

//! not tested yet
static KeyPair* find(KeyMap* self, const String* key)
{
    ASSERT_INIT(self);
    ui32 index = find_index_keymap(self, key->value);
    if(index == INDEX_NOTFOUND)
    {
        return NULL;
    }
    return self->at(self, index);
}

//! not tested yet
static KeyMap* copy_heap(KeyMap* self)
{
    ASSERT_INIT(self);
    KeyMap* copy = init_keyMap_heap();
    for(ui32 i = 0; i < self->count; i++)
    {
        copy->add(copy, self->at(self, i));
    }
    return copy;
}

//! not tested yet
static KeyMap copy_stack(KeyMap* self)
{
    ASSERT_INIT(self);
    KeyMap copy = init_keyMap_stack();
    for(ui32 i = 0; i < self->count; i++)
    {
        copy.add(&copy, self->at(self, i));
    }
    return copy;
}

static void assign_methods_keymap(KeyMap* map)
{
    map->add = add_keymap;
    map->remove_index = remove_index;
    map->remove_key = remove_key;
    map->clear = clear_keymap;
    map->at = at;
    map->remove_key_cstr = remove_key_cstr;
    map->find_cstr = find_cstr;
    map->find = find;
    map->copy_heap = copy_heap;
    map->copy_stack = copy_stack;
}

KeyMap* init_keyMap_heap()
{
    KeyMap* map = (KeyMap*) malloc(sizeof(KeyMap));
    map->count = 0;
    assign_methods_keymap(map);
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
    assert(pair->isInitialised == true);
    pair->key.clear(&pair->key);
    free(pair->data);
}

static KeyPair* assign_methods_keypair(KeyPair* pair)
{
    pair->clear = clear_keypair;
    return pair;
}

KeyPair* init_keypair_heap(String* key, void* data, size_t size)
{
    KeyPair* newKeyPair = (KeyPair*) malloc(sizeof(KeyPair));
    if(newKeyPair == NULL)
    {
        return NULL;
    }
    newKeyPair->size = size;
    newKeyPair->data = malloc(size);
    memcpy(newKeyPair->data, data, size);
    newKeyPair->key = init_string_stack(key->value);
    assign_methods_keypair(newKeyPair);
    newKeyPair->isInitialised = true;
    return newKeyPair;
}

KeyPair* init_keypair_heap_cstr(const char* key, void* data, size_t size)
{
    KeyPair* newKeyPair = (KeyPair*) malloc(sizeof(KeyPair));
    if(newKeyPair == NULL)
    {
        return NULL;
    }
    newKeyPair->size = size;
    newKeyPair->data = malloc(size);
    if(newKeyPair->data == NULL)
    {
        return NULL;
    }
    memcpy(newKeyPair->data, data, size);
    newKeyPair->key = init_string_stack(key);
    assign_methods_keypair(newKeyPair);
    newKeyPair->isInitialised = true;
    return newKeyPair;
}

KeyPair init_keypair_stack(String* key, void* data, size_t size)
{
    KeyPair newKeyPair;
    newKeyPair.size = size;
    newKeyPair.data = malloc(size);
    if(newKeyPair.data == NULL)
    {
        return newKeyPair;
    }
    memcpy(newKeyPair.data, data, size);
    newKeyPair.key = init_string_stack(key->value);
    assign_methods_keypair(&newKeyPair);
    newKeyPair.isInitialised = true;
    return newKeyPair;
}

KeyPair init_keypair_stack_cstr(const char* key, void* data, size_t size)
{
    KeyPair newKeyPair;
    newKeyPair.size = size;
    newKeyPair.data = malloc(size);
    if(newKeyPair.data == NULL)
    {
        return newKeyPair;
    }
    memcpy(newKeyPair.data, data, size);
    newKeyPair.key = init_string_stack(key);
    assign_methods_keypair(&newKeyPair);
    newKeyPair.isInitialised = true;
    return newKeyPair;
}