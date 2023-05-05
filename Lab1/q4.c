#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
    FILE *inputFile, *outputFile;
    int c;

    if (argc < 3) {
        printf("Usage: %s <input_file> <output_file>\n", argv[0]);
        return 1;
    }

    inputFile = fopen(argv[1], "r");
    outputFile = fopen(argv[2], "w");

    if (inputFile == NULL || outputFile == NULL) {
        printf("Error opening files\n");
        return 1;
    }

    while ((c = fgetc(inputFile)) != EOF) {
        if (isdigit(c)) {
            fputc(c, outputFile);
        }
    }

    fclose(inputFile);
    fclose(outputFile);

    return 0;
}

