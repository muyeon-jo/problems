#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
FILE* input_fp;
FILE* output_fp;
long long getNum(int Bit[32]) {
    long long  std = 1;
    long long sum = 0;
    for (int i = 0; i < 32; i++) {
        if (Bit[i] == 1) {
            sum += std;
        }
        std *= 2;
    }
    return sum;
}
long long calc(int aBit[32], int bBit[32]) {
    int sumBit[32] = { 0 };
    for (int i = 0; i < 32; i++) {
        sumBit[i] = aBit[i] + bBit[i];
    }
    return getNum(sumBit);
}

void getBits(int bit[32],long long target) {
    long long std = 1;
    for (int i = 0; i < 31; i++) {
        std *= 2;
    }

    for (int i = 31; i >= 0; i--) {
        if (target >= std) {
            bit[i] = 1;
            target -= std;
        }
        std /= 2;
    }
}

int main() {
    input_fp = fopen("p10469.inp", "rt");
    output_fp = fopen("p10469.out", "wt");
    long long a, b;
    while (fscanf(input_fp, "%lld %lld", &a, &b) != EOF) {
        int aBit[32] = { 0 };
        int bBit[32] = { 0 };
        getBits(aBit, a);
        getBits(bBit, b);

        fprintf(output_fp, "%lld\n", calc(aBit, bBit));
    }
    fclose(input_fp);
    fclose(output_fp);
    return 0;
}
