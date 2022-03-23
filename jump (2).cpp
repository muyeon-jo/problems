#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE* input_fp = fopen("jump.inp", "rt");
FILE* output_fp = fopen("jump.out", "wt");
int arr[10000] = { 0 };
int compare(const void* x, const void* y) {
    return *(int*)x - *(int*)y;
}
int max(int x, int y) {
    if (x > y)
        return x;

    return y;
}
int min(int x, int y) {
    if (x > y)
        return y;

    return x;
}
int minDifrency(int pre_f, int pre_s, int next_f, int next_s) {
    if (next_s == 0) {
        return max(next_f - pre_f, next_f - pre_s);
    }
    return min(max(next_f - pre_f, next_s - pre_s), max(next_s - pre_f, next_f - pre_s));
}
int main() {
    int T;
    fscanf(input_fp, "%d", &T);
    while (T) {
        int N;
        fscanf(input_fp, "%d", &N);
        for (int i = 0; i < N; i++) {
            fscanf(input_fp, "%d", &arr[i]);
        }
        
        qsort(arr, N, sizeof(int), compare);
        int M = arr[1] - arr[0];
        for (int i = 0; i < N - 2; i += 2) {
            if (i + 3 >= N) {
                M = max(minDifrency(arr[i], arr[i + 1], arr[i + 2], 0), M);
            }
            else {
                M = max(minDifrency(arr[i], arr[i + 1], arr[i + 2], arr[i + 3]), M);
            }
        }
        fprintf(output_fp, "%d\n", M);
        T--;
    }
    fclose(input_fp);
    fclose(output_fp);
    return 0;
}