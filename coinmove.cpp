#include <stdio.h>
#include <stdlib.h>
#include <string.h>
FILE* input_fp = fopen("coinmove.inp", "rt");
FILE* output_fp = fopen("coinmove.out", "wt");
int way[8][1000000] = { 0 };
void findWay(int p, int k, int s) {
    for (int i = 1; i < s; i++) {//i�� �����Ѵ�
        if (i % p == 0) {//����� ������ ��
            for (int j = 1; j < k + 1; j++) {
                way[j][i] = -1;
            }
            continue;
        }
        for (int j = 1; j < k + 1; j++) {//j��ŭ �̵�������
            int temp = 0;//1ã���� ���
            for (int z = 1; z < k + 1; z++) {//��
                if (j == z || i - z < 0) {//���� ���ڸ�ŭ �������� �������δ�
                    //0���� ������ ����
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
            way[i][0] = 1;//0�� �����ϸ� �¸� ���� �¸�

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