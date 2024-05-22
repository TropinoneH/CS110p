#include "cache.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>

/* Create a cache simulator according to the config */
struct cache *cache_create(struct cache_config config, struct cache *lower_level) {
    /*YOUR CODE HERE*/
    struct cache *c = (struct cache *)malloc(sizeof(struct cache));
    c->config = config;
    return c;
}

/* 
Release the resources allocated for the cache simulator. 
Also, writeback dirty lines

The order in which lines are evicted is:
set0-slot0, set1-slot0, set2-slot0, (the 0th way)
set0-slot1, set1-slot1, set2-slot1, (the 1st way)
set0-slot2, set1-slot2, set2-slot2, (the 2nd way)
and so on.
*/
void cache_destroy(struct cache *cache) {
    /*YOUR CODE HERE*/
}

/* Read one byte at a specific address. return hit=true/miss=false */
bool cache_read_byte(struct cache *cache, uint32_t addr, uint8_t *byte) {
    /*YOUR CODE HERE*/
}
/* Write one byte into a specific address. return hit=true/miss=false*/
bool cache_write_byte(struct cache *cache, uint32_t addr, uint8_t byte) {
    /*YOUR CODE HERE*/
}
