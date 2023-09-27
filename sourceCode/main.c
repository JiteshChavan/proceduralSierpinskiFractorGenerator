#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include "triangle.h"

void seedRGen ();

int main (int argc, char *argv[]) {
    seedRGen ();
    fileName outFile = "triangle.pgm";
    Triangle geometry = initializeTriangle (1920, RANDOM_VERTEX, MAX_PIXEL_VALUE);
    execute (geometry);
    save (geometry, outFile);
    destroyTriangle (geometry);

    return EXIT_SUCCESS;
}

void seedRGen () {
    time_t t;
    srand (time (&t));
    return;
}