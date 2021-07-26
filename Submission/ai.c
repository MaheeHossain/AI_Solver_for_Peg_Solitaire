#include <time.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>
#include <math.h>

#include "ai.h"
#include "utils.h"
#include "hashtable.h"
#include "stack.h"
#include "llist.h"


/* Sets board state src to board state dst */
void copy_state(state_t* dst, state_t* src){
	
	//Copy field
	memcpy( dst->field, src->field, SIZE*SIZE*sizeof(int8_t) );
	
	dst->cursor = src->cursor;
	dst->selected = src->selected;
}

/**
 * Saves the path up to the node as the best solution found so far
*/
void save_solution( node_t* solution_node ){
	node_t* n = solution_node;
	while( n->parent != NULL ){
		copy_state( &(solution[n->depth]), &(n->state) );
		solution_moves[n->depth-1] = n->move;
		
		n = n->parent;
	}
	solution_size = solution_node->depth;
}

/* Creates the top node with the starting position of the board */
node_t* create_init_node( state_t* init_state ){
	node_t * new_n = (node_t *) malloc(sizeof(node_t));
	new_n->parent = NULL;	
	new_n->depth = 0;
	copy_state(&(new_n->state), init_state);
	return new_n;
}

/* Sets new node to n */
node_t* copy_node( node_t* n, node_t* new_node ){
	assert(n!=NULL && new_node!=NULL);
	new_node->parent = n->parent;
	new_node->move = n->move;
	new_node->depth = n->depth;
	copy_state(&(new_node->state), &(n->state));
	return new_node;
}

/* Frees all the data structures (linked list, stack, hashtable) */
void free_all(list_t list, HashTable *table) {
	free_stack();
	free_list(list);
	ht_destroy(table);
}

/**
 * Apply an action to node n and return a new node resulting from executing the action
*/
node_t* applyAction(node_t* n, position_s* selected_peg, move_t action ) {
	
	node_t* new_node = NULL;
	new_node = (node_t *) malloc(sizeof(node_t));
	assert(new_node!=NULL);
	generated_nodes++;
	
	//FILL IN MISSING CODE
	new_node = copy_node(n, new_node);
	new_node->state.cursor = *selected_peg;
	
	// Updates the state of the new node
	execute_move_t( &(new_node->state), &(new_node->state.cursor), action );
	
	new_node->move = action;
	new_node->depth++;
	new_node->parent = n;
	
	return new_node;
	
}

/**
 * Find a solution path as per algorithm description in the handout
 */

void find_solution( state_t* init_state  ) {
	// The board has been initialised to a layout, cursor is (4, 4),
	// selected is false
	
	HashTable table;
	
	/* Sets up the (empty) hash table
	   Choose initial capacity of PRIME NUMBER 
	   Specify the size of the keys and values you want to store once */
	ht_setup( &table, AI_HT_KEY_SIZE, AI_HT_VALUE_SIZE, AI_HT_CAPACITY);
	
	// Initialize Stack
	initialize_stack();
	
	// Add the initial node, and then place inside a linked list for freeing
	node_t* n = create_init_node( init_state );
	list_t node_list = createList();
	node_list = insert(n, node_list);
	
	//FILL IN THE GRAPH ALGORITHM
	
	stack_push(n); // Put the initial node inside the stack
	int remaining_pegs = num_pegs(&n->state); 
	
	// While stack has nodes inside it
	while (is_stack_empty() == 0) {
		n = stack_top();
		stack_pop();
		ht_insert(&table, n->state.field, n->state.field);
		expanded_nodes++;
		
		// If we've found a better solution, save it
		if (num_pegs( &(n->state) ) < remaining_pegs) {
			save_solution(n);
			remaining_pegs = num_pegs( &(n->state) );
		}
		
		// Check all moves on every peg on the board (x first, then y)
		for (int8_t x=0; x<SIZE; x++) { 
			for (int8_t y=0; y<SIZE; y++) { 
				// Set the current node's cursor position
				position_s pos = set_pos(x, y);
				
				for (move_t dir=0; dir<DIRECTIONS; dir++) {
					if (can_apply( &(n->state), &pos, dir)) {
						
						// Create a child node, place it into the list
						node_t* new_node = applyAction(n, &pos, dir);
						node_list = insert(new_node, node_list);
						
						// Check if the game is won
						if (won( &(new_node->state) )) {
							save_solution(new_node);
							free_all(node_list, &table);
							return;
						}
						// If node hasn't appeared before, push into stack
						if (!ht_contains(&table, new_node->state.field)) {
							stack_push(new_node);
						}
					}
				}
			}
		}
		
		// If the budget is exhausted, end process
		if (expanded_nodes >= budget) {
			free_all(node_list, &table);
			return;
		}
	}
}