#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int compare(const void* a, const void* b) {
    return *(int*)a - *(int*)b;
}
int main() {
    FILE* fp_in, * fp_out;
    fp_in = fopen("sequence.inp", "r");
    fp_out = fopen("sequence.out", "w");

    int n;
    fscanf(fp_in, "%d", &n);
    int* arr = (int*)malloc(sizeof(int) * n);
    int* answer = (int*)malloc(sizeof(int) * n);
    int* C = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        fscanf(fp_in, "%d", &arr[i]);
    }
    for (int i = 0; i < n; i++) {
        fscanf(fp_in, "%d", &C[i]);
    }


    qsort(arr, n, sizeof(int), compare);
    for (int i = n - 1; i >= 0; i--) {
        int temp = C[i];
        int now = -1;
        int count = -1;
        for (int j = 0; j < n; j++) {
            if (arr[j] != -1) {
                now = arr[j];
                count++;
                if (count == C[i]) {
                    arr[j] = -1;
                    answer[i] = now;
                    break;
                }
            }
        }


    }

    for (int i = 0; i < n; i++) {
        fprintf(fp_out, "%d\n", answer[i]);
    }
    fclose(fp_in);
    fclose(fp_out);
    return 0;
}