#include <stdio.h>
#include <stdlib.h>


typedef unsigned char byte;
int main (int argc, char *argv[]) {

    FILE *dest;
    dest = fopen ("1.pgm", "w");

    fputc ('P', dest);
    fputc ('2', dest);
    fputc ('\n', dest);
    fputc ('4', dest);
    fputc (' ', dest);
    fputc ('2', dest);
    fputc ('\n', dest);
    fputc ('1', dest);
    fputc ('\n', dest);
    fputc ('0', dest);
    fputc (' ', dest);
    fputc ('1', dest);
    fputc (' ', dest);
    fputc ('0', dest);
    fputc (' ', dest);
    fputc ('1', dest);
    fputc ('\n', dest);
    fputc ('1', dest);
    fputc (' ', dest);
    fputc ('0', dest);
    fputc (' ', dest);
    fputc ('1', dest);
    fputc (' ', dest);
    fputc ('0', dest);
    fputc ('\n', dest);
    fclose (dest);
    return EXIT_SUCCESS;

}