#include "../inc/fks_level1.h"
#include "../inc/hash_func.h"
#include <stdint.h>

static int get_list_len(list_node *node) {
    int len = 0;
    while (node) {
        node = node->next;
        ++len;
    }
    return len;
}

fks_level1 *fks_level1_build(hash_chaining *hash_chaining_table) {
    // TODO
    fks_level1 *table = (fks_level1 *)malloc(sizeof(fks_level1));
    table->size = hash_chaining_table->size;
    table->parameters = hash_chaining_table->parameters;
    table->level2_tables = malloc(sizeof(hash_chaining *) * table->size);
    for (uint32_t i = 0; i < table->size; ++i) {
        int len = get_list_len(hash_chaining_table->slots[i]);
        table->level2_tables[i] = fks_level2_build(
            hash_chaining_table->slots[i], len, generate_hash_parameters());
    }

    return table;
}

bool fks_level1_search(fks_level1 *table, uint32_t key) {
    uint32_t index = hash_func(key, table->parameters, table->size);
    return fks_level2_search(table->level2_tables[index], key);
}

void fks_level1_destroy(fks_level1 *table) {
    for (uint32_t i = 0; i < table->size; ++i) {
        fks_level2_destroy(table->level2_tables[i]);
    }
    free(table->level2_tables);
    free(table);
}
