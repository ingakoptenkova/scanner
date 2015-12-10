#include <stdio.h>
#include "src/scanner.h"

int main() {
    char token[20];

    FILE *fp = fopen("c:\\users\\inga\\git\\lexica\\example.txt", "r");
    if (fp == NULL) {
        fprintf(stderr, "Error in opening file");
        return -1;
    }

    scan(fp, token, sizeof(token));

    fclose(fp);

    return 0;
}