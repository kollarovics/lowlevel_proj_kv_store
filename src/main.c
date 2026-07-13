#import <stdio.h>
#import "../inc/kv.h"

int main(void) {
    kv_t* db = kv_init(16);
    size_t idx = kv_put(db, "color", "red");
    printf("idx: %zu\n", idx);
    kv_delete(db, "color");
    idx = kv_put(db, "color", "grey");
    printf("idx: %zu\n", idx);
    return 0;
}