#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int ans = 0;
int N;
typedef struct node {
    int child;
    struct node* next;
}node_t;
struct node* nodeAllocate(int child) {//노드를 만들어서 리턴
    node_t* new_node = (node_t*)malloc(sizeof(node_t));
    new_node->child = child;
    new_node->next = NULL;
    return new_node;

}
node_t* arr[500000] = { NULL };
node_t* tail[500000] = { NULL };
void insertNode(node_t* temp, int index) {
    node_t* head = arr[index];
    if (arr[index] == NULL) {
        arr[index] = temp;
        return;
    }
    while (head->next != NULL) {
        head = head->next;
    }
    head->next = temp;
    return;
}

int search(int index, int reset) {
    static int memo[500000];
    if (reset == 1) {
        for (int i = 0; i < N; i++) {
            memo[i] = 0;
        }
        return -1;
    }

    node_t* head = arr[index];
    int depth=1;
    if (memo[index] > 0)
        return memo[index];
    while (head != NULL) {
        depth = 1;
        
        depth += search(head->child, 0);

        if (depth > memo[index]) {
            memo[index] = depth;
        }
        head = head->next;
    }
    if (memo[index] > ans)
        ans = memo[index];
    return memo[index];
}
void resetPointer(node_t* head) {
    if (head->next == NULL) {
        free(head);
        return;
    }
    resetPointer(head->next);
    head->next = NULL;
}
void reset() {
    search(0, 1);//memo초기화
    for (int i = 0; i < N; i++) {
        if (arr[i] != NULL) {
            resetPointer(arr[i]);
            arr[i] = NULL;
        }
    }
    ans = 0;
}
int main() {
    FILE* fp_in, * fp_out;
    fp_in = fopen("family.inp", "r");
    fp_out = fopen("family.out", "w");
    int T;
    int parent, child;
    fscanf(fp_in, "%d", &T);

    while (T > 0) {
        fscanf(fp_in,"%d", &N);
        for (int i = 0; i < N-1; i++) {
            
            fscanf(fp_in, "%d %d", &parent, &child);
            //node_t* temp = nodeAllocate(child-1);
            node_t* temp = (node_t*)malloc(sizeof(node_t));
            temp->child = child-1;
            temp->next = NULL;

            //insertNode(temp, parent - 1);
            node_t* head = arr[parent-1];
            if (arr[parent - 1] == NULL) {
                arr[parent - 1] = temp;
                tail[parent - 1] = temp;
            }
            else {
                tail[parent-1]->next = temp;
                tail[parent - 1] = tail[parent - 1]->next;
            }

        }
        //
        int a;
        for (int i = 0; i < N; i++) {
            a = search(i,0);
        }
        
        fprintf(fp_out, "%d\n", ans+1);
        reset();
        T--;
    }

    fclose(fp_in);
    fclose(fp_out);
    return 0;
}