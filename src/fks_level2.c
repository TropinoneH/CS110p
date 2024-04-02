#include "../inc/fks_level2.h"
#include "../inc/hash_func.h"
#include <stdio.h>
#include <string.h>

fks_level2 *fks_level2_init(uint32_t size, hash_parameters parameters) {
    fks_level2 *table = (fks_level2 *) malloc(sizeof(fks_level2));
    table->size = size;
    table->parameters = parameters;
    table->slots = malloc(sizeof(uint32_t) * size);
    memset(table->slots, FKS_LEVEL2_EMPTY, sizeof(uint32_t) * size);
    return table;
}

fks_level2 *fks_level2_build(list_node *head, uint32_t size, hash_parameters parameters) {
    if (size == 0) {
        return NULL;
    }
    size *= size;
    bool no_conflict = false;
    list_node *current;

    fks_level2 *table = fks_level2_init(size, parameters);

    while (!no_conflict) {
        no_conflict = true;
        fks_level2_destroy(table);
        table = fks_level2_init(size, generate_hash_parameters());
        current = head;
        while (current) {
            if (!fks_level2_insert(table, current->key)) {
                no_conflict = false;
                break;
            }
            current = current->next;
        }
    }

    return table;
}

bool fks_level2_insert(fks_level2 *table, uint32_t key) {
    uint32_t index = hash_func(key, table->parameters, table->size);
    // printf("p->a: %u, p->b: %u\n", table->parameters.a, table->parameters.b);
    if (table->slots[index] != FKS_LEVEL2_EMPTY && table->slots[index] != key) {
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
