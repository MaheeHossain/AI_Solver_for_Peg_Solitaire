#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define NOT_ALIGNED 0
#define ALIGNED 1
#define ORBIT_FINISHED 0
#define ORBIT_NOT_FINISHED -1

int planets_aligned(int* positions, int num_planets) {
    /* Checks if all planets are at position 0 or not */
    for (int i=0; i<num_planets; i++) {
        if (positions[i] != ORBIT_FINISHED) {
            return NOT_ALIGNED;
        }
    }
    return ALIGNED;
}


int main(int argc, char* argv[]) {
    /* Finds when rocket can launch */
    int num_planets=0;

    // Read file to get all the planets and their orbits
    // As the question says to use fscanf, it is assumed 
    // that argv[0] is a file containing the line which
    // is given as the input
    FILE *fp = fopen(argv[0], "r");
    fscanf(fp, "%d", &num_planets);
    if (fp == NULL) {
        printf("Input file is empty");
        exit(EXIT_FAILURE);
    }

    // Allocate space for orbit and positions array then fill both
    int *orbits = (int*)malloc(sizeof(int) * num_planets);
    assert(orbits!=NULL);
    int *positions= (int*)malloc(sizeof(int) * num_planets);
    assert(positions!=NULL);

    for (int i=0; i<num_planets; i++) {
        fscanf(fp, " %d", &(orbits[i]));
        positions[i] = 0;
    }

    // For each second (after the first), loop through all the planets
    // and check if their orbits have finished. If not, set position to 
    // -1. Call planets_aligned to check if they're all 0
    int seconds = 0;

    do {
        for (int i=0; i<num_planets; i++) {
            if ((seconds+1) % orbits[i] == 0) {
                positions[i] = ORBIT_FINISHED;
            }
            else {
                positions[i] = ORBIT_NOT_FINISHED;
            }
        }
        seconds++;

    } while (planets_aligned(positions, num_planets != ALIGNED));

    // Once out of loop, the value of seconds is how long it takes 
    // to align
    printf("\nTime to wait for take-off: %d seconds\n", seconds);
    
    // Free everything and return
    free(orbits);
    free(positions);
    fclose(fp);
    return 0;
}