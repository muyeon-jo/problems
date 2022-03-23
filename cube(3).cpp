#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 210000000

FILE* input_fp = fopen("cube.inp", "rt");
FILE* output_fp = fopen("cube.out", "wt");

int cube[201][201][201] = { 0 };

int min(int x, int y) {
    if (x > y)
        return y;

    return x;
}
int cutCube(int w, int l, int h) {
    if (w == l && w == h) {//이미 정육각형
        return 1;
    }
    if (w == 1 || l == 1 || h == 1) {//한 변이라도 1이면 1로 잘라야됨
        return w * l * h;
    }
    if (cube[w][l][h] != 0) {
        return cube[w][l][h];
    }
    int size[3] = {MAX,MAX,MAX};
    for (int i = 1; i < w / 2 + 1; i++) {//w가 나누어지도록 자름
        size[0] = min(size[0], cutCube(i, l, h) + cutCube(w - i, l, h));
    }
    for (int i = 1; i < l / 2 + 1; i++) {//l이 나누어지도록 자름
        size[1] = min(size[1], cutCube(w, i, h) + cutCube(w , l - i, h));
    }
    for (int i = 1; i < h / 2 + 1; i++) {//h가 나누어지도록 자름
        size[2] = min(size[2], cutCube(w, l, i) + cutCube(w, l, h - i));
    }
    int temp = min(min(size[0], size[1]), size[2]);

    cube[w][l][h] = temp;
    cube[w][h][l] = temp;
    cube[l][w][h] = temp;
    cube[l][h][w] = temp;
    cube[h][l][w] = temp;
    cube[h][w][l] = temp;

    return temp;
}
int main() {

    int T;
    
    fscanf(input_fp, "%d", &T);
    while (T) {
        int w,l,h;
        
        fscanf(input_fp, "%d %d %d", &w, &l, &h);

        fprintf(output_fp, "%d\n", cutCube(w, l, h));
        T--;
    }
    fclose(input_fp);
    fclose(output_fp);

    return 0;
}