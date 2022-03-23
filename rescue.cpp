#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE* input_fp;
FILE* output_fp;
int arr[10000];
int DP[2][10001];
int max(int a, int b) {
    if (a > b)
        return a;
    return b;
}
int rescue(int floor, int last) {
    static int memo[2][10001];
    if (floor <= 0)
        return 0;
    if (floor == 1) {
        return arr[floor - 1];
    }
    if (memo[last][floor] != 0)
        return memo[last][floor];

    int m = arr[floor - 1];
    if (last) {
        m += rescue(floor - 2, 0);
    }
    else {
        m += max(rescue(floor - 1, 1), rescue(floor - 2, 0));
    }
    return memo[last][floor] = m;
}
void rescueDP(int n) {
    DP[0][1] = arr[0];
    DP[1][1] = arr[0];
    for (int i = 2; i <= n; i++) {
        
        DP[1][i] = arr[i - 1] + DP[0][i - 2];
        DP[0][i] = arr[i - 1] + max(DP[0][i - 2], DP[1][i - 1]);
    }
}
int main() {
    input_fp = fopen("rescue.inp", "rt");
    output_fp = fopen("rescue.out", "wt");
    int T;
    fscanf(input_fp, "%d", &T);
    while (T--) {
        int n;
        fscanf(input_fp, "%d", &n);
        for (int i = 0; i < n; i++) {
            fscanf(input_fp, "%d", &arr[i]);

        }
        rescueDP(n);
        fprintf(output_fp, "%d\n",max(DP[1][n], DP[0][n]));
    }
    fclose(input_fp);
    fclose(output_fp);
    return 0;
}