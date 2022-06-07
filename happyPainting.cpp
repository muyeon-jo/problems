#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
FILE* input_fp, * output_fp;
int nodesParent[50001];
int edgeColor[50001];
int pathCheker[50001];
int colorChecker[31];
void clearPathChecker(int n) {
    for (int i = 0; i <= n; i++) {
        pathCheker[i] = 0;
    }
}
int getColorNum() {
    int sum = 0;
    for (int i = 1; i < 31; i++) {
        sum += colorChecker[i];
        colorChecker[i] = 0;
    }
    return sum;
}
int findPath(int x, int y) {
    int nowNode = x;
    while (1) {
        pathCheker[nowNode]++;
        if (nodesParent[nowNode] == 0) {//루트노드 만나면 다음으로
            break;
        }
        
        nowNode = nodesParent[nowNode];
    }
    nowNode = y;
    while (1) {
        pathCheker[nowNode]++;
        if (pathCheker[nowNode] > 1) {
            return nowNode;
        }
        if (nodesParent[nowNode] == 0) {
            return 0;
        }
        
        nowNode = nodesParent[nowNode];
    }
}
void command1(int x, int y, int c) {
    int nowNode = y;
    while (1) {
        if (nowNode == x) {//x가 조상이면 무시
            return;
        }
        if (nodesParent[nowNode] == 0) {//루트까지 찾았으면 통과
            break;
        }
        nowNode = nodesParent[nowNode];
    }

    nodesParent[x] = y;
    edgeColor[x] = c;
    return;
}
void command2(int x, int y, int c) {
    
    int targetNode = findPath(x, y);
    
    if (targetNode == 0) {
        return;
    }

    int nowNode = x;
    while (1) {
        if (nowNode == targetNode) {
            break;
        }
        edgeColor[nowNode] = c;
        nowNode = nodesParent[nowNode];
    }
    nowNode = y;
    while (1) {
        if (nowNode == targetNode) {
            break;
        }
        edgeColor[nowNode] = c;
        nowNode = nodesParent[nowNode];
    }
}
void command3(int x, int y) {
    int targetNode = findPath(x, y);

    if (targetNode == 0) {
        fprintf(output_fp, "0 0\n");
        return;
    }
    int edgeNum = 0;
    int colorNum = 0;

    int nowNode = x;
    while (1) {
        if (nowNode == targetNode) {
            break;
        }
        edgeNum++;
        colorChecker[edgeColor[nowNode]]=1;
        nowNode = nodesParent[nowNode];
    }
    nowNode = y;
    while (1) {
        if (nowNode == targetNode) {
            break;
        }
        edgeNum++;
        colorChecker[edgeColor[nowNode]]=1;
        nowNode = nodesParent[nowNode];
    }
    colorNum = getColorNum();
    fprintf(output_fp, "%d %d\n", edgeNum, colorNum);
}
int main() {
    input_fp = fopen("p11994.inp", "rt");
    output_fp = fopen("p11994.out", "wt");
    
    int n, m;
    fscanf(input_fp, "%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        fscanf(input_fp, "%d", &nodesParent[i]);
    }
    for (int i = 1; i <= n; i++) {
        fscanf(input_fp, "%d", &edgeColor[i]);
    }
    int command, x, y, c;
    for (int i = 0; i < m; i++) {
        
        fscanf(input_fp, "%d", &command);

        if (command == 3) {
            fscanf(input_fp, "%d %d", &x, &y);
            command3(x, y);
            clearPathChecker(n);
        }
        else {
            fscanf(input_fp, "%d %d %d", &x, &y, &c);
            if (command == 1) {
                command1(x, y, c);
            }
            else {
                command2(x, y, c);
                clearPathChecker(n);
            }
        }
    }

    fclose(input_fp);
    fclose(output_fp);
    return 0;
}