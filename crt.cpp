#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <stack>
using namespace std;

FILE* input_fp, * output_fp;

long long gcd(long long a, long long b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}
long long euclid(long long x, long long y){
    long long r1 = x, r2 = y, r;
    long long s1 = 1, s2 = 0, s;
    long long t1 = 0, t2 = 1, t;
    long long q;
    while (r2 > 0) {
        q = r1 / r2;

        r = r1 - q * r2;
        r1 = r2;
        r2 = r;

        s = s1 - q * s2;
        s1 = s2;
        s2 = s;

        t = t1 - q * t2;
        t1 = t2;
        t2 = t;
    }
    return s1;//a의 곱역원
}
int main(){
    input_fp = fopen("crt.inp", "r");
    output_fp = fopen("crt.out", "w");

    int T;
    fscanf(input_fp, "%d", &T);
    while (T--) {
        long long r[60] = { 0 };
        long long m[60] = { 0 };
        long long coeff = 1;
        long long cons = 0;
        int k;
        fscanf(input_fp, "%d", &k);
        for (int i = 0; i < k; i++) {
            fscanf(input_fp, "%lld %lld", &r[i], &m[i]);
        }
        long long s = 1;
        long long a=0, b=0, n=0;
        int checker = 0;
        for (int i = 0; i < k; i++) {
            a = s, b = r[i], n = m[i];

            if (b % gcd(a, n) != 0) {//정답없음
                checker = 1;
                break;
            }

            //공약수 나누어줌
            long long t = gcd(gcd(a, b), n);
            a /= t;
            b /= t;
            n /= t;

            //나머지
            a = a % n;
            b = b % n;

            long long revA = euclid(a, n);
            b *= revA;

            b %= n;
            if (b < 0) {
                b += n;
            }

            cons += coeff * b;
            coeff = coeff * n;

            s = coeff;
            r[i+1] = r[i + 1] - cons;
            if (i != k - 1) {
                r[i + 1] %= m[i + 1];
                if (r[i + 1] < 0) {
                    r[i + 1] += m[i + 1];
                }
            }
        }
        if (checker == 1) {
            fprintf(output_fp, "-1\n");
        }
        else {
            fprintf(output_fp, "%lld\n", cons);
        }
        

    }
    fclose(input_fp);
    fclose(output_fp);
    return 0;
}
