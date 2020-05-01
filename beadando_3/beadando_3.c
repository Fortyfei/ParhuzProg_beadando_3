#include <stdio.h>
#include <math.h>
#include <omp.h>

#define PI 3.1415926535897932
#define N 16 //size of the plate

#define SIZE N+2
#define ITERATIONS 100000000

void printMatrix(int A[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            printf("%3d ", A[i][j]);
        }
        printf("\n");
    }
}

void printTime(double s, double e) {
    printf("Elapsed time: %f s\n", e - s);
}

void sequentialJacobi(int A[SIZE][SIZE]) {

    printf("\n\nSEQUENTIAL W/JACOBI\n");
    //takes the avarage of the neighbouring points
    double start = omp_get_wtime();
    {
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
    }
    double end = omp_get_wtime();
    
    printMatrix(A);
    printTime(start, end);
}

void openMP_SOR(int A[SIZE][SIZE], int t) {

    printf("\n\openMP w/SOR w/ %d threads\n",t);
    //doing odd-even updates on matrix
    double start = omp_get_wtime();
    for (int it = 0; it < ITERATIONS; ++it) {
            omp_set_num_threads(t);
            #pragma omp parallel
            for (int i = 1; i < SIZE - 1; ++i) {
            #pragma omp for nowait
                //red nodes
                for (int j = 1; j < SIZE - 1; j += 2) {
                    int n1 = A[i - 1][j];
                    int n2 = A[i + 1][j];
                    int n3 = A[i][j - 1];
                    int n4 = A[i][j + 1];
                    double num = (n1 + n2 + n3 + n4) / 4;
                    A[i][j] = round(num);
                }
                #pragma omp for nowait
                //black nodes
                for (int j = 2; j < SIZE - 1; j += 2) {
                    int n1 = A[i - 1][j];
                    int n2 = A[i + 1][j];
                    int n3 = A[i][j - 1];
                    int n4 = A[i][j + 1];
                    double num = (n1 + n2 + n3 + n4) / 4;
                    A[i][j] = round(num);
                }
                
            }
#pragma omp barrier

        }
    double end = omp_get_wtime();

    printMatrix(A);
    printTime(start, end);
}


int main() {
    
    int A[SIZE][SIZE]; //original matrix
    int B[SIZE][SIZE]; //original matrix
    int t = omp_get_max_threads();

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
    printf("MAX_NUM_OF_THREADS: %d\n", t); //in my case is 4
    printf("Number of iteration: %d\n", ITERATIONS);
    printf("\n\n PRINT START\n");
    printMatrix(A);
    //sequentialJacobi(A);
    /*for (int i = 2; i <= t; i += 2) {
        openMP_SOR(A, i);
    }*/
    openMP_SOR(A, 4);
    return 0;
}