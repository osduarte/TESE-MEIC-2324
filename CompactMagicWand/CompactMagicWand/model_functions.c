#include <stdio.h>
#include "model_functions.h"
#include <math.h>

//valores máximos no define
//mRowMax, etc
//typedef - como fazer
void convolution1(int mRow, int mCol, float m[MaxmRowC1][MaxmColC1], int kRow, int kCol, int kNum, float k[MaxkNumC1][MaxkRowC1][MaxkColC1], float bias[MaxkNumC1], float out[MaxmRowC1][MaxmColC1][MaxkRowC1]) {

    int d, i, j;

    for (d = 0; d < kNum; d++) {
        for (i = 0; i < mRow; i++) {
            for (j = 0; j < mCol; j++) {

                out[i][j][d] = m[i][j] * k[d][1][1] + bias[d];

                if (i - 1 >= 0) {
                    out[i][j][d] += m[i - 1][j] * k[d][0][1];
                    if (j - 1 >= 0) out[i][j][d] += m[i - 1][j - 1] * k[d][0][0] + m[i][j - 1] * k[d][1][0];
                    if (j + 1 < mCol) out[i][j][d] += m[i - 1][j + 1] * k[d][0][2] + m[i][j + 1] * k[d][1][2];
                }
                else {
                    if (j - 1 >= 0) out[i][j][d] += m[i][j - 1] * k[d][1][0];
                    if (j + 1 < mCol) out[i][j][d] += m[i][j + 1] * k[d][1][2];
                }
                if (i + 2 < mRow) {
                    out[i][j][d] += m[i + 1][j] * k[d][2][1] + m[i + 2][j] * k[d][3][1];
                    if (j - 1 >= 0) out[i][j][d] += m[i + 1][j - 1] * k[d][2][0] + m[i + 2][j - 1] * k[d][3][0];
                    if (j + 1 < mCol) out[i][j][d] += m[i + 1][j + 1] * k[d][2][2] + m[i + 2][j + 1] * k[d][3][2];
                }
                else if (i + 1 < mRow) {
                    out[i][j][d] += m[i + 1][j] * k[d][2][1];
                    if (j - 1 >= 0) out[i][j][d] += m[i + 1][j - 1] * k[d][2][0];
                    if (j + 1 < mCol) out[i][j][d] += m[i + 1][j + 1] * k[d][2][2];
                }

                if (out[i][j][d] < 0) out[i][j][d] = 0;
            }
        }
    }
}

void convolution2(int mRow, int mCol, int mDep, float m[MaxmRowC2][MaxmColC2][MaxmDepC2], int kRow, int kCol, int kNum, float k[MaxkNumC2][MaxkRowC2][MaxkColC2], float bias[MaxkNumC2], float out[MaxmRowC2][MaxmColC2][MaxkNumC2]) {

    int d, h, i, j;

    for (d = 0; d < kNum; d++) {
        for (i = 0; i < mRow; i++) {
            for (j = 0; j < mCol; j++) {

                out[i][j][d] = bias[d];
                for (h = 0; h < mDep; h++) {
                    out[i][j][d] += m[i][j][h] * k[d][1][h];
                }

                if (i - 1 >= 0) {
                    for (h = 0; h < mDep; h++) {
                        out[i][j][d] += m[i - 1][j][h] * k[d][0][h];
                    }
                }
                if (i + 2 < mRow) {
                    for (h = 0; h < mDep; h++) {
                        out[i][j][d] += m[i + 1][j][h] * k[d][2][h] + m[i + 2][j][h] * k[d][3][h];
                    }
                }
                else if (i + 1 < mRow) {
                    for (h = 0; h < mDep; h++) {
                        out[i][j][d] += m[i + 1][j][h] * k[d][2][h];
                    }
                }

                if (out[i][j][d] < 0) out[i][j][d] = 0;
            }
        }
    }
}

void maxPool(int mRow, int mCol, int mDep, float m[MaxmRowMP][MaxmColMP][MaxmDepMP], int oRow, int oCol, float out[MaxmRowMP][MaxmColMP][MaxmDepMP], int kRow, int kCol) {

    int i, j, d;

    for (d = 0; d < mDep; d++) {
        for (i = 0; i < mRow; i++) {
            if (i / kRow == oRow) break;
            if (i % kRow == 0) {
                out[i / kRow][0][d] = 0;
            }
            for (j = 0; j < mCol; j++) {
                out[i / kRow][0][d] = max(out[i / kRow][0][d], m[i][j][d]);
            }
        }
    }
}

void dense1(int mRow, int mCol, int mDep, float m[MaxmRowD1][MaxmColD1][MaxmDepD1], int kRow, int kCol, int kNum, float k[MaxkNumD1][MaxkRowD1][MaxkColD1], float bias[MaxkNumD1], int oSize, float out[MaxoSizeD1]) {

    int d, h, i, j;

    for (d = 0; d < kNum; d++) {
        out[d] = bias[d];
        for (i = 0; i < mRow; i++) {
            for (j = 0; j < mCol; j++) {
                for (h = 0; h < mDep; h++) {
                    out[d] += m[i][j][h] * k[d][i][h];
                }
            }
        }
        if (out[d] < 0) out[d] = 0;
    }
}

void dense2(int mSize, const float m[MaxmSizeD2], int kSize, int kNum, float k[MaxkNumD2][MaxkSizeD2], const float bias[MaxkNumD2], int oSize, float out[MaxoSizeD2]) {

    int d, i;

    for (d = 0; d < kNum; d++) {
        out[d] = bias[d];
        for (i = 0; i < mSize; i++) {
            out[d] += m[i] * k[d][i];
        }
    }
}

void softmax(int mSize, float m[MaxmSizeSM], float out[MaxmSizeSM]) {

    int i;
    double sum = 0;

    for (i = 0; i < mSize; i++) {
        sum += exp((double)m[i]);
    }

    for (i = 0; i < mSize; i++) {
        out[i] = (float)(exp((double)m[i]) / sum);
    }
}