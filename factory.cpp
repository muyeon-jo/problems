#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <stack>
#define MAX 4010
using namespace std;

FILE* input_fp, * output_fp;

int N, D;
int timeTable[MAX];
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
    if (a >= N*2)
        return a - N*2;
    return a + N*2;
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
    input_fp = fopen("factory.inp", "r");
    output_fp = fopen("factory.out", "w");

    int T;
    int caseNum = 1;
    fscanf(input_fp, "%d", &T);
    while (T--) {
        
        fscanf(input_fp, "%d %d", &N, &D);
        int num = 0;
        for (int i = 0; i < N; i++) {
            int num1, num2;
            fscanf(input_fp, "%d %d", &num1, &num2);

            node[reverseIndex(num)].push_back(num+1);
            node[reverseIndex(num+1)].push_back(num);
            node_transpose[num].push_back(reverseIndex(num+1));
            node_transpose[num+1].push_back(reverseIndex(num));
            timeTable[num] = num1;
            timeTable[num + 1] = num2;

            for (int i = num - 1; i >= 0; i--) {//다른 노드 탐색
                if ((timeTable[i] + D > num1 && timeTable[i] <= num1) || (num1 + D > timeTable[i] && num1 + D <= timeTable[i] + D)) {
                    node[num].push_back(reverseIndex(i));
                    node[i].push_back(reverseIndex(num));
                    node_transpose[reverseIndex(i)].push_back(num);
                    node_transpose[reverseIndex(num)].push_back(i);

                }

                if ((timeTable[i] + D > num2 && timeTable[i] <= num2) || (num2 + D > timeTable[i] && num2 + D <= timeTable[i] + D)) {
                    node[num+1].push_back(reverseIndex(i));
                    node[i].push_back(reverseIndex(num+1));
                    node_transpose[reverseIndex(i)].push_back(num+1);
                    node_transpose[reverseIndex(num+1)].push_back(i);
                }
            }

            num += 2;
        }
        for (int i = 0; i < N * 4; i++) {
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
        for (int i = 0; i < N * 2; i++) {
            if (scc[i] == scc[i + N*2]) {
                checker = -1;
                break;
            }
        }
        if(checker == 1)
            fprintf(output_fp, "Test Case #%d: Possible\n", caseNum);
        else
            fprintf(output_fp, "Test Case #%d: Impossible\n", caseNum);
        clear();
        caseNum++;
    }


    fclose(input_fp);
    fclose(output_fp);
    return 0;
}
