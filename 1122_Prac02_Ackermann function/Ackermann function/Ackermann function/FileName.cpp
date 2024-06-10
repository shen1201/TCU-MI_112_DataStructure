#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE* file;
    int A[3][3], B[3][3], C[3][3];
    char matrixName;
    int i, j;

    file = fopen("02.txt", "r");
    if (file == NULL) {
        perror("無法打開檔案");
        return 1;
    }

    while (!feof(file)) {
        fscanf(file, "%c", &matrixName); // 讀取矩陣名稱
        if (matrixName == 'A' || matrixName == 'B' || matrixName == 'C') {
            // 跳過換行符
            fgetc(file);
            for (i = 0; i < 3; i++) {
                for (j = 0; j < 3; j++) {
                    if (matrixName == 'A') {
                        fscanf(file, "%d", &A[i][j]);
                    }
                    else if (matrixName == 'B') {
                        fscanf(file, "%d", &B[i][j]);
                    }
                    else if (matrixName == 'C') {
                        fscanf(file, "%d", &C[i][j]);
                    }
                }
            }
        }
    }

    fclose(file);

    // 測試：打印A矩陣
    printf("A矩陣：\n");
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            printf("%d ", A[i][j]);
        }
        printf("\n");
    }
    printf("B矩陣：\n");
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            printf("%d ", B[i][j]);
        }
        printf("\n");
    }
    printf("C矩陣：\n");
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    int A_t[3][3] = {};
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            int temp = A[i][j];
            A_t[j][i] = temp;
        }
    }

    printf("A^T:\n");
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            printf("%d ", A_t[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    int D[3][3] = {};
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                D[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    printf("A*T:\n");
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            printf("%d ", D[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            D[i][j] += C[i][j];
        }
    }

    printf("A*B+C:\n");
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            printf("%d ", D[i][j]);
        }
        printf("\n");
    }


    return 0;
}