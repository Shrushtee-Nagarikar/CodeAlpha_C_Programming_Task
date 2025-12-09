#include <stdio.h>
#define MAX 10
// Function to read a matrix
void readMatrix(int matrix[MAX][MAX], int row, int col) {
    printf("Enter elements of the matrix (%dx%d):\n", row, col);
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
}
// Function to print a matrix
void printMatrix(int matrix[MAX][MAX], int row, int col) 
{
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
}
// Matrix Addition
void addMatrices(int m1[MAX][MAX], int m2[MAX][MAX], int r, int c) {
    int sum[MAX][MAX];
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            sum[i][j] = m1[i][j] + m2[i][j];
        }
    }
    printf("\nSum of Matrices:\n");
    printMatrix(sum, r, c);
}
// Matrix Multiplication
void multiplyMatrices(int m1[MAX][MAX], int m2[MAX][MAX], int r1, int c1, int c2) {
    int product[MAX][MAX] = {0};
    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c2; j++) {
            for (int k = 0; k < c1; k++) {
                product[i][j] += m1[i][k] * m2[k][j];
            }
        }
    }
    printf("\nProduct of Matrices:\n");
    printMatrix(product, r1, c2);
}
// Transpose
void transposeMatrix(int m[MAX][MAX], int r, int c) {
    int trans[MAX][MAX];
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            trans[j][i] = m[i][j];
        }
    }
    printf("\nTranspose of Matrix:\n");
    printMatrix(trans, c, r); // Note: Rows and cols are swapped
}
int main() {
    int matA[MAX][MAX], matB[MAX][MAX];
    int r1, c1, r2, c2, choice;
    printf("\n\n    Matrix Operations    \n\n");
    printf("1. Addition\n2. Multiplication\n3. Transpose\n\nEnter choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        printf("Enter rows and cols for matrices: ");
        scanf("%d %d", &r1, &c1);
        readMatrix(matA, r1, c1);
        readMatrix(matB, r1, c1); // Must be same size
        addMatrices(matA, matB, r1, c1);
    } else if (choice == 2) {
        printf("\nEnter rows and cols for Matrix A: ");
        scanf("%d %d", &r1, &c1);
        printf("\nEnter rows and cols for Matrix B: ");
        scanf("%d %d", &r2, &c2);
        
        if (c1 != r2) {
            printf("\nError: Col of A must equal Row of B for multiplication.\n");
        } else {
            readMatrix(matA, r1, c1);
            readMatrix(matB, r2, c2);
            multiplyMatrices(matA, matB, r1, c1, c2);
        }
    } else if (choice == 3) {
        printf("\nEnter rows and cols for Matrix: ");
        scanf("%d %d", &r1, &c1);
        readMatrix(matA, r1, c1);
        transposeMatrix(matA, r1, c1);
    }
    else if (choice > 3) {
        printf("\nOops..! Invalid Set Operation.");
	}
    return 0;
}
