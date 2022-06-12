#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <stack>
#define MAX 1000
#define GET_LAST_ONE(N) ((N)&(-(N)))

using namespace std;

int tree[MAX];
int t_size = 100;

void initCumulativeSum(int a[], int tree[], int size)//트리작성
{
    int i, sum, index;
    int lastOne, removeLastOne;
    for (i = 1; i <= size; i++)
    {
        lastOne = GET_LAST_ONE(i);
        removeLastOne = i - lastOne;
        sum = a[i];
        index = lastOne - 1;
        while (index > 0)
        {
            sum += tree[removeLastOne + index];
            index -= GET_LAST_ONE(index);
        }
        tree[i] = sum;
    }
}

int getCumulativeSum(int k)//k까지의 합
{
    int sum, index;
    sum = 0;
    index = k;
    while (index > 0)
    {
        sum += tree[index];
        index -= GET_LAST_ONE(index);
    }
    return sum;
}
void update(int k, int value)//배열의 값 변경 시 트리 값도 변경
{
    int index;
    index = k;
    while (index <= t_size)
    {
        tree[index] += value;
        index += GET_LAST_ONE(index);//add last significant bit
    }
}

int max(int a, int b) {
    return a > b ? a : b;
}
int main() {
    int a[100];
    for (int i = 0; i < 100; i++) {
        a[i] = i;
    }
    initCumulativeSum(a, tree, 16);
    printf("%d\n", getCumulativeSum(10));
    printf("%d\n", getCumulativeSum(5));
    printf("%d\n", getCumulativeSum(4));
    return 0;
}