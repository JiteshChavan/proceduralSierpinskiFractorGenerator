#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <math.h>
#include "triangle.h"

#define ALL_CHARS_EXTRACTED -1

typedef unsigned char byte;
typedef byte pixMap [MAX_H_RES * MAX_V_RES];

typedef struct cartesian {
    int x;
    int y;
} cartesian;

typedef struct triangle {
    int base;
    int height;
    int netRes;
    int maxPixVal;
    pixMap graphics;
    cartesian eyeOfTheStorm;
    cartesian vertA;
    cartesian vertB;
    cartesian vertC;
} triangle;

static void printNumberToFile (FILE *target, int number);
static int roundz (double number);
static char getCharFromRight (int *number);

static void testHelpers ();
static void testLog ();
static void testGetCharFromRight ();
static void testroundz ();
static int noCharsLeftToExtract (int a);

Triangle initializeTriangle (int base, seed initialVertex, int maxPixelValue) {
    testHelpers ();
    assert (base <= MAX_H_RES && base > 0);
    assert (maxPixelValue > 0);
    assert (initialVertex == VERTEX_A || initialVertex == VERTEX_B || initialVertex == VERTEX_C || initialVertex == RANDOM_VERTEX);

    Triangle geometry;
    geometry = malloc (sizeof (triangle));

    geometry->base = base;
    geometry->height = roundz(((sqrt (3))/2) * base);
    assert (geometry->height <= MAX_V_RES);
    geometry->netRes = geometry->height * geometry->base;
    printf ("netR = %u & base *height = %u\n",geometry->netRes,geometry->base*geometry->height);
    geometry->maxPixVal = MAX_PIXEL_VALUE;
    int i = 0;
    while (i < MAX_NET_RES) {
        geometry->graphics[i] = 0;
        i ++;
    }
    geometry->vertA.x = 0;
    geometry->vertA.y = geometry->height - 1;
    geometry->vertB.x = geometry->base - 1;
    geometry->vertB.y = geometry->height - 1;
    geometry->vertC.x = (int) ((geometry->base - 1)/2);
    geometry->vertC.y = 0;

    if (initialVertex == VERTEX_A) {
        geometry->eyeOfTheStorm = geometry->vertA;
    } else if (initialVertex == VERTEX_B) {
        geometry->eyeOfTheStorm = geometry->vertB;
    } else if (initialVertex == VERTEX_C) {
        geometry->eyeOfTheStorm = geometry->vertC;
    } else {
        int a = rand () % 3;
        printf ("a = %d\n",a);
        if (a == 0) {
            geometry->eyeOfTheStorm = geometry->vertA;
        } else if (a == 1) {
            geometry->eyeOfTheStorm = geometry->vertB;
        } else {
            geometry->eyeOfTheStorm = geometry->vertC;
        }
    }
    printf ("point A ~ x %d  y %d\n", geometry->vertA.x, geometry->vertA.y);
    printf ("point B ~ x %d  y %d\n", geometry->vertB.x, geometry->vertB.y);
    printf ("point C ~ x %d  y %d\n", geometry->vertC.x, geometry->vertC.y);
    return geometry;
}

void destroyTriangle (Triangle geometry) {
    assert (geometry != NULL);
    free (geometry);
    return;
}

void execute (Triangle geometry) {
    assert (geometry != NULL);
    int i = 0;
    while (i < ITERATIONS) {
        int randomizedVert = rand () % 3;
        //printf ("rverrt = %d\n", randomizedVert);
        assert (randomizedVert == 0 || randomizedVert == 1 || randomizedVert == 2);
        cartesian target;
        if (randomizedVert == 0) {
            target = geometry->vertA;
        } else if (randomizedVert == 1) {
            target = geometry->vertB;
        } else {
            target = geometry->vertC;
        }
        cartesian midPoint;
        midPoint.x = roundz ((geometry->eyeOfTheStorm.x + target.x)/2);
        midPoint.y = roundz ((geometry->eyeOfTheStorm.y + target.y)/2);
        int location = midPoint.y * geometry->base + midPoint.x;
        geometry->graphics[location] = 1;
        geometry->eyeOfTheStorm = midPoint;
        i ++;
    }      
    return;
}

void save (Triangle geometry, fileName outFile) {
    assert (geometry != NULL);

    FILE *target;
    target = fopen (outFile, "wb");
    assert (target != NULL);

    fputc ('P', target);
    fputc ('2', target);
    fputc ('\n', target);

    printNumberToFile (target, geometry->base);
    fputc (' ', target);
    printNumberToFile (target, geometry->height);
    fputc ('\n', target);
    printNumberToFile (target, geometry->maxPixVal);
    fputc ('\n', target);

    assert (geometry->netRes == geometry->base * geometry->height);
    int i = 0;
    while (i < geometry->netRes) {
        // since the base matrix is all 0' and 1 we multiply here by MAX_PIX_VAL , try gradients for effect
        printNumberToFile (target, MAX_PIXEL_VALUE * geometry->graphics[i]);
        if (i % geometry->base == 0) {
            fputc ('\n', target);
        } else {
            fputc (' ', target);
        }
        i ++;
    }
    fclose (target);
    return;
}

static void printNumberToFile (FILE *target, int number) {
    assert (target != NULL);
    assert (number >= 0);
    digits digitStack;
    int stackPtr = -1;
    while (!noCharsLeftToExtract (number)) {
        char cChar = getCharFromRight (&number);
        digitStack[stackPtr+1] = cChar;
        stackPtr ++;
    }
    while (stackPtr > -1) {
        fputc (digitStack[stackPtr], target);
        stackPtr --;
    } 
    return;
}


static int noCharsLeftToExtract (int a) {
    int noCharsLeftToExtract= FALSE;
    if (a < 0) {
        noCharsLeftToExtract = TRUE;
    }
    return noCharsLeftToExtract;
}

static char getCharFromRight (int *number) {
    assert (*number >= 0);
    char cChar;
    int digit = *number % 10;
    if (digit == 0) {
        cChar = '0';
    } else if (digit == 1) {
        cChar = '1';
    } else if (digit == 2) {
        cChar = '2';
    } else if (digit == 3) {
        cChar = '3';
    } else if (digit == 4) {
        cChar = '4';
    } else if (digit == 5) {
        cChar = '5';
    } else if (digit == 6) {
        cChar = '6';
    } else if (digit == 7) {
        cChar = '7';
    } else if (digit == 8) {
        cChar = '8';
    } else if (digit == 9) {
        cChar = '9';
    } else {
        cChar = EOF;
        puts ("ABORTING ########################");
        assert (FALSE);
    }

    if (*number / 10 == 0) {
        *number = ALL_CHARS_EXTRACTED;
    } else {
        *number = *number / 10;
    }
    return cChar;
}

static int roundz (double number) {
    double a = number - (int) number;
    assert (a >= 0 && a < 1);
    int answer;
    if (a >= 0.5) {
        answer = (int)number + 1;
    } else {
        answer = (int)number;
    }
    return answer;
}

static void testHelpers () {
    printf ("\ttesting helper funntions\n");
    testroundz ();
    testLog ();    
    testGetCharFromRight ();
    printf ("\twoohoo!All helpers passed\n");
    return;
}

static void testGetCharFromRight () {
    printf ("\ttesting getCharFromRighht ()\n");
    int a = 1917;
    char cChar = getCharFromRight (&a);
    printf ("%c %d\n", cChar,a);
    assert (cChar == '7');
    assert (a == 191);
    cChar = getCharFromRight (&a);
    assert (cChar == '1' && a == 19);
    cChar = getCharFromRight (&a);
    assert (cChar == '9' && a == 1);
    cChar = getCharFromRight (&a);
    assert (cChar == '1'); 
    assert (a == ALL_CHARS_EXTRACTED);

    a = 1000;
    cChar = getCharFromRight (&a);
    assert (cChar == '0' && a == 100);
    cChar = getCharFromRight (&a);
    assert (cChar == '0' && a == 10);
    cChar = getCharFromRight (&a);
    assert (cChar == '0' && a == 1);
    cChar = getCharFromRight (&a);
    assert (cChar == '1' && a == ALL_CHARS_EXTRACTED);
    return;
}

static void testLog () {
    printf ("\ttesting log10 ()\n");
    int i = log10 (2);
    assert (i == 0);
    assert ((int) log10 (11) == 1);
    assert ((int)log10 (101) == 2);
    assert ((int)log10 (1001) == 3);
    assert ((int)pow (10,3) == 1000);
    return;
}

static void testroundz () {
    printf ("\t\ttesting roundz ()\n");
    int a = roundz (9.7);
    assert (a == 10);
    a = roundz (9.49);
    assert (a == 9);
    a = roundz (9.5);
    assert (a == 10);
    return;
}