#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE* input_fp = fopen("jump.inp", "rt");
FILE* output_fp = fopen("jump.out", "wt");

int main() {
    int T;
    fscanf(input_fp, "%d", &T);
    while (T) {
        int n;
        fscanf(input_fp, "%d", &n);
        int* arr = (int*)malloc(sizeof(int) * n);
        int* sum = (int*)malloc(sizeof(int) * n);
        for (int i = 0; i < n; i++) {
            fscanf(input_fp, "%d", &arr[i]);
            sum[i] = arr[i];
        }
        
        int max = -1;
        for (int i = n - 1; i >= 0; i--) {
            if (i + sum[i] < n) {
                sum[i] += sum[i + sum[i]];
                
            }

            if (sum[i] > max)
                max = sum[i];
        }

        fprintf(output_fp, "%d\n", max);
        T--;
    }
    fclose(input_fp);
    fclose(output_fp);
    return 0;
}