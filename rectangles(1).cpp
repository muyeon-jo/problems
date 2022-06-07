#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

using namespace std;
FILE* input_fp, * output_fp;
typedef struct node {
    int w, h, sum;
}node_t;

node_t arr[10000];
int checker[10000];
int LEN = 0;

int compare(const void* a, const void* b) {
    return (*(node_t*)a).sum - (*(node_t*)b).sum;
     
}
void check() {
    for (int i = 0; i < LEN; i++) {
        for (int j = 0; j < i; j++) {
            if (checker[j] == 1) {
                continue;
            }
            if (arr[i].h * arr[j].w == arr[j].h * arr[i].w) {
                checker[i] = 1;
            }
        }
    }
}
void getTriple() {
    int sum = 0;
    int a, b, c;
    for (int m = 2;; m++) {
        int n = 1;
        if (m % 2 != 0) {//È¦¼ö¸é
            n++;
        }
        for (; n < m; n += 2) {
            a = m * m - n * n;
            b = 2 * m * n;
            if (a > b) {
                int temp = a;
                a = b;
                b = temp;
            }
            c = (a + b) * 2;
            arr[LEN++] = { a,b, c };
            
            sum += c;
        }

        if (sum > 10000000) {
            break;
        }
    }
    qsort(arr, LEN, sizeof(node_t), compare);

}
int main(){

    input_fp = fopen("rectangles.inp", "r");
    output_fp = fopen("rectangles.out", "w");
    getTriple();
    check();
    int T;
    fscanf(input_fp, "%d", &T);
    while (T--) {
        int L;
        fscanf(input_fp, "%d", &L);
        int sum = 0;
        int length = 0;
        for (int i = 0; ; i++) {
            if (checker[i] == 1) {
                continue;
            }

            sum += arr[i].sum;
            if (sum > L) {
                break;
            }
            length++;
        }
        fprintf(output_fp, "%d\n", length);

    }


    fclose(input_fp);
    fclose(output_fp);
    return 0;
}
