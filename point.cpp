#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE* input_fp, * output_fp;

typedef struct node {
    int x;
    int y;
}point;
point nPoints[5001];
point kPoints[1001];
int checker[1001];
int ccw(point p, point q, point r) {
    p.x = p.x - r.x;
    p.y = p.y - r.y;
    q.x = q.x - r.x;
    q.y = q.y - r.y;
    return p.x * q.y - p.y * q.x;
}
int isOnEdge(int kIdx, int n) {
    for (int i = 0; i < n; i++) {
        if (nPoints[i].x <= kPoints[kIdx].x && kPoints[kIdx].x <= nPoints[(i + 1) % 2].x || nPoints[i].x >= kPoints[kIdx].x && kPoints[kIdx].x >= nPoints[(i + 1) % 2].x) {
            if (nPoints[i].y <= kPoints[kIdx].y && kPoints[kIdx].y <= nPoints[(i + 1) % 2].y || nPoints[i].y >= kPoints[kIdx].y && kPoints[kIdx].y >= nPoints[(i + 1) % 2].y) {
                if (ccw(nPoints[(i + 1) % 2], kPoints[kIdx], nPoints[i]) == 0) {
                    return 1;
                }
            }
        }
        
    }
    return 0;
}
int checkPosition(int nIdx, int kIdx, int nnIdx) {

    if (nPoints[nIdx].y < nPoints[nnIdx].y) {//nidx < nnidx
        
        if (kPoints[kIdx].y <= nPoints[nnIdx].y && kPoints[kIdx].y > nPoints[nIdx].y) {

            return ccw(nPoints[nnIdx], kPoints[kIdx], nPoints[nIdx]);
        }
    }
    else if (nPoints[nIdx].y > nPoints[nnIdx].y) {//nnidx < nidx
        if (kPoints[kIdx].y <= nPoints[nIdx].y && kPoints[kIdx].y > nPoints[nnIdx].y) {

            return ccw(nPoints[nIdx], kPoints[kIdx], nPoints[nnIdx]);
        }
    }
    return -1;
}
int checkPositionWithoutPoint(int nIdx, int kIdx, int nnIdx) {
    
    if (nPoints[nIdx].y < nPoints[nnIdx].y) {//nidx < nnidx
        
        if (kPoints[kIdx].y < nPoints[nnIdx].y && kPoints[kIdx].y > nPoints[nIdx].y) {
            
            return ccw(nPoints[nnIdx], kPoints[kIdx], nPoints[nIdx]);
        }
    }
    else if (nPoints[nIdx].y > nPoints[nnIdx].y) {//nnidx < nidx
        if (kPoints[kIdx].y < nPoints[nIdx].y && kPoints[kIdx].y > nPoints[nnIdx].y) {
            
            return ccw(nPoints[nIdx], kPoints[kIdx], nPoints[nnIdx]);
        }
    }
    else {//x축에 대칭인 선에대한 경우 도형의 변 위에 존재하는지 확인, 존재하면 return 0
        if (nPoints[nIdx].y != kPoints[kIdx].y) {
            return -1;
        }
        if (nPoints[nIdx].x <= kPoints[kIdx].x && kPoints[kIdx].x <= nPoints[nnIdx].x) {//nidx <= kidx <= nnidx
            return 0;
        }
        else if (nPoints[nnIdx].x <= kPoints[kIdx].x && kPoints[kIdx].x <= nPoints[nIdx].x) {//nnidx <= kIdx <= nIdx
            return 0;
        }
    }

    return -1;
}
int checkPositionPoint(int kIdx, int n) {//폴리곤 밖에서 점 하나랑만 만나는 점이 문제이다
    int temp = 0;
    for (int i = 0; i < n; i++) {
        if (nPoints[i].y == kPoints[kIdx].y && nPoints[i].x == kPoints[kIdx].x) {//같은 위치에 점이 있음
            return -1;
        }
        else if (nPoints[i].y == kPoints[kIdx].y && nPoints[i].x > kPoints[kIdx].x) {
            temp++;
        }
    }
    return temp;
}
void solve(int n, int k) {
    int i, j;
    for (i = 0; i < k; i++) {
        int temp = 0;
        temp = isOnEdge(i, n);
        checker[i] = temp;
        if (checker[i] > 0) {
            continue;
        }
        for (j = 1; j <= n; j++) {
            temp = checkPosition(j % n, i, j - 1);
            if (temp > 0) {
                checker[i]++;
            }
            
        }
        
    }

}
int main() {
    input_fp = fopen("point.inp", "rt");
    output_fp = fopen("point.out", "wt");
    int n = 0;
    int x, y;
    fscanf(input_fp, "%d", &n);
    for (int i = 0; i < n; i++) {
        fscanf(input_fp, "%d %d", &x, &y);
        nPoints[i].x = x;
        nPoints[i].y = y;
    }
    int k;
    fscanf(input_fp, "%d", &k);
    for (int i = 0; i < k; i++) {
        fscanf(input_fp, "%d %d", &x, &y);
        kPoints[i].x = x;
        kPoints[i].y = y;
    }

    solve(n, k);

    for (int i = 0; i < k; i++) {
        fprintf(output_fp, "%d\n", checker[i]%2);
    }
    fclose(input_fp);
    fclose(output_fp);
    return 0;
}
