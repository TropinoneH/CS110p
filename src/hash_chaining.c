#include "../inc/hash_chaining.h"
#include "../inc/hash_func.h"

hash_chaining *hash_chaining_init(uint32_t size) {
    hash_chaining *table = (hash_chaining *)malloc(sizeof(hash_chaining));
    table->slots = calloc(size, sizeof(list_node *));
    table->size = size;
    table->parameters = generate_hash_parameters();
    return table;
}

void hash_chaining_insert(hash_chaining *table, uint32_t key) {
    uint32_t index = hash_func(key, table->parameters, table->size);
    list_node *node = (list_node *)malloc(sizeof(list_node));
    node->key = key;
    node->next = table->slots[index];
    table->slots[index] = node;
}

bool hash_chaining_search(hash_chaining *table, uint32_t key) {
    uint32_t index = hash_func(key, table->parameters, table->size);
    list_node *node = table->slots[index];
    while (node) {
        if (node->key == key) {
            return true;
        }
        node = node->next;
    }
    return false;
}

void hash_chaining_destroy(hash_chaining *table) {
    for (uint32_t i = 0; i < table->size; ++i) {
        list_node *node = table->slots[i];
        while (node) {
            list_node *temp = node;
            node = node->next;
            free(temp);
        }
    }

    free(table->slots);
    free(table);
}
