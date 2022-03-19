#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX 1000000
FILE* input, * output;
int max(int a, int b) {
    if (a > b) {
        return a;
    }
    else {
        return b;
    }
}
int min(int a, int b) {
    if (a < b) {
        return a;
    }
    else {
        return b;
    }
}
unsigned long long calcLength(unsigned long long num) {
    static int memo[MAX+1];
    unsigned long long t = 0;
    if (num == 1) {
        return 1;
    }
    if (num % 2 == 0) {
        if (num > MAX) {
            t = calcLength(num / 2);
        }
        else if (memo[num / 2] > 0) {
            t = memo[num / 2];
        }
        else {
            t = calcLength(num / 2);
        }
    }
    else {
        if (num * 3+1 > MAX) {
            t = calcLength(num * 3 + 1);
        }
        else if (memo[num * 3 + 1] > 0) {
            t = memo[num * 3 + 1];
        }
        else {
            t = calcLength(num * 3 + 1);
        }
    }
    if (num <= MAX) {
        memo[num] = t + 1;
    }
    return t + 1;
    
}
int main() {
    input = fopen("cycle.inp", "r");
    output = fopen("cycle.out", "w");
    int buffer[10] = { 0 };
    while (!feof(input)) {
        int a, b;
        char c;
        if (fscanf(input, "%d %d", &a, &b) == -1) {
            break;
        }
        unsigned long long m = 0;
        int start, end;
        start = min(a, b);
        end = max(a, b);
        for (int i = start; i <= end; i++) {
            unsigned long long temp = calcLength(i);
            if (m < temp) {
                m = temp;
            }
        }
        fprintf(output, "%d %d %llu\n", a, b, m);
    }
    

    fclose(input);
    fclose(output);
    return 0;
}