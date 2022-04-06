#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
FILE* input_fp;
FILE* output_fp;
int max(int x, int y) {
    return x > y ? x : y;
}
int isSlump(char line[], int startIdx, int endIdx) {
    int check = -1;
    //first character is either a 'D' or an 'E'
    if (line[startIdx] != 'D' && line[startIdx] != 'E') {
        return -1;
    }

    //first character followed by a string of one or more 'F's
    if (line[startIdx + 1] != 'F') {
        return -1;
    }
    for (int i = startIdx + 2; i < endIdx; i++) {
        if (line[i] != 'F') {
            return isSlump(line, i, endIdx);
        }
    }
    if(line[endIdx] != 'G'){
        return -1;
    }

    return 1;
}
int isSlimp(char line[], int startIdx, int endIdx) {
    int check = -1;
    //first character is 'A'
    if (line[startIdx] != 'A')
        return -1;
    //is two character slimp then second and last character is an 'H' 
    if (endIdx - startIdx + 1 == 2){
        if (line[startIdx + 1] != 'H') 
            return -1;
        else
            return 1;
    }
    else if (line[endIdx] != 'C') {
        return -1;
    }
    else{
        //'A' followed by 'B' followed by a slimp followed by a 'C'
        
        if (line[startIdx + 1] == 'B') {
            check = max(check, isSlimp(line, startIdx + 2, endIdx - 1));
        }
        //'A' followed by a slump followed by a 'C'
        
        check = max(check, isSlump(line, startIdx + 1, endIdx - 1));
        
    }

    return check;
}
int isSlurpy(char line[]) {
    int len = strlen(line);
    for (int i = 2; i < len - 2; i++) {//slump는 D 나 E로 시작하기 때문에 D나 E로 시작하는 단어를 기준으로 쪼개서 넣어본다
        if (line[i] == 'D' || line[i] == 'E') {
            if (isSlimp(line, 0, i - 1) == 1) {
                if (isSlump(line, i, len - 1) == 1) {
                    return 1;
                }
            }
            
        }
    }

    return -1;
}
int main() {
    input_fp = fopen("p384.inp", "rt");
    output_fp = fopen("p384.out", "wt");
    int T;
    fscanf(input_fp, "%d ", &T);
    fprintf(output_fp, "SLURPYS OUTPUT\n");
    while (T--) {
        char line[70] = { '\0' };
        fscanf(input_fp, "%s", line);
        //슬림프 뒤에 슬럼프 = 슬럴프
        if (isSlurpy(line) == 1) {
            fprintf(output_fp, "YES\n");
        }
        else {
            fprintf(output_fp, "NO\n");
        }

    }
    fprintf(output_fp, "END OF OUTPUT\n");
    fclose(input_fp);
    fclose(output_fp);
    return 0;
}
