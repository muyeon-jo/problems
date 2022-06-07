#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <stack>
using namespace std;

FILE* input_fp, * output_fp;

typedef struct node {
    int number;
    int left, right;
}node_t;

node_t arr[1010];

int n;
char str[2010];
int list[1010];
int idx[1010];

int strLen;
int strIdx = 0;
int nextNode = 0;
void makeTree(int nowNode) {
    int closed = 0;
    while (strIdx < strLen) {
        if (closed == 0) {
            if (str[strIdx] == '(') {
                arr[nowNode].left = nextNode;
                strIdx++;
                nextNode++;
                makeTree(nextNode-1);
            }
            else {
                strIdx++;
            }
            closed++;
        }
        else {
            if (str[strIdx] == '(') {
                arr[nowNode].right = nextNode;
                strIdx++;
                nextNode++;
                makeTree(nextNode-1);
            }
            else {
                strIdx++;
            }
            return;
        }
    }

}
void makeBracket(int start, int end, int range[]) {
    int targetIdx = idx[nextNode];
    int leftNum = targetIdx - range[0];
    int rightNum = range[1] - targetIdx;
    str[start] = '(';
    str[start + 1 + leftNum * 2] = ')';

    if (leftNum > 0) {
        int leftRange[2] = { range[0],targetIdx - 1 };
        nextNode++;
        makeBracket(start + 1, start + leftNum * 2, leftRange);
    }
    if(rightNum>0) {
        int rightRange[2] = { targetIdx + 1,range[1] };
        nextNode++;
        makeBracket(start + leftNum * 2 + 2, end, rightRange);
    }
}
void dfs(int nowNode) {

    if (arr[nowNode].left != 0) {
        dfs(arr[nowNode].left);
    }
    fprintf(output_fp, "%d ", nowNode + 1);
    if (arr[nowNode].right != 0) {
        dfs(arr[nowNode].right);
    }
}
void clear() {
    for (int i = 0; i < nextNode; i++) {
        arr[i].left = 0;
        arr[i].right = 0;
    }
    memset(str, '\0', n * 2);
}
int main(){
    input_fp = fopen("transform.inp", "r");
    output_fp = fopen("transform.out", "w");

    int T;
    fscanf(input_fp, "%d", &T);
    while (T--) {
        int k;
        fscanf(input_fp, "%d %d", &n, &k);
        if (k == 1) {
            
            fscanf(input_fp, "%s", str);

            strLen = n * 2;
            strIdx = 1;
            nextNode = 1;
            makeTree(0);
            fprintf(output_fp, "%d ", n);
            dfs(0);
            fprintf(output_fp, "\n");
            
        }
        else {
            for (int i = 0; i < n; i++) {
                fscanf(input_fp, "%d", &list[i]);
                idx[list[i]] = i;
            }

            nextNode = 1;
            int range[2] = { 0,n - 1 };
            makeBracket(0, n * 2 - 1, range);
            fprintf(output_fp, "%d %s\n", n, str);
        }
        clear();
    }
    fclose(input_fp);
    fclose(output_fp);
    return 0;
}
