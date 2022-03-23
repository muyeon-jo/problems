#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE* input_fp;
FILE* output_fp;

int max(int x, int y) {
    if (x > y)
        return x;
    return y;
}int min(int x, int y) {
    if (x < y)
        return x;
    return y;
}
int sum[5002][5002];
int color[2][5002][26] = { 0 };

int calcLength(int i, int j, int c, int len[2]) {//���̴� ������ ������ ��ǥ - ������ ���� ��ǥ
    int ret1 = 0, ret2 = 0;
    if (color[0][i][c] + color[1][j][c] == color[0][len[0] - 1][c] + color[1][len[1] - 1][c]) //������ ��� ���Դ�
        ret1 = i + j;//������ ������ ��ǥ
    if ((color[0][i][c] == 1 && color[1][j][c] == 0)||(color[0][i][c] == 0 && color[1][j][c] == 1))//�� �� �ϳ� ������ ����
        ret2 = i + j;//������ ���� ��ǥ
    return ret1 - ret2;
}
void cpyColor(int i, int j, int m, int c) {
    if (m) {
        for (int k = 0; k < 26; k++) {
            color[0][j + 1][k] = color[0][j][k];
            color[1][j + 1][k] = color[1][j][k];
        }
    }
    else {
        for (int k = 0; k < 26; k++) {
            color[0][i + 1][k] = color[0][i][k];
            color[1][i + 1][k] = color[1][i][k];
        }
    }
}

int main() {
    input_fp = fopen("color.inp", "rt");
    output_fp = fopen("color.out", "wt");
    int T;
    fscanf(input_fp, "%d ", &T);

    while (T--) {
        
        char arr[2][5001] = {};
        
        fscanf(input_fp, "%s %s", &arr[0][1], &arr[1][1]);
        int arr_len[2] = { strlen(&arr[0][1]) + 1,strlen(&arr[1][1]) + 1 };

        for (int i = 0; i < arr_len[0]; i++) //�ʱ�ȭ
            for (int j = 0; j < arr_len[1]; j++)
                sum[i][j] = 210000000;
        
        for (int k = 0; k < 2; k++) {//�� ����
            for (int i = 1; i < arr_len[k]; i++) {//����
                for (int j = 0; j < 26; j++) {
                    color[k][i][j] = color[k][i - 1][j];//cpy
                }
                color[k][i][arr[k][i] - 'A']++;//i��°���� ������ �� ���� � �ִ°�
            }
        }
        sum[0][0] = 0;
        for (int i = 0; i < arr_len[0]; i++) {
            for (int j = 0; j < arr_len[1]; j++) {
                int len1, len2;
                len1 = calcLength(i + 1, j, arr[0][i + 1] - 'A', arr_len);//���翡�� 0�� ������ ���� �´ٸ�
                len2 = calcLength(i, j + 1, arr[1][j + 1] - 'A', arr_len);//���翡�� 1�� ������ ���� �´ٸ�
                sum[i + 1][j] = min(sum[i][j] + len1, sum[i + 1][j]);
                sum[i][j + 1] = min(sum[i][j] + len2, sum[i][j + 1]);
            }
        }


        fprintf(output_fp, "%d\n", sum[arr_len[0] - 1][arr_len[1] - 1]);

    }
    fclose(input_fp);
    fclose(output_fp);
    return 0;
}