#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>

FILE* input_fp = fopen("kruskal.inp", "rt");
FILE* output_fp = fopen("kruskal.out", "wt");
int ff[10000] = { 0 };
int seq[10000] = { 0 };
int same[10001] = { 0 };
typedef struct node {
    int dest[2];
    int weight;
    int num;
    struct node* next;
}node_edge;
node_edge* head = NULL;

node_edge* allocateNodeEdge(int dest1, int dest2, int weight, int num) {
    node_edge* temp = (node_edge*)malloc(sizeof(node_edge));
    temp->dest[0] = dest1;
    temp->dest[1] = dest2;
    temp->num = num;
    temp->weight = weight;
    temp->next = NULL;
    return temp;
}
void sortNode(node_edge* ne) {
    node_edge* temp = head;
    node_edge* pre = NULL;
    if (head == NULL) {
        head = ne;
        return;
    }

    while (temp != NULL) {
        if (temp->weight > ne->weight) {
            ne->next = temp;
            if (head == temp) {//제일 작다
                head = ne;
            }
            else {//중간 
                pre->next = ne;
            }
            return;
        }
        pre = temp;
        temp = temp->next;
    }
    //마지막
    pre->next = ne;
    return;
}
int compare(const void* x, const void* y) {
    return ((node_edge*)x)->weight - ((node_edge*)y)->weight;
}
void merge(int node1, int node2, int N) {
    ff[node2] = node1;
    for (int i = 0; i < N; i++) {
        if (ff[i] == node2)
            ff[i] = node1;
    }
}
void freeNode() {
    node_edge* temp = head;
    head = head->next;
    free(temp);
}
int min(int x, int y) {
    if (x > y)
        return y;
    return x;
}
int main() {
    int N, E;
    int dest[2], weight;
    
    fscanf(input_fp, "%d %d", &N, &E);
    node_edge* arr = (node_edge*)malloc(sizeof(node_edge) * E);
    for (int i = 0; i < E; i++) {
        fscanf(input_fp, "%d %d %d", &dest[0], &dest[1], &weight);
        arr[i].dest[0] = dest[0];
        arr[i].dest[1] = dest[1];
        arr[i].num = i;
        arr[i].weight = weight;
        same[weight]++;

        //sortNode(allocateNodeEdge(dest[0], dest[1], weight, i));
    }
    qsort(arr, E, sizeof(node_edge), compare);
    for (int i = 0; i < N; i++) {
        ff[i] = i;
    }
    int F = N - 1;
    int sum = 0;
    int index = 0;
    int min_index;
    node_edge temp;
    for (int i = 0; i < E && F;i++) {
        /*
        int p = ff[head->dest[0]];
        int q = ff[head->dest[1]];
        */
        if (same[arr[i].weight] > 1) {//같은거 여러개 있다
            min_index = i;
            for (int j = i + 1; j < same[arr[i].weight]; j++) {
                if (arr[min_index].num > arr[j].num) {
                    min_index = j;
                }
            }
            temp = arr[i];
            arr[i] = arr[min_index];
            arr[min_index] = temp;
            same[arr[i].weight]--;
        }
        int p = ff[arr[i].dest[0]];
        int q = ff[arr[i].dest[1]];
        
        if (p != q) {
            merge(p, q, N);
            //sum += head->weight;
            sum += arr[i].weight;
            //seq[index] = head->num;
            seq[index] = arr[i].num;
            F--;
            index++;
        }
        //freeNode();
    }
    int a;
    /*
    fscanf(input_test, "%d", &a);
    if (sum != a) {
        fprintf(output_test, "sum : %d\n", sum);
    }*/
    fprintf(output_fp, "%d\n", sum);
    for (int i = 0; i < index; i++) {/*
        fscanf(input_test, "%d", &a);
        if (seq[i] != a) {
            fprintf(output_test, "seq[%d] : %d\n", i, seq[i]);
        }*/
        fprintf(output_fp, "%d\n", seq[i]);
    }
    /*
    fclose(input_test);
    fclose(output_test);*/
    fclose(input_fp);
    fclose(output_fp);
    return 0;
}