#ifndef __UTILS__
#define __UTILS__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "termios.h"
#include <stdbool.h>
#include <stdint.h>
#include <time.h>
#include <signal.h>
#include <assert.h>


#define SIZE 9
#define SIDE_SPACES 14-SIZE
#define _XOPEN_SOURCE 500
#define PAUSE_TIME 500000
#define DIRECTIONS 4

/**
 * Taken from sample solution of assignment 1 for the linked list
 */
void *my_malloc(size_t n);
char *my_strdup(char *);

/**
 * Data structure containing the information about the game state
 */

typedef struct {
	int8_t x,y; // int8_t is a signed char
} position_s; // Position of cursor

/* State of the board - array with all pegs, position of cursor, if selected */
typedef struct {
	int8_t field[SIZE][SIZE]; // Array of all the pegs
	position_s cursor; // Position where the cursor is
	bool selected; // Whether or not the cursor has selected a peg
} state_t;


/**
* Move type
*/
typedef enum moves_e{
	left=0,
	right=1,
	up=2,
	down=3
} move_t;


/**
 * Search Node information
 */
struct node_s{
    int depth; // How far down the node's gone
    move_t move; // Current move
    state_t state; // State of the board
    struct node_s* parent;
};

/* Node with depth, current move, state of board and parent node */
typedef struct node_s node_t;

/**
 * GLOBAL VARIABLES
*/

state_t solution[SIZE*SIZE]; // Has all the states in the solution in order
move_t  solution_moves[SIZE*SIZE]; // Has all the moves used in the solution in order
int solution_size;

int generated_nodes;
int expanded_nodes;

bool ai_run; //Run AI
bool show_solution; //Play solution found by AI algorithm
int budget; // budget for expanded nodes



/**
 *  Useful functions for AI algorithm
 */

position_s set_pos(int8_t x, int8_t y);

// Updates the field and cursor given the selected peg and the jump action chosen
void execute_move_t(state_t* state, position_s* selected_peg, move_t jump);

// returns true if move is legal
bool can_apply(state_t *board, position_s* selected_peg, move_t jump);

// Check if game is over
bool won(state_t *board);

// returns number of pegs in board
int num_pegs( state_t *board );

/**
 * Used for human games
*/
void rotateBoard(state_t *board);
bool select_peg(state_t *board);
bool moveUp(state_t *board);
bool moveLeft(state_t *board); 
bool moveDown(state_t *board); 
bool moveRight(state_t *board);
int8_t validMovesUp(state_t *board);
int8_t validMoves(state_t *board);
bool gameEndedForHuman(state_t *board);

void initialize(state_t *board, int8_t layout);

/**
 * Output functions
*/
void drawBoard(state_t *board);
char* action_cstr(move_t move);
void print_solution();
void play_solution();


#endif