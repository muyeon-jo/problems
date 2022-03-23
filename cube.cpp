#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int DICE[24][6] = {
    {1,2,3,4,5,6},
    {1,4,2,5,3,6},
    {1,5,4,3,2,6},
    {1,3,5,2,4,6},

    {2,6,3,4,1,5},
    {2,4,6,1,3,5},
    {2,3,1,6,4,5},
    {2,1,4,3,6,5},

    {3,2,6,1,5,4},
    {3,1,2,5,6,4},
    {3,5,1,6,2,4},
    {3,6,5,2,1,4},

    {4,2,1,6,5,3},
    {4,1,5,2,6,3},
    {4,5,6,1,2,3},
    {4,6,2,5,1,3},

    {5,4,1,6,3,2},
    {5,1,3,4,6,2},
    {5,3,6,1,4,2},
    {5,6,4,3,1,2},

    {6,2,4,3,5,1},
    {6,4,5,2,3,1},
    {6,5,3,4,2,1},
    {6,3,2,5,4,1}
};

int main() {
    FILE* fp_in, * fp_out;
    fp_in = fopen("cube.inp", "r");
    fp_out = fopen("cube.out", "w");
    char arr[6] = {};
    char temp[6] = {};
    char a;
    char test[10] = {};
    int b = 1;
    while (1) {
        for (int i = 0; i < 6; i++) {
            fscanf(fp_in, "%c", &arr[i]);
        }
        for (int i = 0; i < 6; i++) {
            fscanf(fp_in, "%c", &temp[i]);
        }
        fscanf(fp_in, "%c", &a);
        int count = 0;
        for (int i = 0; i < 6; i++) {
            if (arr[0] == temp[i] && arr[0] == arr[i]) {
                count++;
            }
        }
        if (count == 6) {
            break;
        }

        int check = 0;
        for (int i = 0; i < 24; i++) {//주사위의 경우의 수 

            check = 0;
            for (int j = 0; j < 6; j++) {//기준되는 주사위
                
                for (int k = 0; k < 6; k++) {//비교되는 주사위
                    if (DICE[0][j] == DICE[i][k]) {
                        if (arr[j] == temp[k]) {
                            check++;
                        }
                    }
                }
                if (check <= j) {
                    break;
                }
            }
            if (check == 6) {
                break;
            }
        }
        if (check == 6) {
            fprintf(fp_out, "TRUE\n");
        }
        else {
            fprintf(fp_out, "FALSE\n");
        }
        b++;
    }
    fprintf(fp_out, "TRUE\n");
    fclose(fp_in);
    fclose(fp_out);
    return 0;
}