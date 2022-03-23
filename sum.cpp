#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

FILE* input_fp;
FILE* output_fp;
int compare1(const void* a,const void* b) {
    return *(int*)a - *(int*)b;
}
unsigned long long count;
int n;
int arr[10001];
int check[10001];
//int c[201][80001];
long long c[2][80001];

void calcSum(int n, int m) {//n:arr의 인덱스 m:숫자(w) 
    for (int i = 1; i <= m; i++) {//첫 행은 숫자 없기 때문에 무조건 0
        c[0][i] = 0;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (c[(i - 1)%2][j] > 0) {//앞에서 만들 수 있는 숫자다
                c[i % 2][j] += c[(i - 1) % 2][j] % 100000;//arr[i-1] 없이도 만들어지므로 그대로 내려온다
                if (j + arr[i - 1] <= m) {
                    c[i % 2][j + arr[i - 1]] += c[(i - 1) % 2][j] % 100000;//그대로 내려온 값만큼  + arr[i-1]한 위치에 더한다
                }
            }

            if (j == arr[i - 1]) {//숫자 하나로 만들 수 있음
                c[i % 2][j] = (c[i % 2][j] + 1) % 100000;
            }
        }
        for (int j = 1; j <= m; j++) {
            c[(i - 1) % 2][j] = 0;
        }
    }
    /*
    for (int i = 1; i <= m; i++) {//첫 행은 숫자 없기 때문에 무조건 0
        c[0][i] = 0;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (c[i - 1][j] > 0) {//앞에서 만들 수 있는 숫자다
                c[i][j] += c[i - 1][j];//arr[i-1] 없이도 만들어지므로 그대로 내려온다
                c[i][j + arr[i - 1]] += c[i - 1][j];//그대로 내려온 값만큼  + arr[i-1]한 위치에 더한다
            }
            
            if (j == arr[i - 1]) {//숫자 하나로 만들 수 있음
                c[i][j]++;
            }
        }

    }*/
}
void calcSubSet(int index, int W) {
    if (W == 0) {
        count++;
        return;
    }
    if (W < 0)
        return;
    if (index == n) {
        return;
    }
        calcSubSet(index + 1, W - arr[index]);
        calcSubSet(index + 1, W);
}
int main() {
    input_fp = fopen("sum.inp", "rt");
    output_fp = fopen("sum.out", "wt");
    int T;
    fscanf(input_fp, "%d", &T);
    while (T--) {
        int w;
        fscanf(input_fp, "%d %d", &n, &w);
        for (int i = 0; i < n; i++) {
            fscanf(input_fp, "%d", &arr[i]);
        }
        qsort(arr, n, sizeof(int), compare1);
        for (int i = 0; i <= w; i++) {
            c[1][i] = 0;
            c[0][i] = 0;
        }
        calcSum(n, w);
        
        fprintf(output_fp, "%lld\n", c[n % 2][w] % 100000);
        count = 0;
    }
    fclose(input_fp);
    fclose(output_fp);
    return 0;
}