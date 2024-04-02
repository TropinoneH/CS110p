#include "../inc/fks_level2.h"
#include "../inc/hash_func.h"
#include <string.h>

fks_level2 *fks_level2_init(uint32_t size, hash_parameters parameters) {
    fks_level2 *table = (fks_level2 *)malloc(sizeof(fks_level2));
    table->size = size;
    table->parameters = parameters;
    table->slots = malloc(sizeof(uint32_t) * size);
    memset(table->slots, FKS_LEVEL2_EMPTY, sizeof(uint32_t) * size);
    return table;
}

fks_level2 *fks_level2_build(list_node *head, uint32_t size,
                             hash_parameters parameters) {
    if (size == 0) {
        return NULL;
    }
    fks_level2 *table = fks_level2_init(size, parameters);
    while (head) {
        fks_level2_insert(table, head->key);
        head = head->next;
    }
    return table;
}

bool fks_level2_insert(fks_level2 *table, uint32_t key) {
    uint32_t index = hash_func(key, table->parameters, table->size);
    if (table->slots[index] != FKS_LEVEL2_EMPTY) {
        return false;
    }
    table->slots[index] = key;
    return true;
}

bool fks_level2_search(fks_level2 *table, uint32_t key) {
    uint32_t index = hash_func(key, table->parameters, table->size);
    return table->slots[index] == key;
}

void fks_level2_destroy(fks_level2 *table) {
    free(table->slots);
    free(table);
}
