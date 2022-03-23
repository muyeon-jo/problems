#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE* input_fp = fopen("coin.inp", "rt");
FILE* output_fp = fopen("coin.out", "wt");
int table[4][4][4] = { 0 };
void solve(int a, int b, int c) {
    int temp = 1;
    int ans = table[a][b][c] * -1;
    if (a == b && b == c && c == 0)
        return;
    for (int i = 0; i < 3; i++) {
        if (table[(a + i + 1) % 4][b][c] <= 0)
            table[(a + i + 1) % 4][b][c] = ans;
        if (table[a][(b + i + 1) % 4][c] <= 0)
            table[a][(b + i + 1) % 4][c] = ans;
        if (table[a][b][(c + i + 1) % 4] <= 0)
            table[a][b][(c + i + 1) % 4] = ans;
    }
}
int main() {
    int T;
    fscanf(input_fp, "%d", &T);
    while (T) {
        int a, b, c;
        fscanf(input_fp, "%d %d %d", &a, &b, &c);
        int A=1, B=1, C=1;

        table[0][0][0] = 1;
        table[1][0][0] = -1;
        table[0][1][0] = -1;
        table[0][0][1] = -1;
        
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                for (int k = 0; k < 4; k++) {
                    solve(i,j,k);
                }
            }
        }
        A = a%4;
        B = b%4;
        C = c%4;
        fprintf(output_fp, "(%d %d %d) : %d\n", a, b, c, table[A][B][C]);
        
        
        T--;
    }
    fclose(input_fp);
    fclose(output_fp);
    return 0;
}