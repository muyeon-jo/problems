#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define P 1000000007
FILE* input_fp = fopen("addingways.inp", "rt");
FILE* output_fp = fopen("addingways.out", "wt");
int addingWay(int n, int k, int min) {
    static int memo[21][301] = { 0 };//k,n
    int sum = 0;
    n = n - (k * (min - 1));
    if (n < k)
        return 0;
    if (k == 0)
        return 0;
    if (k == 1) {
        return memo[k][n]=1;
    }
    if (memo[k][n] != 0) {
        return memo[k][n];
    }
    
    for (int i = 1; i <= n; i++) {
        
        sum += addingWay(n-i, k - 1, i);
        sum %= P;
    }
    if (memo[k][n] == 0) {
        memo[k][n] = sum % P;
    }
    return sum % P;
}
int main() {
    int n, k;
    int sum = 0;
    do {
        fscanf(input_fp, "%d %d", &n, &k);
        if (n == 0 && k == 0)
            break;
        sum = 0;
        sum = addingWay(n, k, 1);

        fprintf(output_fp, "%d\n", sum);
    } while (n != 0 && k != 0);

    fclose(input_fp);
    fclose(output_fp);
    return 0;
}