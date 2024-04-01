#include "../inc/fks_level2.h"
#include "../inc/hash_func.h"
#include <string.h>

fks_level2 *fks_level2_init(uint32_t size, hash_parameters parameters) {
    // TODO
    fks_level2 *table = malloc(sizeof(fks_level2));
    table->size = size;
    table->slots = calloc(size, sizeof(uint32_t));
    for (uint32_t i = 0; i < size; i++) {
        table->slots[i] = UINT32_MAX;
    }
    table->parameters = parameters;
    return table;
}

fks_level2 *fks_level2_build(list_node *head, uint32_t size, hash_parameters parameters) {
    // TODO
    fks_level2 *table = fks_level2_init(size, parameters);

    for (list_node *current = head; current != NULL; current = current->next) {
        uint32_t index = hash_func(current->key, table->parameters, table->size);
        if (table->slots[index] == UINT32_MAX) { // Slot is empty
            table->slots[index] = current->key;
        } else {
            free(table->slots);
            free(table);
            return NULL;
        }
    }

    return table;
}

bool fks_level2_insert(fks_level2 *table, uint32_t key) {
    // TODO
    uint32_t index = hash_func(key, table->parameters, table->size);
    if (table->slots[index] == UINT32_MAX) { // Check if slot is empty
        table->slots[index] = key;
        return true;
    } else {
        // Handle collision (could signal need to rebuild the table)
        return false;
    }
}

bool fks_level2_search(fks_level2 *table, uint32_t key) {
    // TODO
    uint32_t index = hash_func(key, table->parameters, table->size);
    return table->slots[index] == key;
}

void fks_level2_destroy(fks_level2 *table) {
    // TODO
    free(table->slots);
    free(table);
}
