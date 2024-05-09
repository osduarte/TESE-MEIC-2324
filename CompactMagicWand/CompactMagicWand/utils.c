/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "utils.h"
#pragma warning(disable : 4996)

void printData2D(int row, int column, float matrix[Maxrow][Maxcolumn]) {
    int i, j;

    printf("[");
    for (i = 0; i < row; i++) {
        printf("[");

        for (j = 0; j < column; j++) {
            if(j < column-1) printf("%.4f,\t", matrix[i][j]);
            else printf("%.4f", matrix[i][j]);
        }

        if(i < row-1) printf("],\n");
        else printf("]");
    }
    printf("]");
    fflush(stdin);
}

void printData3D(int row, int column, int depth, float matrix[Maxrow][Maxcolumn][Maxdepth]) {
    int i, j, d;

    printf("[");
    for (d = 0; d < depth; d++) {
        printf("[");
        for (i = 0; i < row; i++) {
            printf("[");

            for (j = 0; j < column; j++) {
                if (j < column - 1) printf("%.20f,\t", matrix[i][j][d]);
                else printf("%.20f", matrix[i][j][d]);
            }

            if (i < row - 1) printf("],\n");
            else printf("]");
        }
        if (d < depth - 1) printf("],\n\n");
        else printf("]");
    }
    printf("]");
    fflush(stdin);
}

void write2File(float data[], int size, char fileName[]) {

    int i;

    FILE *file = fopen(fileName, "w");
    if (file == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    for(i = 0; i < size; i++) {
        fprintf(file, "%.20f\n", data[i]);
    }

    fclose(file);
}

void compareFiles(char file1Name[], char file2Name[]) {

    printf("start compare files!\n");

    FILE *file1 = fopen(file1Name, "r");
    FILE *file2 = fopen(file2Name, "r");
    FILE *file3 = fopen("../ErrorsFile.txt", "w");
    int counter = 0;
    int aux[64];
    float val1, val2;
    float error, max_error = 0, avg_error = 0, quad_error = 0;
    char buffer[255];

    while (fscanf(file1, "%s", buffer) == 1) // expect 1 successful conversion
    {
        val1 = strtof(buffer, NULL);
        if(fscanf(file2, "%s", buffer) == 1) {
            if (_stricmp(buffer, "\n") != 0) {
                val2 = strtof(buffer, NULL);
                error = fabsf(val1 - val2);

                printf("Error: %.20f:\n\tBits-> ", error);
                fprintf(file3, "%.30f\n", error);
                if (error > 0) {
                   twoComplement(1 / error, aux);
                }
                printf("\n\n");

                if (error > max_error) max_error = error;
                avg_error += error;
                quad_error += sqrtf(error);

                counter++;
            }

        } else {
            printf("Files with different sizes!\n");
            return;
        }
        
    }
    avg_error = avg_error/(float)counter;
    quad_error = quad_error/(float)counter;

    printf("Max Error: %.20f", max_error);
    printf("\nAverage Error: %.20f", avg_error);
    printf("\nQuadratic Error: %.20f\n", quad_error);

    fclose(file1);
    fclose(file2);
    fclose(file3);
}

void twoComplement(float val, int out[64]) {

    val = (val > (floorf(val)+0.5f)) ? ceilf(val) : floorf(val);

    int ex = (int)floorf(log2f(val));
    out[ex] = 1;
    printf("%d-", ex);

    if((val - pow(2, ex)) > 0) twoComplement((val - powf(2, (float)ex)), out);

}

void twoComplement2File(FILE* file, float val, int out[64]) {

    val = (val > (floorf(val)+0.5f)) ? ceilf(val) : floorf(val);

    int ex = (int)floorf(log2f(val));
    out[ex] = 1;
    fprintf(file, "%d-", ex);

    if((val - pow(2, ex)) > 0) twoComplement2File(file, (val - powf(2, (float)ex)), out);

}*/