#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
FILE* input_fp, * output_fp;
FILE* testout;
typedef struct node {
    int x1, y1;
    int x2, y2;
}node_t;
typedef struct line {
    int y1, y2, x;
    int st;
}yLine_t;
node_t* array[10001];
node_t* same[10001];
int startIdx = 0;
int nowX = -1;
int nextX;
int Y;

int segXIdx[20001];
int segmentX[20001];

int segYIdx[20001];
int segmentY[20001];

int temp[20001];

int startX = 0;
int endX = 0;

int startY = 0;
int endY = 0;
int table[20001][20001];

yLine_t lines[20001];
int sumAndCount[2][20001];
int saveIndex[20001];
int cmpLine(const void* a, const void* b) {
    return (*(yLine_t*)a).x - (*(yLine_t*)b).x;
}
int compareReverse(const void* a, const void* b) {
    return *(int*)b - *(int*)a;
}
int compare(const void* a, const void* b) {
    return *(int*)a - *(int*)b;
}
int cmpReverseX(const void* a, const void* b) {
    return (*(node_t**)b)->x2 - (*(node_t**)a)->x2;
}
int cmpX(const void* a, const void* b) {
    return (*(node_t**)a)->x1 - (*(node_t**)b)->x1;
}
int compareY(const void* a, const void* b) {
    return (*(node_t**)b)->y2 - (*(node_t**)a)->y2;
}
int partition(int start, int end, int segment[], int target) {
    if (start == end) {
        return end;
    }
    int pivot = (start + end) / 2;
    if (segment[pivot] == target) {
        return pivot;
    }
    if (segment[pivot] > target) {
        return partition(start, pivot-1, segment, target);
    }
    else {
        return partition(pivot+1, end, segment, target);
    }
}

int getSegmentX(int n) {
    int now = -1;
    int now2 = -1;
    int count = 0;
    int count2 = 0;

    for (int i = 0; i < n; i++) {
        now = array[i]->x2;
        temp[count++] = now;
        now2 = array[i]->x1;
        temp[count++] = now2;
    }

    qsort(temp, count, sizeof(int), compare);
    now = -1;
    count2 = 0;
    for (int i = 0; i < count; i++) {
        if (now != temp[i]) {
            now = temp[i];
            segmentX[count2] = now;
            segXIdx[count2++] = i;
        }
    }
    return count2;
}
int getSegmentY(int n) {
    int now = -1;
    int now2 = -1;
    int count = 0;
    int count2 = 0;

    for (int i = 0; i < n; i++) {
        now = array[i]->y2;
        temp[count++] = now;
        now2 = array[i]->y1;
        temp[count++] = now2;
    }

    qsort(temp, count, sizeof(int), compare);
    now = -1;
    count2 = 0;
    for (int i = 0; i < count; i++) {
        if (now != temp[i]) {
            now = temp[i];
            segmentY[count2] = now;
            segYIdx[count2++] = i;
        }
    }
    return count2;
}
int getXIndex_lines(int nodeIdx, int len) {
    //절반으로 나누면서 찾아야 lg(n)

    int nodeX = lines[nodeIdx].x;
    return partition(0, len - 1, segmentX, nodeX);
    
}
int getXIndex(int nodeIdx, int len, int m) {
    
    if (m == 2) {
        int nodeX = array[nodeIdx]->x2;
        return partition(0, len-1, segmentX, nodeX);
        
    }
    else if (m == 1) {
        int nodeX = array[nodeIdx]->x1;
        return partition(0, len-1, segmentX, nodeX);
    }
    return -1;
}
int getYIndex(int nodeIdx, int len, int m) {

    if (m == 2) {
        int nodeY = array[nodeIdx]->y2;
        return partition(0, len - 1, segmentY, nodeY);

    }
    else if (m == 1) {
        int nodeY = array[nodeIdx]->y1;
        return partition(0, len - 1, segmentY, nodeY);
    }

    return -1;
}
int getYIndex_lines(int nodeIdx, int len, int m) {
    if (m == 1) {
        int nodeY = lines[nodeIdx].y1;
        return partition(0, len - 1, segmentY, nodeY);
    }
    if (m == 2) {
        int nodeY = lines[nodeIdx].y2;
        return partition(0, len - 1, segmentY, nodeY);
    }
    return -1;
}

int solve2(int n) {
    int sum = 0;
    int count = 0;
    int segYNum = getSegmentY(n);//y값을 기준으로 쪼갬, 변수 값=배열의 y축 크기
    int segXNum = getSegmentX(n);//x값으로 쪼개서 구간 확인 변수 값=배열의 x축 크기

    int x1, x2, y1, y2, x;
    int nx, ny1, ny2;
    for (int i = 0; i < n*2 ; i++) {//배열 모두돌면서 각각의 노드에대해 마킹
        x = getXIndex_lines(i, segXNum);
        y1 = getYIndex_lines(i, segYNum, 1);
        y2 = getYIndex_lines(i, segYNum, 2);

        if (lines[i].st == 1) {//사각형 시작
            for (int j = 0; j < y1; j++) {
                if (sumAndCount[1][j] > 0) {//0보다 크면 사각형이 이어지고있다는 뜻
                    sumAndCount[0][j] += (segmentY[j + 1] - segmentY[j]) * (segmentX[x] - segmentX[saveIndex[j]]);
                    saveIndex[j] = x;
                }
            }
            for (int j = y1; j < y2; j++) {
                if (sumAndCount[1][j] > 0) {
                    sumAndCount[0][j] += (segmentY[j+1]  - segmentY[j]) * (segmentX[x] - segmentX[saveIndex[j]]);
                    saveIndex[j] = x;
                }
                sumAndCount[1][j]++;
                saveIndex[j] = x;
            }
            for (int j = y2; j < segYNum-1; j++) {
                if (sumAndCount[1][j] > 0) {
                    sumAndCount[0][j] += (segmentY[j + 1] - segmentY[j]) * (segmentX[x] - segmentX[saveIndex[j]]);
                    saveIndex[j] = x;
                }
            }
        }
        else if (lines[i].st == -1) {//사각형 끝
            for (int j = 0; j < y1; j++) {
                if (sumAndCount[1][j] > 0) {//0보다 크면 사각형이 이어지고있다는 뜻
                    sumAndCount[0][j] += (segmentY[j + 1] - segmentY[j]) * (segmentX[x] - segmentX[saveIndex[j]]);
                    saveIndex[j] = x;
                }
            }
            for (int j = y1; j < y2; j++) {
                if (sumAndCount[1][j] > 0) {
                    sumAndCount[0][j] += (segmentY[j + 1] - segmentY[j]) * (segmentX[x] - segmentX[saveIndex[j]]);
                    saveIndex[j] = x;
                }
                sumAndCount[1][j]--;
            }
            for (int j = y2; j < segYNum-1; j++) {
                if (sumAndCount[1][j] > 0) {
                    sumAndCount[0][j] += (segmentY[j + 1] - segmentY[j]) * (segmentX[x] - segmentX[saveIndex[j]]);
                    saveIndex[j] = x;
                }
            }
        }

    }

    for (int i = 0; i < segYNum-1; i++) {
        sum += sumAndCount[0][i];
    }
    return sum;
}
node_t* allocateNode(int x1, int y1, int x2, int y2) {
    node_t* temp = (node_t*)malloc(sizeof(node_t));
    temp->x1 = x1;
    temp->y1 = y1;
    temp->x2 = x2;
    temp->y2 = y2;
    return temp;
}

int random(int range) {
    return (rand() % range) + 1 - 10000;
}
void test(int n) {
    for (int i = 0; i < n; i++) {
        int x1 = random(20000);
        int y1 = random(20000);
        int x2, y2;
        do {
            x2 = random(20000);
        } while (x2 < x1);
        do {
            y2 = random(20000);
        } while (y2 < y1);
        fprintf(testout, "%d %d %d %d\n", x1, y1, x2, y2);
    }
        
}
int main() {
    input_fp = fopen("rectangles.inp", "rt");
    output_fp = fopen("rectangles.out", "wt");
    //testout = fopen("test", "wt");
    //srand(time(NULL));
    //test(5000);
    int n;
    fscanf(input_fp, "%d", &n);

    for (int i = 0; i < n; i++) {
        int x1, y1, x2, y2;
        fscanf(input_fp, "%d %d %d %d", &x1, &y1, &x2, &y2);
        array[i] = allocateNode(x1+10000, y1+10000, x2+10000, y2+10000);
        lines[i * 2].x = x1 +10000;
        lines[i * 2].y1 = y1+10000;
        lines[i * 2].y2 = y2+10000;
        lines[i * 2].st = 1;//사각형 시작하는 선

        lines[i * 2 + 1].x = x2+10000;
        lines[i * 2 + 1].y1 = y1+10000;
        lines[i * 2 + 1].y2 = y2+10000;
        lines[i * 2 + 1].st = -1;//사각형 끝나는 선
    }
    qsort(lines, n * 2, sizeof(yLine_t), cmpLine);
    qsort(array, n, sizeof(node_t*), cmpX);
    int sum = solve2(n);
    fprintf(output_fp, "%d", sum);

    //fclose(testout);
    fclose(input_fp);
    fclose(output_fp);
    return 0;
}