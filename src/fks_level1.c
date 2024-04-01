#include "../inc/fks_level1.h"
#include "../inc/hash_func.h"
#include <stdio.h>

static int get_list_len(list_node *node) {
    // TODO
    int count = 0;
    while (node != NULL) {
        count++;
        node = node->next;
    }
    return count;
}

fks_level1 *fks_level1_build(hash_chaining *hash_chaining_table) {
    // TODO
    fks_level1 *table = malloc(sizeof(fks_level1));
    table->size = hash_chaining_table->size;
    table->level2_tables = malloc(table->size * sizeof(fks_level2 *));
    table->parameters = hash_chaining_table->parameters;

    for (uint32_t i = 0; i < table->size; i++) {
        list_node *chain = hash_chaining_table->slots[i];
        if (chain != NULL) {
            uint32_t l2_size = get_list_len(chain);
            table->level2_tables[i] = fks_level2_build(chain, l2_size, generate_hash_parameters());
            if (table->level2_tables[i] == NULL) {
                // Handle error in building Level 2 table
            }
        } else {
            table->level2_tables[i] = NULL;
        }
    }

    return table;
}

bool fks_level1_search(fks_level1 *table, uint32_t key) {
    // TODO
    uint32_t index = hash_func(key, table->parameters, table->size);
    if (table->level2_tables[index] != NULL) {
        return fks_level2_search(table->level2_tables[index], key);
    }
    return false;
}

void fks_level1_destroy(fks_level1 *table) {
    // TODO
    for (uint32_t i = 0; i < table->size; i++) {
        if (table->level2_tables[i] != NULL) {
            fks_level2_destroy(table->level2_tables[i]);
        }
    }
    free(table->level2_tables);
    free(table);
}
