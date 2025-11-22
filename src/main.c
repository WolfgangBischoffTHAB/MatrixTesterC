// Msys2: install gcc: 
// pacman -S mingw-w64-ucrt-x86_64-gcc
// gcc.exe is installed to C:\msys64\mingw64\bin
// Add it to the path environment variable
// set PATH=%PATH%;C:\msys64\mingw64\bin\
//
// Compile an application:
// gcc main.c

#include <stdio.h>

//const static int DIMENSION = 4;
#define DIMENSION 4
#define ELEMENTS DIMENSION*DIMENSION

void printMatrix(int* matrix, int dim);
void prettyPrintFormatMatrix(int* matrix, int dim, const char* format);
void identityMatrix(int* matrix, int dim);
void zeroMatrix(int* matrix, int dim);
void upCountingMatrix(int* matrix, int dim);
void standardMatrixMult(int* matrixA, int* matrixB, int* matrixC, int rows, int columns);
void segmentedMatrixMult(int* matrixA, int* matrixB, int* matrixC, int rows, int columns);
//void matrixAdd(int* matrixA, int* matrixB, int* matrixC, int rows, int columns);
void matrixAddInto(int* matrixA, int* matrixB, int rows, int columns);
void getSubMatrix(int* matrix, int dim, int xPos, int yPos, int width, int height, int* matrixC);
void setSubMatrix(int* matrix, int dim, int xPos, int yPos, int width, int height, int* matrixC);

int main()
{
    printf("Matrix\n");

    int matrixA[ELEMENTS] = {
        9, 0, 9, 4,
        2, 6, 6, 7,
        9, 3, 8, 1,
        6, 9, 7, 1
    };
    int matrixB[ELEMENTS] = {
        1, 2, 4, 2,
        8, 6, 0, 0,
        7, 6, 8, 5,
        8, 4, 7, 5
    };
    int matrixC[ELEMENTS] = {
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0
    };

    int sub[4] = {
        0, 0, 
        0, 0
    };
    int subSetTest[4] = {
        1, 2, 
        3, 4
    };

    //setSubMatrix(matrixC, DIMENSION, 0, 0, 2, 2, subSetTest);
    //setSubMatrix(matrixC, DIMENSION, 1, 1, 2, 2, subSetTest);
    //prettyPrintFormatMatrix(matrixC, 4, "%6d");

    //matrixAddInto(matrixC, matrixA, 4, 4);
    //matrixAddInto(matrixC, matrixA, 4, 4);
    //prettyPrintFormatMatrix(matrixC, 4, "%6d");

    //getSubMatrix(matrixA, DIMENSION, 0, 0, 2, 2, sub);
    //getSubMatrix(matrixA, DIMENSION, 1, 0, 2, 2, sub);
    //getSubMatrix(matrixA, DIMENSION, 2, 2, 2, 2, sub);
    //getSubMatrix(matrixA, DIMENSION, 0, 0, 3, 2, sub);
    //getSubMatrix(matrixA, DIMENSION, 0, 1, 3, 2, sub);
    //getSubMatrix(matrixA, DIMENSION, 0, 2, 3, 2, sub);
    //getSubMatrix(matrixA, DIMENSION, 0, 0, 1, 4, sub);
    
    //prettyPrintFormatMatrix(sub, 2, "%6d");

    //identityMatrix(matrixA, DIMENSION);

    upCountingMatrix(matrixA, DIMENSION);
    upCountingMatrix(matrixB, DIMENSION);
    //zeroMatrix(matrixC, DIMENSION);
    
    //printMatrix(matrixA, DIMENSION);
    //printMatrix(matrixB, DIMENSION);
    printf("A\n");
    prettyPrintFormatMatrix(matrixA, DIMENSION, "%6d");
    printf("B\n");
    prettyPrintFormatMatrix(matrixB, DIMENSION, "%6d");

    //standardMatrixMult(matrixA, matrixB, matrixC, DIMENSION, DIMENSION);
    segmentedMatrixMult(matrixA, matrixB, matrixC, DIMENSION, DIMENSION);

    printf("C\n");
    prettyPrintFormatMatrix(matrixC, DIMENSION, "%6d");

    // int[] intArray = new int[] {
    //             104, 88, 136, 83,
    //             148, 104, 105, 69,
    //             97, 88, 107, 63,
    //             135, 112, 87, 52
    //     };
    
    return 0;
}

/*
void subMatrix(int* matrix, int dim, int xPos, int yPos, int width, int height, int* matrixC) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {

            int tempData = matrix[(yPos + i) * dim + (xPos + j)];
            //printf("%d\n", tempData);

            matrixC[i * width + j] = tempData;
            //matrixC[(yPos + i) * width + (xPos + j)] = tempData;
        }
    }
}
*/

void matrixAddInto(int* matrixA, int* matrixB, int rows, int columns) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            matrixA[i * rows + j] += matrixB[i * rows + j];
        }
    }
}

void getSubMatrix(int* matrix, int dim, int xPos, int yPos, int width, int height, int* matrixC) {
    int innerI = 0;
    for (int i = xPos; i < xPos + width; i++) {
        int innerJ = 0;
        for (int j = yPos; j < yPos + height; j++) {
            matrixC[innerI * width + innerJ] = matrix[i * dim + j];
            innerJ++;
        }
        innerI++;
    }
}

void setSubMatrix(int* matrix, int dim, int xPos, int yPos, int width, int height, int* matrixC) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int tempData = matrixC[i * width + j];
            matrix[(yPos + i) * dim + (xPos + j)] = tempData;
        }
    }
}

void segmentedMatrixMult(int* matrixA, int* matrixB, int* matrixC, int rows, int columns) {
    
    int nc = 2; // subset size
    int rowSteps = rows / nc;

    int kc = 2; // subset size
    int columnsSteps = columns / kc;

    int mc = 2; // subset size
    int innerSteps = rows / nc;

    //
    // ACT
    //

    // DEBUG
    int iterationCounter = 0;

    // for jc = 0 to n-1 step nc
    // Loop 1
    for (int jc = 0; jc < rowSteps; jc++) {

        // for pc = 0 to k-1 step kc
        // Loop 2
        for (int pc = 0; pc < columnsSteps; pc++) {

            //int* subMatrixB = subMatrix(matrixB, pc * kc, jc * nc, kc, nc);
            int subMatrixB[2*2];
            getSubMatrix(matrixB, DIMENSION, pc * kc, jc * nc, kc, nc, subMatrixB);

            // for ic = 0 to m-1 step mc
            // Loop 3
            for (int ic = 0; ic < innerSteps; ic++) {

                //Matrix subMatrixA = matrixA.getSubMatrix(ic * mc, pc * kc, mc, kc);
                int subMatrixA[2*2] = { 0, 0, 0, 0 };
                getSubMatrix(matrixA, DIMENSION, ic * mc, pc * kc, mc, kc, subMatrixA);

                printf("[\n");
                prettyPrintFormatMatrix(subMatrixA, 2, "%6d");
                printf("------------------------\n");
                prettyPrintFormatMatrix(subMatrixB, 2, "%6d");
                printf("]\n");

                iterationCounter++;                

                // perform a matrix mult of the sub matrices
                //Matrix temp = subMatrixA.mult(subMatrixB);
                int tempMult[2*2] = { 0, 0, 0, 0 };
                standardMatrixMult(subMatrixA, subMatrixB, tempMult, 2, 2);

                //printf("+++++++++++++++++++++++++++++\n");
                //prettyPrintFormatMatrix(tempMult, 2, "%6d");
                //printf("+++++++++++++++++++++++++++++\n");

                // // retrieve sub matrix to accumulate into
                // Matrix accumulatorSubMatrixC = matrixC.getSubMatrix(ic * kc, jc * nc, nc, kc);
                int tempAccum[2*2] = { 0, 0, 0, 0 };
                getSubMatrix(matrixC, DIMENSION, ic * kc, jc * nc, nc, kc, tempAccum);

                // // accumulate the result
                // accumulatorSubMatrixC.add(temp);
                matrixAddInto(tempAccum, tempMult, 2, 2);

                // // place the accumulator back into the large result matrix
                // matrixC.setSubMatrix(jc * nc, ic * kc, nc, kc, accumulatorSubMatrixC);
                setSubMatrix(matrixC, DIMENSION, jc * nc, ic * kc, nc, kc, tempAccum);

            }
        }
    }

    printf("%d\n", iterationCounter);
}

void standardMatrixMult(int* matrixA, int* matrixB, int* matrixC, int rows, int columns) {
    // over row of matrix B
    for (int i = 0; i < rows; i++) {
        // over column of matrix A
        for (int j = 0; j < columns; j++) {
            // fuse row and column together into a single cell of matrix C
            for (int k = 0; k < columns; k++) {
                matrixC[i * rows + j] += matrixA[i * columns + k] * matrixB[k * columns + j];
            }
        }
    }
}

void printMatrix(int* matrix, int dim) {
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            printf("%d ", matrix[dim*i + j]);
        }
        printf("\n");
    }
}

void prettyPrintFormatMatrix(int* matrix, int dim, const char* format) {
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            printf(format, matrix[dim*i + j]);
        }
        printf("\n");
    }
}

void identityMatrix(int* matrix, int dim) {
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            matrix[dim*i + j] = (i==j) ? 1 : 0;
        }
    }
}

void zeroMatrix(int* matrix, int dim) {
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            matrix[dim*i + j] = 0;
        }
    }
}

void upCountingMatrix(int* matrix, int dim) {
    int count = 1;
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            matrix[dim*i + j] = count;
            count++;
        }
    }
}