#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct node {
    int a;
    struct node* next;
}edge_t;
FILE* input_fp;
FILE* output_fp;
int count[50001];
int check[50001];
int save[50001];
int stack[50001];
edge_t* ori[50001];
edge_t* edge_arr[50001];
edge_t* allocateEdge(int a) {
    edge_t* temp = (edge_t*)malloc(sizeof(edge_t));
    temp->a = a;
    temp->next = NULL;
    return temp;
}
int max(int x, int y) {
    if (x > y)
        return x;
    return y;
}
int DFS(int depth) {
    int max = 0;
    while (depth) {//depth 0되면 탐색끝
        while (edge_arr[stack[depth]] != NULL) {//스택되어있는 노드에서 갈 수 있는 모든 노드를 가봤으면 끝
            if (check[edge_arr[stack[depth]]->a] == 0) {
                check[edge_arr[stack[depth]]->a]++;
                stack[depth + 1] = edge_arr[stack[depth]]->a;

                edge_arr[stack[depth]] = edge_arr[stack[depth]]->next;
                depth++;
                if (depth > max) {
                    max = depth;
                }
            }
            else {
                edge_arr[stack[depth]] = edge_arr[stack[depth]]->next;
            }

        }

        depth--;
    }
    return max;
}
void duplicate(int n) {
    for (int i = 1; i <= n; i++) {//ori에 원본 저장
        edge_arr[i] = ori[i];
    }
}
void deAllocate(int n) {
    for (int i = 1; i <= n; i++) {
        while (ori[i] != NULL) {
            edge_t* temp = ori[i];
            ori[i] = ori[i]->next;
            free(temp);
        }
    }
}
void reset(int n) {
    for (int i = 1; i <= n; i++) {
        check[i] = 0;
    }
}
int main() {
    input_fp = fopen("cycle.inp", "rt");
    output_fp = fopen("cycle.out", "wt");
    int T;
    fscanf(input_fp, "%d", &T);
    while (T--) {
        int n;
        fscanf(input_fp, "%d", &n);
        int a, b;
        for (int i = 0; i < n-1; i++) {
            fscanf(input_fp, "%d %d", &a, &b);
            if (ori[a] == NULL) {
                ori[a] = allocateEdge(b);
            }
            else {
                edge_t* temp = allocateEdge(b);
                temp->next = ori[a];
                ori[a] = temp;
            }

            if (ori[b] == NULL)
                ori[b] = allocateEdge(a);
            else {
                edge_t* temp = allocateEdge(a);
                temp->next = ori[b];
                ori[b] = temp;
            }
            count[a]++;
            count[b]++;
        }
        int roof_num = 0;
        int top = 0;
        int sum = n;
        for (int i = 1; i <= n; i++) {//초기 설정
            if (count[i] == 1) {
                stack[top++] = i;
            }
        }
        while (top) {
            if (top <= 2) {
                break;
            }
            int index = 0;
            
            for (int i = 0; i < top; i++) {//한번 제거
                int other = ori[stack[i]]->a;
                free(ori[stack[i]]);
                ori[stack[i]] = NULL;
                count[stack[i]]--;
                //
                edge_t* pre = NULL;
                edge_t* temp = ori[other];
                while (temp->a != stack[i]) {//지워진 노드 찾기
                    pre = temp;
                    temp = temp->next;
                }
                if (pre != NULL) {
                    pre->next = temp->next;
                }
                else {
                    ori[other] = temp->next;
                }
                free(temp);
                count[other]--;
                if (count[other] == 1) {//other가 
                    stack[index++] = other;
                }
            }
            roof_num++;
            sum = sum - top;
            top = index;
        }
        fprintf(output_fp, "%d\n", sum + roof_num * 2);
        for (int i = 1; i <= n; i++) {
            count[i] = 0;
        }
        deAllocate(n);
    }
    fclose(input_fp);
    fclose(output_fp);
    return 0;
}