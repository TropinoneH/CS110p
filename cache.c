#include "cache.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

/* Create a cache simulator according to the config */
struct cache *cache_create(struct cache_config config, struct cache *lower_level) {
    /*YOUR CODE HERE*/
    struct cache *c = (struct cache *) malloc(sizeof(struct cache));
    c->config = config;
    c->lower_cache = lower_level;

    c->offset_bits = (uint32_t) round(log2(c->config.line_size));
    c->index_bits = (uint32_t) round(log2((double) c->config.lines / c->config.ways));
    c->tag_bits = config.address_bits - c->offset_bits - c->index_bits;

    c->offset_mask = (1 << c->offset_bits) - 1;
    c->index_mask = ((1 << c->index_bits) - 1) << c->offset_bits;
    c->tag_mask = ((1 << c->tag_bits) - 1) << (c->offset_bits + c->index_bits);

    c->lines = (struct cache_line *) malloc(sizeof(struct cache_line) * c->config.lines);
    for (uint32_t i = 0; i < c->config.lines; ++i) {
        c->lines[i].valid = false;
        c->lines[i].dirty = false;
        c->lines[i].tag = 0;
        c->lines[i].last_access = 0;
        c->lines[i].data = (uint8_t *) malloc(sizeof(uint8_t) * c->config.line_size);
        memset(c->lines[i].data, 0, sizeof(uint8_t) * c->config.line_size);
    }

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
    for (uint32_t i = 0; i < cache->config.lines; ++i) {
        if (cache->lines[i].dirty) {
            if (cache->lower_cache != NULL) {
                uint32_t addr = (cache->lines[i].tag << (cache->config.address_bits - cache->tag_bits)) |
                                (i << cache->offset_bits);
                for (uint32_t j = 0; j < cache->config.line_size; ++j)
                    cache_write_byte(cache->lower_cache, addr + j, cache->lines[i].data[j]);
            } else {
                mem_store(cache->lines[i].data, cache->config.line_size, cache->lines[i].tag << cache->offset_bits);
            }
        }
        free(cache->lines[i].data);
    }

    free(cache->lines);
    free(cache);
}

/* Read one byte at a specific address. return hit=true/miss=false */
bool cache_read_byte(struct cache *cache, uint32_t addr, uint8_t *byte) {
    /*YOUR CODE HERE*/
    cache->lines[0].last_access = get_timestamp();
    addr += 1;
    byte += 1;
    return true;
}
/* Write one byte into a specific address. return hit=true/miss=false*/
bool cache_write_byte(struct cache *cache, uint32_t addr, uint8_t byte) {
    /*YOUR CODE HERE*/
    cache->lines[0].last_access = get_timestamp();
    addr += 1;
    byte += 1;
    return true;
}
