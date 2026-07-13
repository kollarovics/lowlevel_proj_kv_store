#include "../inc/kv.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

kv_t  *kv_init(size_t capacity) {
    if (capacity <= 1) {
        perror("Capacity must be greater than one");
        return NULL;
    }
    kv_t *db = malloc(sizeof(kv_t));
    if (db == NULL) {
        perror("Malloc failed");
        return NULL;
    }
    db->capacity = capacity;
    db->count = 0;
   if ( (db->entries = calloc(capacity, sizeof(kv_entry_t))) == NULL) {
       perror("Calloc failed");
       free(db);
       return NULL;
   }
    return db;
}

size_t hash(char* key, size_t capacity) {
    size_t hash = 0x13811c9dc5beafa;

    while (*key) {
        hash ^= *key;
        hash = hash << 8;
        hash += *key;
        key++;
    }

    return hash % capacity;
}

int  kv_put(kv_t *db, char *key, char *value) {
    if (!db || !key || !value) {
        perror("Incorrect db, key or val");
        return -1;
    }
    size_t idx = hash((char*)key, db->capacity);
    for (int i = 0; i < db->capacity -1; i++) {
        size_t real_idx = (idx + i) % db->capacity;
        printf("Calculated idx: %zu\n", real_idx);
        kv_entry_t *entry = &db->entries[real_idx];
        //existing key
        if (entry->key && entry->key != (void*)TOMBSTONE &&!strcmp(entry->key, key)) {
            char *new_val = strdup(value);
            if (!new_val) {
                perror("Strdup failed");
                free(new_val);
                return -1;
            }
            free(entry->value);
            entry->value = new_val;
            if (real_idx == 0) real_idx++;
            return real_idx;
        }
        //empty or deleted key
        if (!entry->key || entry->key == (void*)TOMBSTONE) {
            char *new_key = strdup(key);
            char *new_val = strdup(value);
            if (!new_val || !new_key) {
                perror("Strdup failed");
                free(new_key);
                free(new_val);
                return -1;
            }
            free(entry->key);
            free(entry->value);
            entry->key = new_key;
            entry->value = new_val;
            db->count++;
            return real_idx;
        }

    }

    // db full
    return -2;
}