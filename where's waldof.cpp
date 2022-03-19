
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
//0: �� ��, 1: ��, 2: ���� ��, 3:����, 4:�����Ʒ�, 5:�Ʒ�, 6:�� �Ʒ�, 7: ��
int nextWord(char word[], int x, int y, int wordIndex, int vectorX, int vectorY, int wordLen) {
    if (table[y + vectorY * wordIndex][x + vectorX * wordIndex] == word[wordIndex]) {//���ڰ� �´� ���
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
            if (table[i][j] == word[0]) {//ù���� ������ ã����
                int checker = 0;
                if (i >= wordLen - 1) {//������
                    checker = max(nextWord(word, j, i, 1, 0, -1, wordLen), checker);//��
                    if (j >= wordLen - 1)
                        checker = max(nextWord(word, j, i, 1, -1, -1, wordLen), checker);//����
                    if (maxX - j >= wordLen)
                        checker = max(nextWord(word, j, i, 1, 1, -1, wordLen), checker);//���� ��
                }
                if (maxY - i >= wordLen) {//�Ʒ�����
                    checker = max(nextWord(word, j, i, 1, 0, 1, wordLen), checker);//�Ʒ�
                    if (j >= wordLen - 1)
                        checker = max(nextWord(word, j, i, 1, -1, 1, wordLen), checker);//�޾Ʒ�
                    if (maxX - j >= wordLen)
                        checker = max(nextWord(word, j, i, 1, 1, 1, wordLen), checker);//���� �Ʒ�
                }
                if (j >= wordLen - 1) {
                    checker = max(nextWord(word, j, i, 1, -1, 0, wordLen), checker);//��
                }
                if (maxX - j >= wordLen)
                    checker = max(nextWord(word, j, i, 1, 1, 0, wordLen), checker);//����
                if (checker > 0) {
                    fprintf(output_fp, "%d %d\n", i + 1, j + 1);
                    return;
                }
            }//���� ���� ã�� if��
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
        }//table �ޱ� ��
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
        }//ã�� �ܾ� �ޱ� ��
        for (int i = 0; i < wordNum; i++) {
            parsing(words[i]);
        }

        fprintf(output_fp, "\n");
    }
    fclose(input_fp);
    fclose(output_fp);
    return 0;
}
