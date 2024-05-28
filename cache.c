#include "cache.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

/* utils */
uint32_t mlog2(double x) {
    uint32_t res = 0;
    while (x - 1 > .001) {
        x /= 2;
        res++;
    }
    return res;
}


/* Create a cache simulator according to the config */
struct cache *cache_create(struct cache_config config, struct cache *lower_level) {
    /*YOUR CODE HERE*/
    struct cache *cache = (struct cache *) malloc(sizeof(struct cache));
    cache->config = config;
    cache->lower_cache = lower_level;

    cache->offset_bits = mlog2(cache->config.line_size);
    cache->index_bits = mlog2((double) cache->config.lines / cache->config.ways);
    cache->tag_bits = config.address_bits - cache->offset_bits - cache->index_bits;

    cache->offset_mask = (1 << cache->offset_bits) - 1;
    cache->index_mask = ((1 << cache->index_bits) - 1) << cache->offset_bits;
    cache->tag_mask = ((1 << cache->tag_bits) - 1) << (cache->offset_bits + cache->index_bits);

    cache->lines = (struct cache_line *) malloc(sizeof(struct cache_line) * cache->config.lines);
    if (!cache->lines) {
        free(cache);
        return NULL;
    }

    for (uint32_t i = 0; i < cache->config.lines; ++i) {
        cache->lines[i].valid = false;
        cache->lines[i].dirty = false;
        cache->lines[i].tag = 0;
        cache->lines[i].last_access = 0;
        cache->lines[i].data = (uint8_t *) calloc(cache->config.line_size, sizeof(uint8_t));

        if (!cache->lines[i].data) {
            for (size_t j = 0; j != i; ++j) free(cache->lines[j].data);
            free(cache->lines);
            free(cache);
            return NULL;
        }
    }

    return cache;
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
    uint32_t sets_num = cache->config.lines / cache->config.ways;
    for (uint32_t i = 0; i < cache->config.lines; ++i) {
        if (cache->lines[i].valid && cache->lines[i].dirty) {
            uint32_t addr = (cache->lines[i].tag << (cache->config.address_bits - cache->tag_bits)) |
                            ((i % sets_num) << cache->offset_bits);
            if (cache->lower_cache != NULL) {
                for (uint32_t j = 0; j < cache->config.line_size; ++j)
                    cache_write_byte(cache->lower_cache, addr + j, cache->lines[i].data[j]);
            } else {
                mem_store(cache->lines[i].data, addr, cache->config.line_size);
            }
        }
        free(cache->lines[i].data);
    }

    free(cache->lines);
    free(cache);
}

/* Read one byte at a specific address. return hit=true/miss=false */
void replace(struct cache *cache, uint32_t line_index, uint32_t addr) {
    uint32_t lower_addr = addr & ~cache->offset_mask;

    uint32_t origin_addr = cache->lines[line_index].tag << (cache->config.address_bits - cache->tag_bits) |
                           line_index << cache->offset_bits;

    // for write back policy
    if (cache->config.write_back && cache->lines[line_index].valid && cache->lines[line_index].dirty) {
        if (cache->lower_cache)
            for (uint32_t i = 0; i < cache->config.line_size; ++i)
                cache_write_byte(cache->lower_cache, origin_addr + i, cache->lines[line_index].data[i]);
        else
            mem_store(cache->lines[line_index].data, origin_addr, cache->config.line_size);
    }

    cache->lines[line_index].valid = true;
    cache->lines[line_index].dirty = false;

    // load data from memory or lower cache
    if (cache->lower_cache) {
        for (uint32_t i = 0; i < cache->config.line_size; ++i)
            cache_read_byte(cache->lower_cache, lower_addr + i, &cache->lines[line_index].data[i]);
    } else {
        mem_load(cache->lines[line_index].data, lower_addr, cache->config.line_size);
    }

    cache->lines[line_index].tag = (addr & cache->tag_mask) >> (cache->offset_bits + cache->index_bits);
}

bool cache_read_byte(struct cache *cache, uint32_t addr, uint8_t *byte) {
    /*YOUR CODE HERE*/
    uint32_t sets_num = cache->config.lines / cache->config.ways;
    uint32_t offset = addr & cache->offset_mask;
    uint32_t index = (addr & cache->index_mask) >> cache->offset_bits;
    uint32_t tag = (addr & cache->tag_mask) >> (cache->offset_bits + cache->index_bits);

    /***************************** hit *****************************/
    for (uint32_t i = 0; i < cache->config.ways; ++i) {
        uint32_t line_index = i * sets_num + index;
        if (cache->lines[line_index].valid && cache->lines[line_index].tag == tag) {
            cache->lines[line_index].last_access = get_timestamp();
            *byte = cache->lines[line_index].data[offset];
            return true;
        }
    }

    /***************************** miss *****************************/

    // find line by LRU and update last access time by time stamp
    uint32_t target_line = index;
    for (uint32_t i = 0; i < cache->config.ways; ++i) {
        // replace by LRU
        uint32_t line_index = i * sets_num + index;
        if (!cache->lines[line_index].valid ||
            cache->lines[line_index].last_access < cache->lines[target_line].last_access)
            target_line = line_index;
    }
    cache->lines[target_line].last_access = get_timestamp();

    // load data from memory or lower cache
    if (!cache->lines[target_line].valid) {
        // write directly(exist empty entry)
        if (cache->lower_cache) {
            for (uint32_t i = 0; i < cache->config.line_size; ++i)
                cache_read_byte(cache->lower_cache, (addr & ~cache->offset_mask) | i,
                                &cache->lines[target_line].data[i]);
        } else {
            mem_load(cache->lines[target_line].data, addr & ~cache->offset_mask, cache->config.line_size);
        }
        cache->lines[target_line].valid = true;
        cache->lines[target_line].tag = tag;
    } else {
        // replace by LRU
        replace(cache, target_line, addr);
    }
    *byte = cache->lines[target_line].data[offset];

    return false;
}
/* Write one byte into a specific address. return hit=true/miss=false*/
bool cache_write_byte(struct cache *cache, uint32_t addr, uint8_t byte) {
    /*YOUR CODE HERE*/
    uint32_t sets_num = cache->config.lines / cache->config.ways;
    uint32_t offset = addr & cache->offset_mask;
    uint32_t index = (addr & cache->index_mask) >> cache->offset_bits;
    uint32_t tag = (addr & cache->tag_mask) >> (cache->offset_bits + cache->index_bits);

    /***************************** hit *****************************/
    for (uint32_t i = 0; i < cache->config.ways; ++i) {
        uint32_t line_index = i * sets_num + index;
        if (cache->lines[line_index].valid && cache->lines[line_index].tag == tag) {
            cache->lines[line_index].last_access = get_timestamp();
            cache->lines[line_index].data[offset] = byte;
            if (cache->config.write_back) {
                cache->lines[line_index].dirty = true;
            } else {
                if (cache->lower_cache) {
                    cache_write_byte(cache->lower_cache, addr, byte);
                } else {
                    mem_store(&byte, addr, 1);
                }
            }
            return true;
        }
    }

    /***************************** miss *****************************/
    uint32_t target_line = 0;
    for (uint32_t i = 0; i < cache->config.ways; ++i) {
        uint32_t line_index = i * sets_num + index;
        if (!cache->lines[line_index].valid ||
            cache->lines[line_index].last_access < cache->lines[target_line].last_access)
            target_line = line_index;
    }
    cache->lines[target_line].last_access = get_timestamp();

    if (!cache->lines[target_line].valid) {
        if (cache->lower_cache) {
            for (uint32_t i = 0; i < cache->config.line_size; ++i)
                cache_read_byte(cache->lower_cache, (addr & ~cache->offset_mask) | i,
                                &cache->lines[target_line].data[i]);
        } else {
            mem_load(cache->lines[target_line].data, addr & ~cache->offset_mask, cache->config.line_size);
        }
        cache->lines[target_line].valid = true;
        cache->lines[target_line].tag = tag;
        cache->lines[target_line].data[offset] = byte;
        if (cache->config.write_back) {
            cache->lines[target_line].dirty = true;
        } else {
            if (cache->lower_cache) {
                cache_write_byte(cache->lower_cache, addr, byte);
            } else {
                mem_store(cache->lines[target_line].data, addr & ~cache->offset_mask, cache->config.line_size);
            }
        }
    } else {
        replace(cache, target_line, addr);
        cache->lines[target_line].data[offset] = byte;
        if (cache->config.write_back) {
            cache->lines[target_line].dirty = true;
        } else {
            if (cache->lower_cache) {
                cache_write_byte(cache->lower_cache, addr, byte);
            } else {
                mem_store(cache->lines[target_line].data, addr & ~cache->offset_mask, cache->config.line_size);
            }
        }
    }

    return false;
}
