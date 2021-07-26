#include <assert.h>

#include "utils.h"
#include "layouts.h"

/**
 * Taken from sample solution of assignment 1 for the linked list
 */
void *my_malloc(size_t n){
	assert(n>0);
	void *p= malloc(n);
	assert(p);
	return p;
}

char *my_strdup(char *s) {
	char *t= strdup(s);
	assert(t);
	return t;
}


/* Jumps over a peg */
void execute_move_t(state_t* state, position_s* selected_peg, move_t jump) {
    int8_t x = selected_peg->x;
    int8_t y = selected_peg->y;
	state->cursor = set_pos(x, y);

    
    switch (jump) {
    case up:          //Jump up
        state->field[x][y-2] = 'o';
        state->field[x][y-1] = '.';
        state->field[x][y-0] = '.';
        state->cursor.y = y-2;
        break;

    case down:         //Jump down
        state->field[x][y+0] = '.';
        state->field[x][y+1] = '.';
        state->field[x][y+2] = 'o';
        state->cursor.y = y+2;
        break;

    case left:         //Jump left
        state->field[x-2][y] = 'o';
        state->field[x-1][y] = '.';
        state->field[x-0][y] = '.';
		state->cursor.x = x-2;
        break;

    case right:          //Jump right
        state->field[x+0][y] = '.';
        state->field[x+1][y] = '.';
        state->field[x+2][y] = 'o';
		state->cursor.x = x+2;
        break;

    }
	
}

/* Checks if the jump in a certain direction is legal */
bool can_apply(state_t *board, position_s* selected_peg, move_t jump){
    
    // Can select a Peg
    if ( board->field[ selected_peg->x ][ selected_peg->y ] !='o')  return false;
    
    // Determine if move is legal
    switch (jump) {
        case up:          
            if(  selected_peg->y < 2) return false;
            if( board->field[ selected_peg->x ][ selected_peg->y - 1 ] !='o')  return false;
            if( board->field[ selected_peg->x ][ selected_peg->y - 2 ] !='.')  return false;
            break;
            
        case down:         
            if( selected_peg->y > SIZE - 3 ) return false;
            if( board->field[ selected_peg->x ][ selected_peg->y + 1 ] !='o')  return false;
            if( board->field[ selected_peg->x ][ selected_peg->y + 2 ] !='.')  return false;
            break;

        case left:         
            if( selected_peg->x < 2) return false;
            if( board->field[ selected_peg->x - 1 ][ selected_peg->y ] !='o')  return false;
            if( board->field[ selected_peg->x - 2 ][ selected_peg->y ] !='.')  return false;
            break;

        case right:          
            if( selected_peg->x > SIZE - 3) return false;
            if( board->field[ selected_peg->x + 1 ][ selected_peg->y ] !='o')  return false;
            if( board->field[ selected_peg->x + 2 ][ selected_peg->y ] !='.')  return false;
            break;
    }
    // Can Jump

    
    return true;

}

/* Checks if you've won yet */
bool won(state_t *board) {
	int8_t x,y;
	int8_t count=0;

	for (x=0;x<SIZE;x++) {
		for (y=0;y<SIZE;y++) {
			if (board->field[x][y]=='o') {
				count++;
             
			}
            // If more than one peg is left, you haven't won yet
            if( count > 1) return false;
		}
	}
	//If only one is left
	return count == 1;

}

/* Counts how many pegs there are */
int num_pegs( state_t *board ){
	int count = 0;
	for (int y=0;y<SIZE;y++) {
		for (int x=0;x<SIZE;x++) {
			count+=board->field[x][y]=='o';
		}
	}
	return count;
}

/* Sets a position from a given x and y */
position_s set_pos(int8_t x, int8_t y) {
	position_s pos;
	pos.x = x;
	pos.y = y;
	return pos;
}

/* Rotate the board anti-clockwise */
void rotateBoard(state_t *board) {
	int8_t i,j,n=SIZE;
	int8_t tmp;
	for (i=0; i<n/2; i++){
		for (j=i; j<n-i-1; j++){
			tmp = board->field[i][j];
			board->field[i][j] = board->field[j][n-i-1];
			board->field[j][n-i-1] = board->field[n-i-1][n-j-1];
			board->field[n-i-1][n-j-1] = board->field[n-j-1][i];
			board->field[n-j-1][i] = tmp;
		}
	}
	i = board->cursor.x;
	j = board->cursor.y;

	board->cursor.x = -(j-n/2)+n/2;
	board->cursor.y = (i-n/2)+n/2;
}

/* If a peg is selected, check if it can be, then select it */
bool select_peg(state_t *board) {
	int8_t x,y,(*field)[SIZE];
	bool selected;

	x = board->cursor.x;
	y = board->cursor.y;
	field = board->field;
	selected = board->selected;

	if (field[x][y]!='o') return false;
	board->selected = !selected;
	return true;
}

/* Moves the cursor up */
bool moveUp(state_t *board) {
	int8_t x,y,(*field)[SIZE];
	bool selected;

	x = board->cursor.x;
	y = board->cursor.y;
	field = board->field;
	selected = board->selected;

	/* If selected, jump over the peg */
	if (selected) {
		if (y<2) return false;
		if (field[x][y-2]!='.') return false;
		if (field[x][y-1]!='o') return false;
		if (field[x][y-0]!='o') return false;
		field[x][y-2] = 'o';
		field[x][y-1] = '.';
		field[x][y-0] = '.';
		board->cursor.y = y-2;
		board->selected = false;
	} else {
		if (y<1) return false;
		if (field[x][y-1]==' ') return false;
		board->cursor.y = y-1;
	}
	return true;
}

/* Left, Down and Right all use moveUp but rotate the board */
bool moveLeft(state_t *board) {
	bool success;
	rotateBoard(board);
	success = moveUp(board);
	rotateBoard(board);
	rotateBoard(board);
	rotateBoard(board);
	return success;
}

bool moveDown(state_t *board) {
	bool success;
	rotateBoard(board);
	rotateBoard(board);
	success = moveUp(board);
	rotateBoard(board);
	rotateBoard(board);
	return success;
}

bool moveRight(state_t *board) {
	bool success;
	rotateBoard(board);
	rotateBoard(board);
	rotateBoard(board);
	success = moveUp(board);
	rotateBoard(board);
	return success;
}

/* Checks how many moves are valid up */
int8_t validMovesUp(state_t *board) {
	int8_t x,y;
	int8_t count=0;
	for (x=0;x<SIZE;x++) {
		for (y=SIZE-1;y>1;y--) {
			// For all the pegs, check if it can do a valid move up
			if (board->field[x][y]=='o') {
				if (board->field[x][y-1]=='o') {
					if (board->field[x][y-2]=='.') {
						count++;
					}
				}
			}
		}
	}
	return count;
}

/* Checks how many valid moves there are overall */
int8_t validMoves(state_t *board) {
	int8_t i, count=0;

	for (i=0; i < DIRECTIONS; i++) {
		count += validMovesUp(board);
		rotateBoard(board);
	}

	return count;
}

/* Check if there are any valid moves left, if not return false */
bool gameEndedForHuman(state_t *board) {
	return (validMoves(board)==0);
	// If this doesn't work, copy validMoves but return count==0
}

/* Sets the board to the correct layout */
void initialize(state_t *board, int8_t layout) {
	int8_t x,y;

	// If layout is a number bigger than the highest level, set to 0
	if( layout > NUM_LAYOUTS - 1) layout = 0; 
	
	board->cursor.x = 4; // Why 4?
	board->cursor.y = 4;
	board->selected = false;

	memset(board->field,0,sizeof(board->field));

	// Sets the board's field to the given level's board
	for (y=0;y<SIZE;y++) {
		for (x=0;x<SIZE;x++) {
			board->field[x][y]=configuration[layout][y][x*2];
		}
	}
}

/* Displays the board on the screen (initial state?) */
void drawBoard(state_t *board) {
	int8_t x,y,count=0;

	// move cursor to home position
	printf("\033[H");

	// Set the board covered in o
	for (y=0;y<SIZE;y++) {
		for (x=0;x<SIZE;x++) {
			count+=board->field[x][y]=='o';
		}
	}

	// Print out the peg count
	printf("peg-solitaire.c %7d pegs\n",count);
	printf("                             \n");

	// 
	for (y=0;y<SIZE;y++) {
		// Pushes the board to the centre of the screen
		for (x=0;x<SIDE_SPACES;x++) { // SIDE_SPACES used to be 14-SIZE
			printf(" ");
		}
		for (x=0;x<SIZE;x++) {
			// If the cursor is on the current point, highlight if selected(?)
			if (board->cursor.x == x && board->cursor.y == y) {
				if (board->selected) {
					printf("\b|\033[7m%c\033[27m|",board->field[x][y]);
				} else {
					printf("\033[7m%c\033[27m ",board->field[x][y]);
				}
			} else {
				printf("%c ",board->field[x][y]);
			}
		}
		for (x=0;x<SIDE_SPACES;x++) {
			printf(" ");
		}
		printf("\n");
	}

	// Gives the instructions
	printf("                            \n");
	printf("   arrow keys, q or enter   \n");
	printf("\033[A"); // one line up
}

char* action_cstr(move_t move){

	switch (move) {
		case up:  
			return "Up";
		break;

		case down: 
			return "Down";
		break;

		case left:    
			return "Left";
		break;

		case right:  
			return "Right";
		break;

	}
	return " ";
}

void print_solution(){

	for(int i=0; i< solution_size; i++)
		printf("    %d - %s                              \n", i+1, action_cstr(solution_moves[i]));
		
}

/* Plays the solution animation for the AI solution */
void play_solution(){
	for(int i=0; i <= solution_size; i++) {
		// Draw the current state of the board
		drawBoard(&(solution[i]));
		usleep(PAUSE_TIME); // unistd.h - suspend execution for microsecond intervals
		
		if ( i < solution_size) {
			//Reverse action
			switch ( solution_moves[i] ) {
				case up:          
					solution[i].cursor.y = solution[i+1].cursor.y+2;
					solution[i].cursor.x = solution[i+1].cursor.x;
					break;
				case down:         	
					solution[i].cursor.y = solution[i+1].cursor.y-2;
					solution[i].cursor.x = solution[i+1].cursor.x;
					break;
				case left:         
					solution[i].cursor.x = solution[i+1].cursor.x+2;
					solution[i].cursor.y = solution[i+1].cursor.y;
					break;
				case right:          
					solution[i].cursor.x = solution[i+1].cursor.x-2;
					solution[i].cursor.y = solution[i+1].cursor.y;
					break;
				}
			solution[i].selected = true;
			drawBoard(&(solution[i]));
			usleep(PAUSE_TIME);
		}
	}
}
