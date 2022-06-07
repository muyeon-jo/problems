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
    input_fp = fopen("conEq.inp", "r");
    output_fp = fopen("conEq.out", "w");

    int T;
    fscanf(input_fp, "%d", &T);
    while (T--) {
        long long a, b, n;
        fscanf(input_fp, "%lld %lld %lld", &a, &b, &n);

        if (b % gcd(a, n) != 0) {//정답없음
            fprintf(output_fp, "-1\n");
            continue;
        }
        a = a % n;
        b = b % n;

        long long m = gcd(gcd(a, b), n);
        a /= m;
        b /= m;
        n /= m;

        long long revA = euclid(a, n);
        b *= revA;
        while (b < 0) {
            b += n;
        }
        b %= n;

        fprintf(output_fp, "%lld %lld\n", b, b + n);

    }


    fclose(input_fp);
    fclose(output_fp);
    return 0;
}
