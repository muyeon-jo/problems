#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stack>

using namespace std;
FILE* input_fp, * output_fp;
typedef struct node {
    int x, y;
}node_p;

node_p list[20001];
int ccw(node_p p, node_p q, node_p r) {
    node_p vp = { p.x - r.x, p.y - r.y };
    node_p vq = { q.x - r.x, q.y - r.y };

    return vp.x * vq.y - vq.x * vp.y;
}
int compare(const void* a, const void* b) {
    if((*(node_p*)a).x - (*(node_p*)b).x ==0)
        return (*(node_p*)a).y - (*(node_p*)b).y;
    return (*(node_p*)a).x - (*(node_p*)b).x;
}
void solve(int n) {
    stack<node_p> s;
    s.push(list[0]);
    s.push(list[1]);

    int nextIdx = 2;

    while (nextIdx < n) {
        while (s.size() > 1) {
            node_p first, second;
            second = s.top();
            s.pop();
            first = s.top();
            if (ccw(second, list[nextIdx], first) > 0) {
                s.push(second);
                break;
            }
        }

        s.push(list[nextIdx]);
        nextIdx++;
    }

    //시계방향으로 한번 더

    stack<node_p> s2;
    s2.push(list[0]);
    s2.push(list[1]);

    nextIdx = 2;

    while (nextIdx < n) {
        while (s2.size() > 1) {
            node_p first, second;
            second = s2.top();
            s2.pop();
            first = s2.top();
            if (ccw(list[nextIdx], second, first) > 0) {
                s2.push(second);
                break;
            }
        }

        s2.push(list[nextIdx]);
        nextIdx++;
    }
    if (s2.top().x == s.top().x && s2.top().y == s.top().y) {//마지막 점이 같은 점이면 
        s2.pop();
    }
    node_p pr[20001];
    int idx = 0;
    for (int i = s.size(); i > 0; i = s.size()) {
        pr[idx++] = s.top();
        s.pop();
    }
    fprintf(output_fp, "%d\n", idx + s2.size() - 1);
    for (int i = idx - 1; i >= 0; i--) {
        fprintf(output_fp, "%d %d\n", pr[i].x, pr[i].y);
    }
    for (int i = s2.size(); i > 1; i = s2.size()) {
        fprintf(output_fp, "%d %d\n", s2.top().x, s2.top().y);
        s2.pop();
    }
}
int main() {
    input_fp = fopen("hull.inp", "rt");
    output_fp = fopen("hull.out", "wt");
    int n;
    fscanf(input_fp, "%d", &n);

    for (int i = 0; i < n; i++) {
        fscanf(input_fp, "%d %d", &list[i].x, &list[i].y);
    }
    qsort(list, n, sizeof(node_p), compare);

    solve(n);

    fclose(input_fp);
    fclose(output_fp);
    return 0;
}