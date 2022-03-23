#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE* input_fp;
FILE* output_fp;

int main() {
    input_fp = fopen("yuri.inp", "rt");
    output_fp = fopen("yuri.out", "wt");
    int T;
    fscanf(input_fp, "%d ", &T);
    while (T--) {
        int word[2][26] = { 0 };
        char arr[2000] = { '\0' };
        fscanf(input_fp, "%s", arr);
        for (int i = 0; i < strlen(arr); i++) {
            if (arr[i] >= 'a') {
                word[0][arr[i] - 'a']++;
            }
            else {
                word[1][arr[i] - 'A']++;
            }
        }
        int a = -1;
        int max = 0;
        for (int i = 0; i < 26; i++) {
            if (word[1][i] != 0 && word[1][i] > max) {
                a = i;
                max = word[1][i];
            }
        }
        fprintf(output_fp, "%c %d ", a + 'A', max);
        a = -1;
        int min = 2100000;
        for (int i = 0; i < 26; i++) {
            if (word[1][i] != 0 && word[1][i] < min) {
                a = i;
                min = word[1][i];
            }
        }
        fprintf(output_fp, "%c %d ", a + 'A', min);
        a = -1;
        max = 0;
        for (int i = 0; i < 26; i++) {
            if (word[0][i] != 0 && word[0][i] > max) {
                a = i;
                max = word[0][i];
            }
        }
        fprintf(output_fp, "%c %d ", a + 'a', max);
        a = -1;
        min = 2100000;
        for (int i = 0; i < 26; i++) {
            if (word[0][i] != 0 && word[0][i] < min) {
                a = i;
                min = word[0][i];
            }
        }
        fprintf(output_fp, "%c %d\n", a + 'a', min);
    }
    fclose(input_fp);
    fclose(output_fp);
    return 0;
}