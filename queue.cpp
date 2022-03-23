#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE* input_fp = fopen("queue.inp", "rt");
FILE* output_fp = fopen("queue.out", "wt");
int heap[1000003] = { 0 };
int size = 0;
void exchange(int i, int j) {
    int temp = heap[i];
    heap[i] = heap[j];
    heap[j] = temp;
}
void insertion() {
    int index = size;
    for (int i = size; i > 1; i /= 2) {//root전까지, 부모노드 확인하면서
        if (heap[i] > heap[i / 2]) {
            exchange(i, i / 2);
        }
        else
            return;
    }
}
void report() {
    for (int i = 1; i <= size; i *= 2) {
        fprintf(output_fp, "%d ", heap[i]);
    }
    fprintf(output_fp, "\n");
}
void del() {
    heap[1] = heap[size];
    heap[size--] = 0;
    for (int i = 1; i * 2 <= size;) {
        
        if (heap[i * 2] < heap[i * 2 + 1]) {
            if (heap[i * 2 + 1] > heap[i]) {
                exchange(i, i * 2 + 1);
                i = i * 2 + 1;
            }
            else
                break;
        }
        else {
            if (heap[i * 2] > heap[i]) {
                exchange(i, i * 2);
                i = i * 2;
            }
            else
                break;
        }
    }
}
int main() {
    char arr[20] = {};
    char n;
    int index = 0;
    while (1) {

        fscanf(input_fp, "%c", &n);
        arr[index++] = n;
        if (n == 'q') {
            break;
        }
        else if (n == '\n') {//입력 하나 종료
            
            if (arr[0] == 'r') {
                report();
            }
            else if (arr[0] == 'd') {
                del();
            }
            else {//숫자
                int key = 0;
                for (int i = 0; i < index - 1; i++) {
                    key = key * 10 + arr[i] - '0';
                }
                
                heap[++size] = key;
                insertion();
            }
            index = 0;
        }
    }
    fclose(input_fp);
    fclose(output_fp);
    return 0;
}