#ifndef __AI__
#define __AI__

#include <stdint.h>
#include <unistd.h>
#include "utils.h"
#include "llist.h"
#include "hashtable.h"

#define AI_HT_CAPACITY 16769023
#define AI_HT_KEY_SIZE sizeof(int8_t) * SIZE * SIZE
#define AI_HT_VALUE_SIZE sizeof(int8_t) * SIZE * SIZE

void initialize_ai();

node_t* copy_node( node_t* n, node_t* new_node );
void free_all(list_t list, HashTable *table);

void find_solution( state_t* init_state );
void free_memory(unsigned expanded_nodes);

#endif
