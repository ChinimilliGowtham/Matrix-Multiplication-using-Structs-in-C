#include <stdio.h>
#include <stdlib.h>

// Define a structure for a matrix
struct Matrix {
    int rows;
    int cols;
    int **data;
};

// Function to create a matrix
struct Matrix createMatrix(int rows, int cols) {
    struct Matrix mat;
    mat.rows = rows;
    mat.cols = cols;

    // Allocate memory for the matrix
    mat.data = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; ++i) {
        mat.data[i] = (int *)malloc(cols * sizeof(int));
    }

    // Initialize elements to zero
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            mat.data[i][j] = 0;
        }
    }

    return mat;
}

// Function to free memory allocated for the matrix
void freeMatrix(struct Matrix mat) {
    for (int i = 0; i < mat.rows; ++i) {
        free(mat.data[i]);
    }
    free(mat.data);
}

// Function to perform matrix multiplication
struct Matrix multiplyMatrices(const struct Matrix mat1, const struct Matrix mat2) {
    if (mat1.cols != mat2.rows) {
        printf("Error: Incompatible matrices for multiplication!\n");

        // Returning an empty matrix to indicate an error
        return createMatrix(0, 0);
    }

    struct Matrix result = createMatrix(mat1.rows, mat2.cols);
    for (int i = 0; i < mat1.rows; ++i) {
        for (int j = 0; j < mat2.cols; ++j) {
            for (int k = 0; k < mat1.cols; ++k) {
                result.data[i][j] += mat1.data[i][k] * mat2.data[k][j];
            }
        }
    }
    return result;
}

// Function to display a matrix
void displayMatrix(const struct Matrix mat) {
    for (int i = 0; i < mat.rows; ++i) {
        for (int j = 0; j < mat.cols; ++j) {
            printf("%d ", mat.data[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int rows1, cols1, rows2, cols2;

    printf("Enter dimensions of matrix 1 (rows columns): ");
    scanf("%d %d", &rows1, &cols1);

    printf("Enter dimensions of matrix 2 (rows columns): ");
    scanf("%d %d", &rows2, &cols2);

    struct Matrix mat1 = createMatrix(rows1, cols1);
    struct Matrix mat2 = createMatrix(rows2, cols2);

    printf("Enter elements of matrix 1:\n");
    for (int i = 0; i < rows1; ++i) {
        for (int j = 0; j < cols1; ++j) {
            scanf("%d", &mat1.data[i][j]);
        }
    }

    printf("Enter elements of matrix 2:\n");
    for (int i = 0; i < rows2; ++i) {
        for (int j = 0; j < cols2; ++j) {
            scanf("%d", &mat2.data[i][j]);
        }
    }

    printf("Matrix 1:\n");
    displayMatrix(mat1);

    printf("Matrix 2:\n");
    displayMatrix(mat2);

    struct Matrix result = multiplyMatrices(mat1, mat2);
    if (result.rows > 0 && result.cols > 0) {
        printf("Resultant matrix:\n");
        displayMatrix(result);
    }

    // Free memory allocated for matrices
    freeMatrix(mat1);
    freeMatrix(mat2);
    freeMatrix(result);

    return 0;
}
