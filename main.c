#include <stdio.h>
#include <stdlib.h>
#include "src/scanner.h"

int main() {
    char token[20];

    FILE *fp = fopen("c:\\users\\inga\\git\\scanner\\example.txt", "r");
    if (fp == NULL) {
        fprintf(stderr, "Error in opening file");
        exit(EXIT_FAILURE);
    }

    scan(fp, token, sizeof(token));

    fclose(fp);

    return EXIT_SUCCESS;
}