#import <stdio.h>
#import "../inc/kv.h"

int main(void) {
    kv_t* db = kv_init(16);
    size_t idx = kv_put(db, "color", "red");
    printf("idx: %zu\n", idx);
    idx = kv_put(db, "color", "blue");
    printf("idx: %zu\n", idx);
    idx = kv_put(db, "velem", "KKv1kksjjd");
    printf("idx: %zu\n", idx);
    return 0;
}