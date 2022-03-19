
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

FILE* input_fp;
FILE* output_fp;

int unit;
int test(int start, int end, int criterion, int target, int depth, int repeat) {
    if (criterion > target) {
        return 0;
    }
    int number = (start + end) / 2;
    if (criterion == target) {
        return number;
    }
    int cri = criterion + (int)pow((double)2, (double)repeat);
    int temp = test(start, number, cri, target, depth,repeat+1);
    if (temp > 0)
        return temp;
    cri = cri + (int)pow((double)2, (double)repeat);
    temp = test(number+1, end, cri, target, depth, repeat+1);
    if (temp > 0)
        return temp;

    return 0;
}
int getCase(int c, int d) {
    //int sum = unit;
    int sum = 0;
    if (c % 2 == 0) {
        c -= 1;
        sum += unit / 2;
    }
    if (c == 1) {
        return sum+ unit;
    }
    
    int tt = test(unit, (unit * 2) - (unit/2), 3, c, d, 1);
    printf("%d\n", tt);
    sum += tt;

    return sum;
}
int calc(int L, int D) {
    if (L > unit / 2) {
        int tt = getCase(L - unit / 2, D) + 1;
        //printf("%d\n", tt);
        return tt;
    }
    else {
        int tt = getCase(L, D);
        //printf("%d\n", tt);
        return tt;
    }
}

int main() {
    input_fp = fopen("p679.inp", "rt");
    output_fp = fopen("p679.out", "wt");
    
    int T;
    fscanf(input_fp, "%d", &T);
    while (T--) {
        int d, l;
        fscanf(input_fp, "%d %d", &d, &l);
        unit = (int)pow((double)2, (double)d - 1);
        fprintf(output_fp, "%d\n", calc(l, d - 1));
    }

    fclose(input_fp);
    fclose(output_fp);
    return 0;
}
