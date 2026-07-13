#import <stdio.h>
#import "../inc/kv.h"

int main(void) {
    kv_t* db = kv_init(1024);
    size_t idx = kv_put(db, "key1", "value1");
    printf("idx: %zu\n", idx);
    idx = kv_put(db, "2key2", "Tvalue1");
    printf("idx: %zu\n", idx);
    idx = kv_put(db, "traktors", "KKv1kksjjd");
    printf("idx: %zu\n", idx);
    return 0;
}