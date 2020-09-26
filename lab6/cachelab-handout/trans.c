/* 
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 */ 
#include <stdio.h>
#include "cachelab.h"

//int is_transpose(int M, int N, int A[N][M], int B[M][N]);

/* 
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded. 
 */
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N])
{
	int i = 0, j = 0, k = 0, l = 0, temp_val_0 = 0, temp_val_1 = 0, temp_val_2 = 0, temp_val_3 = 0, temp_val_4 = 0, temp_val_5 = 0, temp_val_6 = 0, temp_val_7 = 0;
	if (M == 32) {
		for (i = 0; i < N; i += 8) {
			for (j = 0; j < M; j += 8) {
				for (k = i; k < i + 8; k++) {
					temp_val_0 = A[k][j];
					temp_val_1 = A[k][j + 1];
					temp_val_2 = A[k][j + 2];
					temp_val_3 = A[k][j + 3];
					temp_val_4 = A[k][j + 4];
					temp_val_5 = A[k][j + 5];
					temp_val_6 = A[k][j + 6];
					temp_val_7 = A[k][j + 7];
					B[j][k] = temp_val_0;
					B[j + 1][k] = temp_val_1;
					B[j + 2][k] = temp_val_2;
					B[j + 3][k] = temp_val_3;
					B[j + 4][k] = temp_val_4;
					B[j + 5][k] = temp_val_5;
					B[j + 6][k] = temp_val_6;
					B[j + 7][k] = temp_val_7;
				}
			}
		}
	}
	else if (M == 64) {
		for (i = 0; i < N; i += 4) {
			for (j = 0; j < M; j += 4) {
				for (k = i; k < i + 4; k++) {
					for (l = j; l < j + 4; l++) {
						if (k != l) {
							B[l][k] = A[k][l];
						}
						else {
							temp_val_0 = A[k][l];
							temp_val_1 = k;
						}
					}
					if (i == j) {
						B[temp_val_1][temp_val_1] = temp_val_0;
					}
				}
			}
		}
	}
	else {
		for (i = 0; i < M; i += 18) {
			for (j = 0; j < N; j += 18) {
				for (k = j; k < j + 18 && k < N; k++) {
					for (l = i; l < i + 18 && l < M; l++) {
						temp_val_0 = A[k][l];
						B[l][k] = temp_val_0;
					}
				}
			}
		}
	}
}


/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc); 

    /* Register any additional transpose functions */
    //registerTransFunction(trans, trans_desc); 

}

