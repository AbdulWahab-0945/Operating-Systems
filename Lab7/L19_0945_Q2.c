#include <stdio.h>

int main() {
    FILE *inputFile;
    FILE *outputFile;
    char ch;

    // Open input.txt file in read mode
    inputFile = fopen("input.txt", "r");

    if (inputFile == NULL) {
        printf("Error opening input file.\n");
        return 1;
    }

    // Open output.txt file in write mode
    outputFile = fopen("output.txt", "w");

    if (outputFile == NULL) {
        printf("Error opening output file.\n");
        return 1;
    }

    // Read input.txt file and write to output.txt file
    while ((ch = fgetc(inputFile)) != EOF) {
        fputc(ch, outputFile);
    }

    printf("Contents of input.txt file successfully copied to output.txt file.\n");

    // Close files
    fclose(inputFile);
    fclose(outputFile);

    return 0;
}

