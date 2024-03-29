//
// Created by wolfgang on 11.11.2021.
//

#include <stdlib.h>
#include <string.h>
#include <key_map.h>
#include <typedef.h>
#include <log.h>

static inline void assign_error_code_keypair(KEYPAIR_ERROR_CODE* error_code,
                                             KEYPAIR_ERROR_CODE value)
{
    if(error_code != NULL) *error_code = value;
}

static inline void assign_error_code_keymap(KEYMAP_ERROR_CODE* error_code, KEYMAP_ERROR_CODE value)
{
    if(error_code != NULL) *error_code = value;
}

static uint32_t find_index_keymap(KeyMap* self, const char* key, KEYMAP_ERROR_CODE* error_code)
{
    if(!self->is_initialized) {
        assign_error_code_keymap(error_code, KEYMAP_NOT_INITIALIZED);
        LOG_WARNING("Keymap not intialized");
        return INDEX_NOTFOUND;
    }
    STRING_ERROR_CODE code;
    for(uint32_t i = 0; i < self->length; i++) {
        if(self->at(self, i, error_code)
               ->key.equal_cstr(&self->at(self, i, error_code)->key, key, &code)) {
            return i;
        }
    }
    assign_error_code_keymap(error_code, KEYMAP_OK);
    LOG_INFO("Index not found");
    return INDEX_NOTFOUND;
}

static KeyPair* add_keymap(KeyMap* self, KeyPair* pair, KEYMAP_ERROR_CODE* error_code)
{
    if(!self->is_initialized) {
        assign_error_code_keymap(error_code, KEYMAP_NOT_INITIALIZED);
        LOG_WARNING("Keymap not intialized");
        return (KeyPair*) INDEX_NOTFOUND;
    }
    if(!self->is_initialized) {
        assign_error_code_keymap(error_code, KEYMAP_NOT_INITIALIZED);
        LOG_WARNING("Keymap not intialized");
        return (KeyPair*) INDEX_NOTFOUND;
    }
    self->length++;
    if(self->length == 1) {
        self->pairs = (KeyPair**) malloc(self->length * sizeof(KeyPair*));
        if(self->pairs == NULL) {
            assign_error_code_keymap(error_code, KEYMAP_MEMORY_ALLOCATION_ERROR);
            LOG_ERROR("Could not allocate memory for keymap");
            return NULL;
        }
    }
    else {
        self->pairs = (KeyPair**) realloc(self->pairs, self->length * sizeof(KeyPair*));
        if(self->pairs == NULL) {
            assign_error_code_keymap(error_code, KEYMAP_MEMORY_ALLOCATION_ERROR);
            LOG_ERROR("Could not allocate memory for keymap");
            return NULL;
        }
    }
    KEYPAIR_ERROR_CODE ec;
    self->pairs[self->length - 1] = init_keypair_heap(&pair->key, pair->data, pair->size, &ec);
    if(ec == KEYPAIR_GENERAL_ERROR) {
        assign_error_code_keymap(error_code, KEYMAP_GENERAL_ERROR);
        LOG_ERROR("Keymap general error");
        return NULL;
    }
    assign_error_code_keymap(error_code, KEYMAP_OK);
    return self->pairs[self->length - 1];
}

static void* remove_index(KeyMap* self, uint32_t index, KEYMAP_ERROR_CODE* error_code)
{
    if(!self->is_initialized) {
        assign_error_code_keymap(error_code, KEYMAP_NOT_INITIALIZED);
        LOG_WARNING("Keymap not intialized");
        return NULL;
    }
    if(self->length == 0) {
        return NULL;
    }
    KeyPair** pair = (KeyPair**) malloc(sizeof(KeyPair*) * self->length - 1);
    if(pair == NULL) {
        assign_error_code_keymap(error_code, KEYMAP_MEMORY_ALLOCATION_ERROR);
        LOG_ERROR("Could not allocate memory for keymap");
        return NULL;
    }
    for(uint32_t i = 0, k = 0; i < self->length; i++) {
        if(i != index) {
            pair[k] = self->pairs[i];
            k++;  //! Should be examined whether k should really be incremented
        }
        else {
            self->pairs[i]->clear(self->pairs[i], NULL);
        }
    }
    void* new_address = realloc(self->pairs, sizeof(KeyPair*) * self->length - 1);
    if(new_address == NULL) {
        assign_error_code_keymap(error_code, KEYMAP_MEMORY_ALLOCATION_ERROR);
        LOG_ERROR("Could not allocate memory for keymap");
        return NULL;
    }
    memcpy(self->pairs, pair, sizeof(KeyPair*) * self->length - 1);
    self->length--;
    assign_error_code_keymap(error_code, KEYMAP_OK);
    return self->pairs;
}

static void* remove_key(KeyMap* self, const String* key, KEYMAP_ERROR_CODE* error_code)
{
    if(!self->is_initialized || !key->is_initialized) {
        assign_error_code_keymap(error_code, KEYMAP_NOT_INITIALIZED);
        LOG_WARNING("Keymap not intialized");
        return NULL;
    }
    uint32_t index = find_index_keymap(self, key->value, error_code);
    if(index == INDEX_NOTFOUND) {
        assign_error_code_keymap(error_code, KEYMAP_PAIR_NOT_FOUND);
        LOG_INFO("Could not find keymap pair");
        return NULL;
    }
    return self->remove_index(self, index, error_code);
}

static void clear_keymap(KeyMap* self, KEYMAP_ERROR_CODE* error_code)
{
    if(!self->is_initialized) {
        assign_error_code_keymap(error_code, KEYMAP_NOT_INITIALIZED);
        LOG_WARNING("Keymap not intialized");
        return;
    }
    STRING_ERROR_CODE code;
    for(uint32_t i = 0; i < self->length; ++i) {
        KeyPair* pair = self->pairs[i];
        pair->key.clear(&pair->key, &code);
        if(code != KEYMAP_OK) {
            assign_error_code_keymap(error_code, KEYMAP_GENERAL_ERROR);
            LOG_ERROR("Keymap general error");
            return;
        }
        free(pair->data);
        free(pair);
    }
    free(self->pairs);
    self->length = 0;
    assign_error_code_keymap(error_code, KEYMAP_OK);
}

static KeyPair* at(KeyMap* self, uint32_t index, KEYMAP_ERROR_CODE* error_code)
{
    if(!self->is_initialized) {
        assign_error_code_keymap(error_code, KEYMAP_NOT_INITIALIZED);
        LOG_WARNING("Keymap not intialized");
        return NULL;
    }
    if(index >= self->length) {
        LOG_WARNING("Index out-of-bounds");
        return NULL;
    }
    assign_error_code_keymap(error_code, KEYMAP_OK);
    return self->pairs[index];
}

static void* remove_key_cstr(KeyMap* self, const char* key, KEYMAP_ERROR_CODE* error_code)
{
    if(!self->is_initialized) {
        assign_error_code_keymap(error_code, KEYMAP_NOT_INITIALIZED);
        LOG_ERROR("Keymap not intialized");
        return NULL;
    }
    uint32_t index = find_index_keymap(self, key, error_code);
    if(index == INDEX_NOTFOUND) {
        LOG_INFO("Keypair not found");
        return NULL;
    }
    return self->remove_index(self, index, error_code);
}

static KeyPair* find_cstr(KeyMap* self, const char* key, KEYMAP_ERROR_CODE* error_code)
{
    if(!self->is_initialized) {
        assign_error_code_keymap(error_code, KEYMAP_NOT_INITIALIZED);
        LOG_ERROR("Keymap not intialized");
        return NULL;
    }
    uint32_t index = find_index_keymap(self, key, error_code);
    if(index == INDEX_NOTFOUND) {
        LOG_INFO("Keypair not found");
        return NULL;
    }
    return self->at(self, index, error_code);
}

static KeyPair* find(KeyMap* self, const String* key, KEYMAP_ERROR_CODE* error_code)
{
    if(!self->is_initialized || !key->is_initialized) {
        assign_error_code_keymap(error_code, KEYMAP_NOT_INITIALIZED);
        LOG_WARNING("Keymap not intialized");
        return NULL;
    }
    uint32_t index = find_index_keymap(self, key->value, error_code);
    if(index == INDEX_NOTFOUND) {
        LOG_INFO("Keypair not found");
        return NULL;
    }
    return self->at(self, index, error_code);
}

static KeyMap* copy_heap(KeyMap* self, KEYMAP_ERROR_CODE* error_code)
{
    if(!self->is_initialized) {
        assign_error_code_keymap(error_code, KEYMAP_NOT_INITIALIZED);
        LOG_WARNING("Keymap not intialized");
        return NULL;
    }
    KeyMap* copy = init_keyMap_heap(error_code);
    for(uint32_t i = 0; i < self->length; i++) {
        KeyPair* pair = self->at(self, i, error_code);
        if(error_code != KEYMAP_OK) {
            return NULL;
        }
        copy->add(copy, pair, error_code);
    }
    return copy;
}

static KeyMap copy_stack(KeyMap* self, KEYMAP_ERROR_CODE* error_code)
{
    if(!self->is_initialized) {
        assign_error_code_keymap(error_code, KEYMAP_NOT_INITIALIZED);
        LOG_WARNING("Keymap not intialized");
        return init_keyMap_stack(NULL);
    }
    KeyMap copy = init_keyMap_stack(error_code);
    for(uint32_t i = 0; i < self->length; i++) {
        KeyPair* pair = self->at(self, i, error_code);
        if(*error_code != KEYMAP_OK) {
            return init_keyMap_stack(NULL);
        }
        copy.add(&copy, pair, error_code);
    }
    return copy;
}

inline static void assign_methods_keymap(KeyMap* map)
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

KeyMap* init_keyMap_heap(KEYMAP_ERROR_CODE* error_code)
{
    KeyMap* map = (KeyMap*) malloc(sizeof(KeyMap));
    if(map == NULL) {
        assign_error_code_keymap(error_code, KEYMAP_MEMORY_ALLOCATION_ERROR);
        LOG_ERROR("Could not allocate memory for keymap");
        return NULL;
    }
    map->length = 0;
    assign_methods_keymap(map);
    map->is_initialized = TRUE;
    assign_error_code_keymap(error_code, KEYMAP_OK);
    return map;
}

KeyMap init_keyMap_stack(KEYMAP_ERROR_CODE* error_code)
{
    KeyMap map;
    map.length = 0;
    assign_methods_keymap(&map);
    map.is_initialized = TRUE;
    assign_error_code_keymap(error_code, KEYMAP_OK);
    return map;
}

static void clear_keypair(KeyPair* pair, KEYPAIR_ERROR_CODE* error_code)
{
    if(!pair->is_initialized) {
        assign_error_code_keypair(error_code, KEYPAIR_NOT_INITIALIZED);
        LOG_ERROR("Keypair is not ilitialized");
        return;
    }
    STRING_ERROR_CODE code;
    pair->key.clear(&pair->key, &code);
    free(pair->data);
}

inline static KeyPair* assign_methods_keypair(KeyPair* pair)
{
    pair->clear = clear_keypair;
    return pair;
}

KeyPair* init_keypair_heap(String* key, void* data, size_t size, KEYPAIR_ERROR_CODE* error_code)
{
    if(!key->is_initialized) {
        assign_error_code_keypair(error_code, KEYPAIR_NOT_INITIALIZED);
        LOG_ERROR("Key string not initialized");
        return NULL;
    }
    KeyPair* new_key_pair = (KeyPair*) malloc(sizeof(KeyPair));
    if(new_key_pair == NULL) {
        assign_error_code_keypair(error_code, KEYPAIR_MEMORY_ALLOCATION_ERROR);
        LOG_ERROR("Could not allocate memory for keypair");
        return NULL;
    }
    new_key_pair->size = size;
    new_key_pair->data = malloc(size);
    memcpy(new_key_pair->data, data, size);
    STRING_ERROR_CODE code;
    new_key_pair->key = key->copy_stack(key, &code);
    assign_methods_keypair(new_key_pair);
    new_key_pair->is_initialized = TRUE;
    assign_error_code_keypair(error_code, KEYPAIR_OK);
    return new_key_pair;
}

KeyPair* init_keypair_heap_cstr(const char* key, void* data, size_t size,
                                KEYPAIR_ERROR_CODE* error_code)
{
    KeyPair* new_key_pair = (KeyPair*) malloc(sizeof(KeyPair));
    if(new_key_pair == NULL) {
        assign_error_code_keypair(error_code, KEYPAIR_MEMORY_ALLOCATION_ERROR);
        LOG_ERROR("Could not allocate memory for keypair");
        return NULL;
    }
    new_key_pair->size = size;
    new_key_pair->data = malloc(size);
    if(new_key_pair->data == NULL) {
        assign_error_code_keypair(error_code, KEYPAIR_MEMORY_ALLOCATION_ERROR);
        LOG_ERROR("Could not allocate memory for keypair");
        return NULL;
    }
    memcpy(new_key_pair->data, data, size);
    STRING_ERROR_CODE code;
    new_key_pair->key = init_string_stack(key, &code);
    assign_methods_keypair(new_key_pair);
    new_key_pair->is_initialized = TRUE;
    assign_error_code_keypair(error_code, KEYPAIR_OK);
    return new_key_pair;
}

KeyPair init_keypair_stack(String* key, void* data, size_t size, KEYPAIR_ERROR_CODE* error_code)
{
    KeyPair new_key_pair;
    if(!key->is_initialized) {
        assign_error_code_keypair(error_code, KEYPAIR_GENERAL_ERROR);
        LOG_ERROR("Key string not initialized");
        return new_key_pair;
    }
    new_key_pair.size = size;
    new_key_pair.data = malloc(size);
    if(new_key_pair.data == NULL) {
        assign_error_code_keypair(error_code, KEYPAIR_MEMORY_ALLOCATION_ERROR);
        LOG_ERROR("Could not allocate memory for keypair");
        return new_key_pair;
    }
    memcpy(new_key_pair.data, data, size);
    STRING_ERROR_CODE code;
    new_key_pair.key = key->copy_stack(key, &code);
    assign_methods_keypair(&new_key_pair);
    new_key_pair.is_initialized = TRUE;
    assign_error_code_keypair(error_code, KEYPAIR_OK);
    return new_key_pair;
}

KeyPair init_keypair_stack_cstr(const char* key, void* data, size_t size,
                                KEYPAIR_ERROR_CODE* error_code)
{
    KeyPair new_key_pair;
    new_key_pair.size = size;
    new_key_pair.data = malloc(size);
    if(new_key_pair.data == NULL) {
        assign_error_code_keypair(error_code, KEYPAIR_MEMORY_ALLOCATION_ERROR);
        LOG_ERROR("Could not allocate memory for keypair");
        return new_key_pair;
    }
    memcpy(new_key_pair.data, data, size);
    STRING_ERROR_CODE code;
    new_key_pair.key = init_string_stack(key, &code);
    assign_methods_keypair(&new_key_pair);
    new_key_pair.is_initialized = TRUE;
    assign_error_code_keypair(error_code, KEYPAIR_OK);
    return new_key_pair;
}