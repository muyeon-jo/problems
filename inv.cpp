#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE* input_fp;
FILE* output_fp;

int arr[100001];
int idx[100001];
int check[100001];
int leftArray[50001];
int rightArray[50001];
int n;
int calc(int index, int num) {
    int bigger = check[num]; // num보다 큰 숫자가 몇번 나왔는지 넣음
    int rest_bigger = n - num - bigger;
    int result = n - index - rest_bigger;
    for (int i = 1; i <= num; i++)
        check[i]++;

    return result;
}
long long inHalf(int start, int end) {
    if (end - start <= 1)
        return 0;

    long long sum = inHalf(start, (end + start) / 2) + inHalf((end + start) / 2, end);
    for (int i = start; i < (end + start) / 2; i++) {
        leftArray[i-start] = arr[i];
    }
    for (int i = (end + start) / 2; i < end; i++) {
        rightArray[i - (end + start) / 2] = arr[i];
    }
    int left = 0;
    int right = 0;

    for (int i = start; i < end; i++) {
        int temp_left = 210000000;
        int temp_right = 210000000;
        if (left < (end + start) / 2 - start) {
            temp_left = leftArray[left];
        }
        if (right < end - (end + start) / 2) {
            temp_right = rightArray[right];
        }
        if (temp_left < temp_right) {
            arr[i] = leftArray[left++];
        }
        else {
            arr[i] = rightArray[right++];
            sum += (end + start) / 2 - start - left;
        }
    }
    return sum;
}
int main() {
    input_fp = fopen("inv.inp", "rt");
    output_fp = fopen("inv.out", "wt");
    int T;
    fscanf(input_fp, "%d", &T);
    while (T--) {
        fscanf(input_fp, "%d", &n);
        long long sum = 0;
        for (int i = 0; i < n; i++) {
            fscanf(input_fp, "%d", &arr[i]);
        }
        sum = inHalf(0, n);
        fprintf(output_fp, "%lld\n", sum);

    }
    fclose(input_fp);
    fclose(output_fp);
    return 0;
}