#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char NUM_TEMPLATE[13] = { '2','3','4','5','6','7','8','9','T','J','Q','K','A' };
char SHAPE_TEMPLATE[4] = { 'C','D','S','H' };
char USER_TEMPLATE[4] = { 'S','W','N','E' };
int find(char temp, int mode) {
    if (mode == 0) {//num
        for (int i = 0; i < 13; i++) {
            if (NUM_TEMPLATE[i] == temp) {
                return i;
            }
        }
    }

    else if (mode == 1) {//shape
        for (int i = 0; i < 4; i++) {
            if (SHAPE_TEMPLATE[i] == temp) {
                return i;
            }
        }
    }
    else if (mode == 2) {//user
        for (int i = 0; i < 4; i++) {
            if (USER_TEMPLATE[i] == temp) {
                return i;
            }
        }
    }
}
int compare(const void* a, const void* b) {
    return *(int*)a - *(int*)b;
}
int main() {
    int N, T;
    FILE* fp_in, * fp_out;
    fp_in = fopen("bridge.inp", "r");
    fp_out = fopen("bridge.out", "w");

    int card[4][13] = { 0 };
    char dealer;
    fscanf(fp_in, "%c ", &dealer);
    while (dealer != '#') {
        int dealer_index = find(dealer, 2);
        char temp;
        char shape, num;
        int rotation = 0;
        int index = dealer_index + 1;
        for (int i = 0; i < 52; i++, index++) {
            fscanf(fp_in, "%c%c", &shape, &num);
            rotation = i / 4;
            index = index % 4;
            card[index][rotation] = (find(shape, 1) * 100) + find(num, 0);
            if (i % 26 == 25) {
                fscanf(fp_in, "%c", &temp);
            }
        }
        qsort(card[0], 13, sizeof(int), compare);
        qsort(card[1], 13, sizeof(int), compare);
        qsort(card[2], 13, sizeof(int), compare);
        qsort(card[3], 13, sizeof(int), compare);
        for (int j = 0; j < 4; j++) {
            fprintf(fp_out, "%c: ", USER_TEMPLATE[j]);
            for (int i = 0; i < 13; i++) {

                fprintf(fp_out, "%c%c ", SHAPE_TEMPLATE[(card[j][i] / 100)], NUM_TEMPLATE[card[j][i] % 100]);
            }
            fprintf(fp_out, "\n");
        }
        fscanf(fp_in, "%c ", &dealer);
    }

    fclose(fp_in);
    fclose(fp_out);
    return 0;
}