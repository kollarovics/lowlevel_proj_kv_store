#include "../inc/kv.h"
#include <stdlib.h>
#include <stdio.h>

kv_t  *kv_init(size_t capacity) {
    if (capacity == 0) {
        perror("Capacity must be greater than zero");
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