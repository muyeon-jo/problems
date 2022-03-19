
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE* input_fp;
FILE* output_fp;
int maxX, maxY;
char table[50][50];
char words[50][50];
int max(int x, int y) {
    return x > y ? x : y;
}
//0: 왼 위, 1: 위, 2: 오른 위, 3:오른, 4:오른아래, 5:아래, 6:왼 아래, 7: 왼
int nextWord(char word[], int x, int y, int wordIndex, int vectorX, int vectorY, int wordLen) {
    if (table[y + vectorY * wordIndex][x + vectorX * wordIndex] == word[wordIndex]) {//글자가 맞는 경우
        if (wordLen - 1 == wordIndex) {
            return 1;
        }
        else {
            return nextWord(word, x, y, wordIndex + 1, vectorX, vectorY, wordLen);
        }
    }
    return 0;
}
void parsing(char word[]) {
    int wordLen = strlen(word);
    for (int i = 0; i < maxY; i++) {
        for (int j = 0; j < maxX; j++) {
            if (table[i][j] == word[0]) {//첫글자 같은거 찾으면
                int checker = 0;
                if (i >= wordLen - 1) {//윗방향
                    checker = max(nextWord(word, j, i, 1, 0, -1, wordLen), checker);//위
                    if (j >= wordLen - 1)
                        checker = max(nextWord(word, j, i, 1, -1, -1, wordLen), checker);//왼위
                    if (maxX - j >= wordLen)
                        checker = max(nextWord(word, j, i, 1, 1, -1, wordLen), checker);//오른 위
                }
                if (maxY - i >= wordLen) {//아랫방향
                    checker = max(nextWord(word, j, i, 1, 0, 1, wordLen), checker);//아래
                    if (j >= wordLen - 1)
                        checker = max(nextWord(word, j, i, 1, -1, 1, wordLen), checker);//왼아래
                    if (maxX - j >= wordLen)
                        checker = max(nextWord(word, j, i, 1, 1, 1, wordLen), checker);//오른 아래
                }
                if (j >= wordLen - 1) {
                    checker = max(nextWord(word, j, i, 1, -1, 0, wordLen), checker);//왼
                }
                if (maxX - j >= wordLen)
                    checker = max(nextWord(word, j, i, 1, 1, 0, wordLen), checker);//오른
                if (checker > 0) {
                    fprintf(output_fp, "%d %d\n", i + 1, j + 1);
                    return;
                }
            }//같은 글자 찾는 if문
        }//for j
    }//for i


}
int main() {
    input_fp = fopen("p10010.inp", "rt");
    output_fp = fopen("p10010.out", "wt");
    
    int T;
    fscanf(input_fp, "%d", &T);
    while (T--) {
        char temp;
        fscanf(input_fp, "%d %d ", &maxY, &maxX);
        for (int i = 0; i < maxY; i++) {
            fscanf(input_fp, "%s", table[i]);
            for (int j = 0; j < maxX; j++) {
                if (table[i][j] < 'a') {
                    table[i][j] += 32;
                }
            }
            fscanf(input_fp, "%c", &temp);
        }//table 받기 끝
        int wordNum;
        fscanf(input_fp, "%d ", &wordNum);
        for (int i = 0; i < wordNum; i++) {
            fscanf(input_fp, "%s", words[i]);
            int len = strlen(words[i]);
            for (int j = 0; j < len; j++) {
                if (words[i][j] < 'a') {
                    words[i][j] += 32;
                }
            }
        }//찾을 단어 받기 끝
        for (int i = 0; i < wordNum; i++) {
            parsing(words[i]);
        }

        fprintf(output_fp, "\n");
    }
    fclose(input_fp);
    fclose(output_fp);
    return 0;
}
