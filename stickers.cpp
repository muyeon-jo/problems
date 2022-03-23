#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE* input_fp;
FILE* output_fp;
int original[2][100000] = { 0 };
int duplicant[2][100000] = { 0 };
int n;
int max(int x, int y) {
    if (x > y)
        return x;
    return y;

}
int main() {
    input_fp = fopen("stickers.inp", "rt");
    output_fp = fopen("stickers.out", "wt");
    int T;
    fscanf(input_fp, "%d", &T);
    while (T--) {
        fscanf(input_fp, "%d", &n);
        for (int j = 0; j < 2; j++) {
            for (int i = 0; i < n; i++) {
                fscanf(input_fp, "%d", &original[j][i]);
            }
        }
        duplicant[0][0] = original[0][0];
        duplicant[1][0] = original[1][0];
        duplicant[0][1] = duplicant[1][0] + original[0][1];
        duplicant[1][1] = duplicant[0][0] + original[1][1];
        for (int i = 2; i < n; i++) {
            for (int j = 0; j < 2; j++) {
                duplicant[j][i] = max(duplicant[(j + 1) % 2][i - 1], duplicant[(j + 1) % 2][i - 2]) + original[j][i];
            }
        }
        int sum = max(duplicant[0][n - 1], duplicant[1][n - 1]);
        fprintf(output_fp, "%d\n", sum);
    }
    fclose(input_fp);
    fclose(output_fp);
    return 0;
}