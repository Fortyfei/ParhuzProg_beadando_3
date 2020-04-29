#include <stdio.h>
#include <math.h>

#define PI 3.1415926535897932
#define N 16 //size of the plate

#define SIZE N+2
#define ITERATIONS 100*100*100*10

void printMatrix(int A[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            printf("%3d ", A[i][j]);
        }
        printf("\n");
    }
}

void sequential(int A[SIZE][SIZE]) {
    printf("\n\nSEQUENTIAL\n");
    for (int it = 0; it < ITERATIONS; ++it) {
        for (int i = 1; i < SIZE - 1; ++i) {
            for (int j = 1; j < SIZE - 1; ++j) {
                int n1 = A[i - 1][j];
                int n2 = A[i + 1][j];
                int n3 = A[i][j - 1];
                int n4 = A[i][j + 1];
                double num = (n1 + n2 + n3 + n4) / 4;
                A[i][j] = round(num);
            }
        }
    }
    printMatrix(A);
}


int main() {
    
    int A[SIZE][SIZE]; //original matrix
    //initializing matrix
   
    for(int i=0;i<SIZE;++i){
        for (int j = 0; j < SIZE; ++j) {
            if (i == 0) {
                int num = round(100 + 50 * sin(PI * j / (N + 1)));
                A[i][j] = num;
            }
            else {
                A[i][j] = 100;
            }
        }
    }

    printf("\n\n PRINT START\n");
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            printf("%3d ", A[i][j]);
        }
        printf("\n");
    }
    sequential(A);
    
    return 0;
}