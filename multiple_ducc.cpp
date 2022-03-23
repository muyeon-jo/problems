#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE* input_fp;
FILE* output_fp;

int main() {
    input_fp = fopen("multiple.inp", "rt");
    output_fp = fopen("multiple.out", "wt");
    int T;
    fscanf(input_fp, "%d ", &T);
    while (T--) {
        int mini, maxi, c, d;
        int count = 0;
        fscanf(input_fp, "%d %d %d %d", &mini, &maxi, &c, &d);
        for (int i = 1; i < 1000000; i++) {
            int temp = c * i;
            if (temp < mini) {
                continue;
            }
            else if (temp > maxi) {
                break;
            }
            else {
                count++;
            }

        }


        for (int i = 1; i < 1000000; i++) {
            int temp = d * i;
            if (temp < mini) {
                continue;
            }
            else if (temp > maxi) {
                break;
            }
            else {
                if(temp%c != 0)
                    count++;
            }

        }
        fprintf(output_fp, "%d\n", count);
    }
    
    fclose(input_fp);
    fclose(output_fp);
    return 0;
}