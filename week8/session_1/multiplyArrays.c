#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int arrayA[3][4];
    int arrayB[3][4];
    int arrayProduct[3][4];
    int i, j;

    // Seed the random number generator
    srand(time(NULL));

    // Assign random values to each element of the array
    for(i = 0; i < 3; i++) {
        for(j = 0; j < 4; j++) {
            arrayA[i][j] = rand() % 11; // rand() % 11 gives a range 0 to 10
        }
    }

    for(i = 0; i < 3; i++) {
        for(j = 0; j < 4; j++) {
            arrayB[i][j] = rand() % 11; // rand() % 11 gives a range 0 to 10
        }
    }

    for(i = 0; i < 3; i++) {
        for(j = 0; j < 4; j++) {
            arrayProduct[i][j] = arrayA[i][j] * arrayB[i][j];
        }
    }

    printf("\nArray A\n");
    for(i = 0; i < 3; i++) {
        for(j = 0; j < 4; j++) {
            printf("%d ", arrayA[i][j]);
        }
        printf("\n");
    }

    printf("\nArray B\n");
    for(i = 0; i < 3; i++) {
        for(j = 0; j < 4; j++) {
            printf("%d ", arrayB[i][j]);
        }
        printf("\n");
    }

    printf("\nProduct\n");
    for(i = 0; i < 3; i++) {
        for(j = 0; j < 4; j++) {
            printf("%d ", arrayProduct[i][j]);
        }
        printf("\n");
    }
    return 0;
}