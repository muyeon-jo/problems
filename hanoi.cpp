#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE* input_fp = fopen("hanoi.inp", "rt");
FILE* output_fp = fopen("hanoi.out", "wt");
int arr[25] = { 0 };
int sequence[25] = { 0 };
int f[25] = { 0 };
int color[25] = { 0 };
int sum = 0;
void matchColor(int n) {
    if (sequence[n] != color[n] && arr[n] > 1) {//한번 뒤집어야됨
        sequence[n] *= -1;
        if (n >= 1) {
            sequence[n - 1] *= -1;
            sum += arr[n] + f[n - 1];
        }
        else {
            sum += arr[n] - 1;
        }
    }
}
int getf(int n) {
    if (n == 0) {
        f[0] = arr[0];
        return arr[0];
    }
    if (f[n] != 0)
        return f[n];
    f[n] = getf(n - 1) * 2 + arr[n];
    return getf(n - 1) * 2 + arr[n];
    
}
int main() {
    int T;
    fscanf(input_fp, "%d", &T);
    while (T) {
        int n;
        char temp[25] = { 0 };
        sum = 0;
        
        fscanf(input_fp, "%d", &n);

        for (int i = 0; i < n; i++) {
            fscanf(input_fp, " %c %d", &temp[i], &arr[i]);
            if (temp[i] == 'B') {
                sequence[i] = 1;
                color[i] = 1;
            }
            else if (temp[i] == 'R') {
                sequence[i] = 1;
                color[i] = -1;
            }
            else {
                sequence[i] = 0;
                color[i] = 0;
            }
        }
        getf(n - 1);
        sequence[n - 1] *= -1;

        for(int i=n-1;i>=0;i--){
            matchColor(i);
        }

        sum += f[n - 1];
        fprintf(output_fp, "%d\n", sum);
        for (int i = 0; i < n; i++) {
            f[i] = 0;
        }
        T--;
    }
    fclose(input_fp);
    fclose(output_fp);
    return 0;
}