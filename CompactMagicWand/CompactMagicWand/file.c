/*#include <stdio.h>
#include "file.h"
#include "model_functions.h"
#include "utils.h"
#include "parameters.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#pragma warning(disable : 4996)

//copiar para ficheiro main.c

FILE* openFile(char name[], const char * mode) {
    FILE * file;

    file = fopen(name, mode);

    if (NULL == file) {
        printf("File can't be opened \n");
    }

    return file;
}

void closeFile(FILE* file) {
    fclose(file);
}

void readFile(FILE* file) {

    char buff[BUFFER_SIZE];
    bool init = true, isReading = false, wasReading = false;
    float dt[BATCH][DATA_SIZE];
    int i, cnt = 0;

    FILE *out = fopen("../test.txt", "w");
    if (out == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    for (i = 0; i < BATCH; i++) {
        dt[i][0] = 0;
        dt[i][1] = 0;
        dt[i][2] = 0;
    }

    while (fgets(buff, BUFFER_SIZE, file) != NULL) {
        if (wasReading && !isReading) {
            float data[BATCH][DATA_SIZE];

            for (i = 0; i < cnt; i++) {
                data[BATCH-cnt+i][0] = dt[i][0];
                data[BATCH-cnt+i][1] = dt[i][1];
                data[BATCH-cnt+i][2] = dt[i][2];
            }
            for (i = cnt; i < BATCH; i++) {
                data[i-cnt][0] = 0;
                data[i-cnt][1] = 0;
                data[i-cnt][2] = 0;
            }

            float conv1[BATCH][DATA_SIZE][FIRST_NUM_KERNELS];
            float max1[42][1][FIRST_NUM_KERNELS];
            float conv2[42][1][SECOND_NUM_KERNELS];
            float max2[14][1][SECOND_NUM_KERNELS];
            float den1[1][THIRD_NUM_KERNELS];
            float den2[1][FOURTH_NUM_KERNELS];
            float sMax[1][FOURTH_NUM_KERNELS];

            
            convolution1(BATCH, DATA_SIZE, data, FIRST_NUM_ROWS, FIRST_NUM_COLS, FIRST_NUM_KERNELS, firstKernel, firstBias, conv1);
            printData3D(BATCH, DATA_SIZE, FIRST_NUM_KERNELS, conv1);
            maxPool(BATCH, DATA_SIZE, FIRST_NUM_KERNELS, conv1, 42, 1, max1, 3, 3);
            convolution2(42, 1, FIRST_NUM_KERNELS, max1, SECOND_NUM_ROWS, SECOND_NUM_COLS, SECOND_NUM_KERNELS, secondKernel, secondBias, conv2);
            maxPool(42, 1, SECOND_NUM_KERNELS, conv2, 14, 1, max2, 3, 1);
            dense1(14, 1, SECOND_NUM_KERNELS, max2, THIRD_NUM_ROWS, THIRD_NUM_COLS, THIRD_NUM_KERNELS, firstDense, thirdBias, THIRD_NUM_KERNELS, den1[0]);
            dense2(THIRD_NUM_KERNELS, den1[0], FOURTH_NUM_SIZE, FOURTH_NUM_KERNELS, secondDense, fourthBias, FOURTH_NUM_KERNELS, den2[0]);
            softmax(FOURTH_NUM_KERNELS, den2[0], sMax[0]);
            


            printf("\nOut:\n");
            printData2D(1, FOURTH_NUM_KERNELS, sMax);
            printf("\n\n\n\n");
            for(i = 0; i < 4; i++) {
                fprintf(out, "%.30f\n", sMax[0][i]);
            }
            fprintf(out, "\n");

            for (i = 0; i < DATA_SIZE; i++) {
                dt[0][i] = 0;
                dt[1][i] = 0;
                dt[2][i] = 0;
            }
            cnt = 0;
        }
        wasReading = isReading;

        if (stricmp(buff, " -,-,-\n") == 0 || stricmp(buff, "-,-,-\n") == 0) init = true, isReading = true;
        else if (stricmp(buff, "\n") == 0) isReading = false;
        else if (isReading){
            float f1, f2, f3;
            isReading = false;

            char *pt = strtok(buff, ",");
            if (pt != NULL) {
                f1 = strtof(pt, NULL);
            } else continue;
            pt = strtok(NULL, ",");
            if (pt != NULL) {
                f2 = strtof(pt, NULL);
            } else continue;
            pt = strtok(NULL, ",");
            if (pt != NULL) {
                f3 = strtof(pt, NULL);
            } else continue;

            if (init) init = false;

            dt[cnt][0] = f1;
            dt[cnt][1] = f2;
            dt[cnt][2] = f3;
            cnt++;
            if (cnt == 128) isReading = false;
            else isReading = true;
        }
    }
    fclose(out);
}
*/