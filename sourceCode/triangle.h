// triangle.h
// on April 14th 2020
// by Jitesh Chavan
#define TRUE 1
#define FALSE 0

#define MAX_H_RES 1920
#define MAX_V_RES 1920
#define MAX_NET_RES (MAX_H_RES * MAX_V_RES)

#define ITERATIONS 100000000
#define MAX_DIGITS_ALLOWED 255

#define VERTEX_A 0
#define VERTEX_B 1
#define VERTEX_C 2
#define RANDOM_VERTEX 3

#define MAX_PIXEL_VALUE 15
#define MAX_FILE_NAME_LENGTH 255

typedef struct triangle *Triangle;

typedef int seed;
typedef char fileName [MAX_FILE_NAME_LENGTH];
typedef char digits [MAX_DIGITS_ALLOWED];

// creates an equilateral triangle and returns a pointer to it
Triangle initializeTriangle (int base, seed initialVertex, int maxPixValue);

// destroys traingle
void destroyTriangle (Triangle geometry);

// executes triangle
void execute (Triangle geometry);

// stores the executed result to pgm file
void save (Triangle geometry, fileName outFile);