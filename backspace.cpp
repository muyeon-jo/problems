#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE* input_fp = fopen("backspace.inp", "rt");
FILE* output_fp = fopen("backspace.out", "wt");
char s[100001];
char t[100001];
int main() {
    int T;
    fscanf(input_fp, "%d", &T);
    while (T) {
        int n;
        fscanf(input_fp, "%d", &n);
        
        fscanf(input_fp, "%s", &s);
        fscanf(input_fp, "%s", &t);
        int s_len = strlen(s);
        int t_len = strlen(t);
        int j, i;
        for (i = t_len; i >= 0;) {

            for (j = s_len; j >= 0;) {
                if (s[j] == t[i]) {
                    i--;
                    j--;
                }
                else {
                    j = j - 2;
                }
            }
            if (j < 0)
                break;
        }

        if (i < 0)
            fprintf(output_fp, "YES\n");
        else
            fprintf(output_fp, "NO\n");
        T--;
    }
    fclose(input_fp);
    fclose(output_fp);
    return 0;
}