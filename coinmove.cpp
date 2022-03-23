#include <stdio.h>
#include <stdlib.h>
#include <string.h>
FILE* input_fp = fopen("coinmove.inp", "rt");
FILE* output_fp = fopen("coinmove.out", "wt");
int way[8][1000000] = { 0 };
void findWay(int p, int k, int s) {
    for (int i = 1; i < s; i++) {//i에 도착한다
        if (i % p == 0) {//배수는 놓으면 짐
            for (int j = 1; j < k + 1; j++) {
                way[j][i] = -1;
            }
            continue;
        }
        for (int j = 1; j < k + 1; j++) {//j만큼 이동했을때
            int temp = 0;//1찾으면 토글
            for (int z = 1; z < k + 1; z++) {//비교
                if (j == z || i - z < 0) {//같은 숫자만큼 연속으로 못움직인다
                    //0보다 작으면 생략
                    continue;
                }
                if (way[z][i - z] == 1) {
                    temp = 1;
                    break;
                }
            }
            if (temp) {
                way[j][i] = -1;
            }
            else {
                way[j][i] = 1;
            }
        }
    }
}
int main() {
    int T;

    fscanf(input_fp, "%d", &T);
    while (T) {
        int p, k, s;
        fscanf(input_fp, "%d %d %d", &p, &k, &s);
        for (int i = 1; i < k + 1; i++) {
            way[i][0] = 1;//0에 도착하면 승리 영희가 승리

        }
        findWay(p, k, s);
        int temp = 0;
        int i;
        for (i = 1; i < k + 1; i++) {
            if (way[i][s - i] == 1) {
                temp = 1;
                break;
            }
        }
        if (temp) {
            fprintf(output_fp, "%d\n", s - i);
        }
        else {
            fprintf(output_fp, "-1\n");
        }
        T--;
    }
    fclose(input_fp);
    fclose(output_fp);
    return 0;
}