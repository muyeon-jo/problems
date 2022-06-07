#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <stack>
#define MAX 10010
using namespace std;

FILE* input_fp, * output_fp;

int K, N;
vector<int> node[MAX];
vector<int> node_transpose[MAX];
int visit[MAX];
int visit_t[MAX];
int finishTime[MAX];
int scc[MAX];
int time = 0;
stack<int> order;
void dfs(int nodeNum, int sccNum) {
    if (visit_t[nodeNum] > 0) {
        return;
    }
    visit_t[nodeNum]++;
    int size = node_transpose[nodeNum].size();
    for (int i = 0; i < size; i++) {
        dfs(node_transpose[nodeNum][i], sccNum);
    }
    scc[nodeNum] = sccNum;
}
void calcFinishTime(int nodeNum) {
    if (visit[nodeNum] > 0) {
        return;
    }
    time++;
    visit[nodeNum]++;
    int size = node[nodeNum].size();
    for (int i = 0; i < size; i++) {
        calcFinishTime(node[nodeNum][i]);
    }
    time++;
    finishTime[nodeNum] = time;
    order.push(nodeNum);
}
int reverseIndex(int a) {
    if (a > K)
        return a - K;
    return a + K;
}
void connectGraph(int a, int b) {
    node[reverseIndex(a)].push_back(b);
    node[reverseIndex(b)].push_back(a);
    node_transpose[a].push_back(reverseIndex(b));
    node_transpose[b].push_back(reverseIndex(a));
}
void clear() {
    for (int i = 0; i < MAX; i++) {
        int size = node[i].size();
        for (int j = 0; j < size; j++)
            node[i].pop_back();

        size = node_transpose[i].size();
        for (int j = 0; j < size; j++)
            node_transpose[i].pop_back();
    }
    while (order.size() > 0)
        order.pop();
    memset(visit, 0, MAX * sizeof(int));
    memset(visit_t, 0, MAX * sizeof(int));
    memset(finishTime, 0, MAX * sizeof(int));
    memset(scc, 0, MAX * sizeof(int));
}
int main(){
    input_fp = fopen("show.inp", "r");
    output_fp = fopen("show.out", "w");

    int T;
    fscanf(input_fp, "%d", &T);
    while (T--) {
        
        fscanf(input_fp, "%d %d", &K, &N);
        for (int i = 0; i < N; i++) {
            char A, B, C;
            int num1, num2, num3;
            fscanf(input_fp, "%d %c %d %c %d %c", &num1, &A, &num2, &B, &num3, &C);
            //B true, R false
            if (A == 'R')
                num1 = num1 + K;
            if (B == 'R')
                num2 = num2 + K;
            if (C == 'R')
                num3 = num3 + K;
            connectGraph(num1, num2);
            connectGraph(num1, num3);
            connectGraph(num2, num3);
        }
        for (int i = 1; i <= K * 2; i++) {
            if (visit[i] == 0)
                calcFinishTime(i);
        }
        int count = 1;

        while (order.size() > 0) {
            int num = order.top();
            order.pop();
            dfs(num, count++);
        }
        int checker = 1;
        for (int i = 1; i <= K; i++) {
            if (scc[i] == scc[i + K]) {
                checker = -1;
                break;
            }
        }

        fprintf(output_fp, "%d\n", checker);
        clear();
    }


    fclose(input_fp);
    fclose(output_fp);
    return 0;
}
