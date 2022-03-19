#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX 1000000
FILE* input, * output;
typedef struct node{
    int key;
    struct node* right;
    struct node* left;
}node_t;
int num = 0;
node_t* root = NULL;
node_t* allocateNode(int key) {
    node_t* temp = (node_t*)malloc(sizeof(node_t));
    temp->key = key;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}
node_t* successor(int key) {
    node_t* now = root;
    node_t* temp = NULL;
    while (now != NULL) {
        if (now->key > key) {
            if(temp == NULL)
                temp = now;
            else if(temp->key > now->key){
                temp = now;
            }
            now = now->left;
        }
        else {
            now = now->right;
        }
    }
    return temp;
}
void insert(node_t* node) {
    if (root == NULL) {
        root = node;
        return;
    }
    node_t* prev = NULL;
    node_t* now = root;
    
    while (now != NULL) {
        
        if (now->key < node->key) {
            prev = now;
            now = now->right;
        }
        else {
            prev = now;
            now = now->left;
        }
    }
    if (prev->key < node->key) {
        prev->right = node;
    }
    else {
        prev->left = node;
    }
    return;
}
void del(int key) {
    node_t* prev = NULL;
    node_t* now = root;
    while (now->key != key) {//find node
        if (now->key < key) {
            prev = now;
            now = now->right;
        }
        else {
            prev = now;
            now = now->left;
        }
    }

    if (now->left == NULL && now->right == NULL) {//자식 없음
        if (prev == NULL) {//root가 해당 노드
            root = NULL;
        }
        else if (prev->left == now) {
            prev->left = NULL;
        }
        else if (prev->right == now) {
            prev->right = NULL;
        }
        free(now);
    }
    else if (now->left != NULL && now->right !=NULL) {//양쪽에 모두 자식있음
        node_t* ss = successor(key);
        
        int temp = ss->key;
        del(ss->key);
        now->key = temp;
    }
    else {//한쪽만 자식있음
        node_t* target = NULL;
        if (now->left != NULL) {
            target = now->left;
        }
        else if (now->right != NULL) {
            target = now->right;
        }

        if (prev == NULL) {
            root = target;
        }
        else if (prev->left == now) {
            prev->left = target;
        }
        else if (prev->right == now) {
            prev->right = target;
        }
        free(now);
    }
}
int max(int a, int b) {
    if (a > b) {
        return a;
    }
    else {
        return b;
    }
}
int min(int a, int b) {
    if (a < b) {
        return a;
    }
    else {
        return b;
    }
}
int dfs(node_t* r) {
    node_t* now = r;
    int t;
    int h = 0;
    if (now->left == NULL && now->right == NULL) {
        return 1;
    }

    if (now->left != NULL) {
        t = dfs(now->left);
        if (t > h) {
            h = t;
        }
    }
    if (now->right != NULL) {
        t = dfs(now->right);
        if (t > h) {
            h = t;
        }
    }
    return h + 1;
}
int main() {
    input = fopen("bst.inp", "r");
    output = fopen("bst.out", "w");
    
    int k;
    char text;
    while (true) {
        fscanf(input, "%c %d ", &text, &k);
        if (k < 0) {
            break;
        }
        if (text == 'i') {
            node_t* newNode = allocateNode(k);
            insert(newNode);
        }
        else if (text == 'd') {
            del(k);
        }
    }
    int height = dfs(root);
    fprintf(output, "%d", height - 1);
    fclose(input);
    fclose(output);
    return 0;
}