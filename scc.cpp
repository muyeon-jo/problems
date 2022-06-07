#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <stack>
using namespace std;
FILE* input_fp, * output_fp;
vector<int> node[10001];
vector<int> node_transpose[10001];
int visit[10001];
int visit_t[10001];
int finishTime[10001];
int time = 0;
stack<int> order;
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
int dfs(int nodeNum) {
    if (visit_t[nodeNum] > 0) {
        return 0;
    }
    visit_t[nodeNum]++;
    int size = node_transpose[nodeNum].size();
    for (int i = 0; i < size; i++) {
        dfs(node_transpose[nodeNum][i]);
    }
    return 1;
}
int main() {
    
    input_fp = fopen("scc.inp", "r");
    output_fp = fopen("scc.out", "w");
    int n, m;
    fscanf(input_fp, "%d %d", &m, &n);

    int v, d;
    for (int i = 0; i < n; i++) {
        fscanf(input_fp, "%d %d", &v, &d);
        node[v].push_back(d);
        node_transpose[d].push_back(v);
    }
    for (int i = 0; i < m; i++) {
        if(visit[i] == 0)
            calcFinishTime(i);
    }
    int count = 0;
    while (order.size() > 0) {
        int num = order.top();
        order.pop();
        int a = dfs(num);
        count += a;
    }
   
    fprintf(output_fp, "%d", count);

    fclose(input_fp);
    fclose(output_fp);
    return 0;
}
