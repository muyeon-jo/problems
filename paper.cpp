#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct node {
    int BL[2];
    int UR[2];
    char state;
    int overlapedBL[2];
    int overlapedUR[2];
    struct node* next[4];
}node_t;
struct node* nodeAllocate(int x1, int y1, int x2, int y2, int ox1, int oy1, int ox2, int oy2) {//��带 ���� ����
    node_t* new_node = (node_t*)malloc(sizeof(node_t));
    new_node->BL[0] = x1;
    new_node->BL[1] = y1;
    new_node->UR[0] = x2;
    new_node->UR[1] = y2;

    new_node->overlapedBL[0] = ox1;
    new_node->overlapedBL[1] = oy1;
    new_node->overlapedUR[0] = ox2;
    new_node->overlapedUR[1] = oy2;
    for(int i=0;i<4;i++)
        new_node->next[i] = NULL;

    if ((x1 >= ox1 && y1 >= oy1) && (x2 <= ox2 && y2 <= oy2)) {//��üũ�⸦ ���°��
        new_node->state = 'b';
    }
    else if ((x1 >= ox2 || y1 >= oy2) || (x2 <= ox1 || y2 <= oy1)) {//�Ȱ�ġ�°��
        new_node->state = 'w';
    }
    else
        new_node->state = 'x';

    return new_node;

}
void makeQuadTree(node_t* root, int x, int y, int x1, int y1, int x2, int y2) {//�����̿� ������ �κ��� ����ؼ� ������ ����� 4���ǳ�带 ����
    root->next[0] = nodeAllocate(x, y, root->UR[0], root->UR[1], x1, y1, x2, y2);
    root->next[1] = nodeAllocate(root->BL[0], y, x, root->UR[1], x1, y1, x2, y2);
    root->next[2] = nodeAllocate(root->BL[0], root->BL[1], x, y, x1, y1, x2, y2);
    root->next[3] = nodeAllocate(x, root->BL[1], root->UR[0], y, x1, y1, x2, y2);
}
int searchAnswer(int index,node_t* root, int x1[], int y1[], int x2[], int y2[], int n, int check) {//���ϰ����� ���� Ȯ���ϱ�
    int result = 0;//result 1: �κи� ������, 0: ������, 2: �����Ȱ�����
    int j = 0;
    for (j = index + 1; j < n; j++) {
        if (root->BL[0] < x2[j] && root->UR[0] > x1[j] && root->BL[1] < y2[j] && root->UR[1] > y1[j]) {//�κ��� ������ ���̰� �������
            
            if (root->BL[0] >= x1[j] && root->BL[1] >= y1[j] && root->UR[0] <= x2[j] && root->UR[1] <= y2[j]) {//�ſ�ū �ϳ��� ���´�
                check = 0;
                root->state = 'b';
            }
            else {
                check = 1;
                root->state = 'x';
                if (root->BL[0] < x1[j]) {//�������� ��ħ
                    if (root->BL[1] < y1[j]) {//������ ���� ��ħ
                        makeQuadTree(root, x1[j], y1[j], x1[j], y1[j], x2[j], y2[j]);
                    }
                    else if (root->UR[1] > y2[j]) {//������ �Ʒ��� ��ħ
                        makeQuadTree(root, x1[j], y2[j], x1[j], y1[j], x2[j], y2[j]);
                    }
                    else {//������ ��ü�� ��ħ
                        makeQuadTree(root, x1[j], (root->UR[1] + root->BL[1]) / 2, x1[j], y1[j], x2[j], y2[j]);
                    }
                }
                else if (root->BL[1] < y1[j]) {//���� ��ħ
                    if (root->UR[0] > x2[j]) {//���� ���� ��ħ
                        makeQuadTree(root, x2[j], y1[j], x1[j], y1[j], x2[j], y2[j]);
                    }
                    else {//�� ��ü�� ��ħ
                        makeQuadTree(root, (root->BL[0] + root->UR[0]) / 2, y1[j], x1[j], y1[j], x2[j], y2[j]);
                    }
                }
                else if (root->UR[0] > x2[j]) {//������ ��ħ
                    if (root->UR[1] > y2[j]) {//���� �Ʒ��� ��ħ
                        makeQuadTree(root, x2[j], y2[j], x1[j], y1[j], x2[j], y2[j]);
                    }
                    else {//���� ��ü�� ��ħ
                        makeQuadTree(root, x2[j], (root->BL[1] + root->UR[1]) / 2, x1[j], y1[j], x2[j], y2[j]);
                    }
                }
                else {//�Ʒ��� ��ħ
                    makeQuadTree(root, (root->BL[0] + root->UR[0]) / 2, y2[j], x1[j], y1[j], x2[j], y2[j]);
                }
                //Ʈ�� �������
                //���� �簢���� �������� �ٽ� Ž���ؾ���
                for (int i = 0; i < 4; i++) {
                    if (root->next[i] != NULL) {
                        
                        result = searchAnswer(index, root->next[i], x1, y1, x2, y2, n, check);

                        if (result == 1) {
                            for (int k = i + 1; k < 4; k++) {
                                free(root->next[k]);
                            }
                            return 1;
                        }
                    }
                    
                }
                
            }


            break;
        }

    }
    if (check != 2 && root->state == 'w') {
        return 1;
    }
    if (check == 2) {
        return 2;
    }
    return result;
}


int main() {
    FILE* fp_in, * fp_out;
    fp_in = fopen("paper.inp", "r");
    fp_out = fopen("paper.out", "w");
    int n;
    fscanf(fp_in, "%d", &n);
    int** arr = (int**)malloc(sizeof(int*)*4);
    for (int i = 0; i < 4; i++) {
        arr[i] = (int*)malloc(sizeof(int) * n);
    }
    for (int i = 0; i < n; i++) {
        fscanf(fp_in, "%d %d %d %d", &arr[0][i], &arr[1][i], &arr[2][i], &arr[3][i]);
        arr[2][i] += arr[0][i];
        arr[3][i] += arr[1][i];
    }
    int ans[3] = { 0 };
    int temp = -1;
    for (int i = 0; i < n; i++) {
        node_t* root = nodeAllocate(arr[0][i], arr[1][i], arr[2][i], arr[3][i], -1, -1, -1, -1);
        //
        temp = searchAnswer(i, root, arr[0], arr[1], arr[2], arr[3], n, 2);
        free(root);
        root = NULL;
        ans[temp]++;
        //Ʈ��Ž��
    }
    /*
    
    */
    fprintf(fp_out, "%d %d %d", ans[0], ans[1], ans[2]);
    fclose(fp_in);
    fclose(fp_out);
    return 0;
}