#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE* input_fp, * output_fp;

void snail(int height, int movement, int slideDown, int fatigue) {
    int day = 0;
    int nowHeight = 0;
    int dayMovement = 0;
    int n = movement * fatigue / 100;
    int stack = 0;
    while (++day) {
        //아침
        if (stack * n < movement) {//아직 움직일 수 있는가
            nowHeight += movement - n * stack;
            stack++;
        }
        else {//피로 때문에 못움직이는가
           //stack = 0;
        }
        if (nowHeight > height) {//우물 넘었는가
            fprintf(output_fp, "success on day %d\n", day);
            break;
        }
        //밤
        nowHeight -= slideDown;
        if (nowHeight <= 0.0) {
            fprintf(output_fp, "failure on day %d\n", day);
            break;
        }
    }
}

int main() {
    input_fp = fopen("snail.inp", "rt");
    output_fp = fopen("snail.out", "wt");
    
    while (1) {
        int H, U, D, F;
        fscanf(input_fp, "%d %d %d %d", &H, &U, &D, &F);
        if (H == 0) {
            break;
        }
        snail(H*100, U*100, D*100, F);

    }

    fclose(input_fp);
    fclose(output_fp);
    return 0;
}
