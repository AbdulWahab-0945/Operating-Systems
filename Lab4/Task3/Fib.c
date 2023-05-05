#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s n\n", argv[0]);
        exit(1);
    }
    int n = atoi(argv[1]);
    if (n < 1) {
        printf("Invalid value of n: %d\n", n);
        exit(1);
    }
    int a = 0, b = 1;
    printf("Fibonacci series: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", a);
        int c = a + b;
        a = b;
        b = c;
    }
    printf("\n");
    return 0;
}

