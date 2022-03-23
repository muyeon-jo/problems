#include <stdio.h>
#include <stdlib.h>
#include <string.h>
FILE* input_fp = fopen("watertank.inp", "rt");
FILE* output_fp = fopen("watertank.out", "wt");

int hole[4][1001][1001] = { 0 };
int tank[1000][1000] = { 0 };
int movex[4] = { 0,0,-1,1 };
int movey[4] = { -1,1,0,0 };
int N, M, H;
typedef struct node {
    int x, y, h, dir;
    struct node* next;
}node_t;
struct node* nodeAllocate(int x, int y, int h, int dir) {
    node_t* new_node = (node_t*)malloc(sizeof(node_t));
    new_node->x = x;
    new_node->y = y;
    new_node->h = h;
    new_node->dir = dir;
    new_node->next = NULL;
    return new_node;
}
node_t* head = NULL, * tail = NULL;
node_t* top = NULL;
int max(int a, int b) {
    if (a - b > 0)
        return a;

    return b;
}int min(int a, int b) {
    if (a - b > 0)
        return b;

    return a;
}
void push(node_t* temp) {
    temp->next = top;
    top = temp;
}
node_t* pop() {
    if (top == NULL)
        return NULL;
    node_t* temp = top;
    top = top->next;
    temp->next = NULL;
    return temp;
}
node_t* deQ() {
    if (head == NULL)
        return NULL;
    node_t* temp = head;
    head = head->next;
    temp->next = NULL;
    return temp;
}
void initialize(int N, int M, int H) {
    //위아래 초기화
    int temp;
    for (int i = 0; i < N + 1; i++) {
        for (int j = 0; j < M; j++) {
            fscanf(input_fp, "%d", &temp);
            hole[0][i][j] = temp;
            if (i - 1 >= 0)
                hole[1][i-1][j] = temp;
        }
    }


    //옆 초기화
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M + 1; j++) {
            fscanf(input_fp, "%d", &temp);
            hole[2][i][j] = temp;
            if (j - 1 >= 0)
                hole[3][i][j-1] = temp;
        }
    }

    //tank초기화
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            tank[i][j] = H;
        }
    }

}
void searchTank(int x, int y, int height, int dir) {//0:up, 1:down, 2:left, 3:right
    //터진다
    if (x >= M || y >= N || x < 0 || y < 0) {
        return;
    }
    if (tank[y][x] < height) {
        return;
    }
    tank[y][x] = height;
    int index[4] = { hole[0][y][x],hole[1][y + 1][x],hole[2][y][x],hole[3][y][x + 1] };
    for (int i = 0; i < 4; i++) {
        if (dir != i && index[i] != -1) {//index에 들어있는값이랑 height비교해서 넣도록

            if (i == 0) {
                searchTank(x, y - 1, max(index[i], height), 1);
            }
            else if (i == 1) {
                searchTank(x, y + 1, max(index[i], height), 0);
            }
            else if (i == 2) {
                searchTank(x - 1, y, max(index[i], height), 3);
            }
            else {
                searchTank(x + 1, y, max(index[i], height), 2);
            }
        }
    }
    
}
void sum(int x, int y) {
    long long sum = 0;
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            sum += tank[i][j];
        }
    }
    fprintf(output_fp, "%lld\n", sum);
}
void sortQueue(node_t* new_node) {
    if (head == NULL) {
        head = new_node;
        tail = new_node;
        return;
    }
    node_t* now = head;
    node_t* pre = NULL;
    while (now != NULL) {
        if (now->h > new_node->h) {
            if (pre == NULL) {//head 바뀜
                new_node->next = now;
                head = new_node;
                return;
            }
            else {
                pre->next = new_node;
                new_node->next = now;
                return;
            }
        }
        pre = now;
        now = now->next;
        
    }

    tail->next = new_node;
    tail = new_node;
}
void findHole() {
    node_t* temp;
    for (int i = 0; i < M; i++) {//up확인
        
        if (hole[0][0][i] != -1) {
            temp = nodeAllocate(i, 0, hole[0][0][i], 0);
            sortQueue(temp);
        }
        if (hole[1][N-1][i] != -1) {
            temp = nodeAllocate(i, N - 1, hole[1][N-1][i], 1);
            sortQueue(temp);
        }

    }

    for (int i = 0; i < N; i++) {
        if (hole[2][i][0] != -1) {
            temp = nodeAllocate(0, i, hole[2][i][0], 2);
            sortQueue(temp);
        }
        if (hole[3][i][M-1] != -1) {
            temp = nodeAllocate(M - 1, i, hole[3][i][M-1], 3);
            sortQueue(temp);
        }
    }
}
int main() {
    int T;
    fscanf(input_fp, "%d", &T);
    while (T) {

        fscanf(input_fp, "%d %d %d", &N, &M, &H);
        initialize(N, M, H);
        findHole();
        node_t* temp, *now;
        temp = deQ();
        push(temp);
        int nextX, nextY, nextH;
        while (top != NULL) {
            now = pop();
            if (tank[now->y][now->x] >= now->h) {
                tank[now->y][now->x] = now->h;
                for (int i = 0; i < 4; i++) {

                    if (hole[i][now->y][now->x] != -1) {
                        nextX = now->x + movex[i];
                        nextY = now->y + movey[i];
                        
                        if (nextX >= 0 && nextY >= 0 && nextY < N && nextX < M) {
                            nextH = max(min(hole[i][now->y][now->x], tank[nextY][nextX]), tank[now->y][now->x]);
                            if (tank[nextY][nextX] > nextH) {
                                tank[nextY][nextX] = nextH;
                                push(nodeAllocate(nextX, nextY, nextH, -1));
                            }
                        }
                    }
                   
                }

            }
            if (top == NULL && head!=NULL) {
                temp = deQ();
                push(temp);
            }
        }
        head = NULL;
        tail = NULL;

        sum(M, N);
        T--;
    }

    fclose(input_fp);
    fclose(output_fp);
    return 0;
}