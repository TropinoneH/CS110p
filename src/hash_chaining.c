#include "../inc/hash_chaining.h"
#include "../inc/hash_func.h"

hash_chaining *hash_chaining_init(uint32_t size) {
    // TODO
    hash_chaining *table = malloc(sizeof(hash_chaining));
    table->size = size;
    table->slots = calloc(size, sizeof(list_node *));
    table->parameters = generate_hash_parameters();
    return table;
}

void hash_chaining_insert(hash_chaining *table, uint32_t key) {
    // TODO
    uint32_t index = hash_func(key, table->parameters, table->size);
    list_node *new_node = malloc(sizeof(list_node));
    new_node->key = key;
    new_node->next = table->slots[index];
    table->slots[index] = new_node;
}

bool hash_chaining_search(hash_chaining *table, uint32_t key) {
    // TODO
    uint32_t index = hash_func(key, table->parameters, table->size);
    list_node *current = table->slots[index];
    while (current) {
        if (current->key == key) {
            return true;
        }
        current = current->next;
    }
    return false;
}

void hash_chaining_destroy(hash_chaining *table) {
    // TODO
    for (uint32_t i = 0; i < table->size; ++i) {
        list_node *current = table->slots[i];
        while (current) {
            list_node *temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(table->slots);
    free(table);
}
