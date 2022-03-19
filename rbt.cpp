#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE* input_fp;
FILE* output_fp;

typedef struct node {
    int key;
    char color;
    struct node* left;
    struct node* right;
}node_t;

node_t* root = NULL;
node_t* stack[100] = { NULL };
node_t* leaf;
int top = -1;
int max(int a, int b) {
    if (a > b)
        return a;
    return b;
}
node_t* findParent(int key);
node_t* find(int key);
node_t* allocateNode(int key);
void rbtInsert(node_t* node);
void rightRotate(node_t* parent);
void leftRotate(node_t* parent);
void insert(node_t* node);
node_t* successor(int key);
char color(int key);
node_t* del(int key);
void deleteFixup(node_t* x);
void rbDelete(int key);
int main() {
    input_fp = fopen("rbt.inp", "rt");
    output_fp = fopen("rbt.out", "wt");
    leaf = allocateNode(-1);
    leaf->color = 'b';
    char command;
    int key;
    while (1) {
        fscanf(input_fp, "%c %d ", &command, &key);

        if (key == -1)
            break;
        if (command == 'i') {
            node_t* node = allocateNode(key);
            rbtInsert(node);
            top = -1;
        }
        else if (command == 'c') {
            if (color(key) == 'r') {
                fprintf(output_fp, "color(%d): RED\n", key);
            }
            else {
                fprintf(output_fp, "color(%d): BLACK\n", key);
            }
        }
        else if (command == 'd') {
            rbDelete(key);
            top = -1;
        }

    }
    fclose(input_fp);
    fclose(output_fp);
    return 0;
}
node_t* allocateNode(int key) {
    node_t* temp = (node_t*)malloc(sizeof(node_t));

    temp->color = 'r';
    temp->key = key;
    temp->left = leaf;
    temp->right = leaf;

    return temp;
}
void rightRotate(node_t* parent) {
    node_t* temp = parent->left;
    node_t* gp = findParent(parent->key);

    parent->left = temp->right;
    temp->right = parent;
    if (gp == NULL) {
        root = temp;
    }
    else if (gp->left == parent) {
        gp->left = temp;
    }
    else {
        gp->right = temp;
    }
    
}
void leftRotate(node_t* parent) {
    node_t* child = parent->right;
    node_t* gp = findParent(parent->key);

    parent->right = child->left;
    child->left = parent;
    if (gp == NULL) {
        root = child;
    }
    else if (gp->left == parent) {
        gp->left = child;
    }
    else {
        gp->right = child;
    }
}
void rbtInsert(node_t* node) {
    insert(node);
    node_t* now = node;
    while (now != root && stack[top]->color == 'r') {
        node_t* gp = stack[top - 1];
        node_t* parent = stack[top];
        
        if (parent == gp->left) {
            node_t* uncle = stack[top - 1]->right;
            if (uncle->color == 'r') {
                parent->color = 'b';
                uncle->color = 'b';
                gp->color = 'r';
                now = gp;
                top = top - 2;
            }
            else {
                if (now == parent->right) {
                    
                    leftRotate(parent);
                    node_t* temp = now;
                    now = parent;
                    parent = temp;
                    stack[top] = parent;
                }
                parent->color = 'b';
                gp->color = 'r';
                rightRotate(gp);
                stack[--top] = parent;
            }
        }//left
        else {
            node_t* uncle = stack[top - 1]->left;
            if (uncle->color == 'r') {
                parent->color = 'b';
                uncle->color = 'b';
                gp->color = 'r';
                now = gp;
                top = top - 2;
            }
            else {
                if (now == parent->left) {

                    rightRotate(parent);
                    node_t* temp = now;
                    now = parent;
                    parent = temp;
                    stack[top] = parent;
                }
                parent->color = 'b';
                gp->color = 'r';
                leftRotate(gp);
                stack[--top] = parent;
            }
        }//right
    }//while
    root->color = 'b';
}
void insert(node_t* node) {
    if (root == NULL) {
        root = node;
        return;
    }
    node_t* prev = NULL;
    node_t* now = root;

    while (now != leaf && now != NULL) {

        if (now->key < node->key) {
            prev = now;
            stack[++top] = now;
            
            now = now->right;
        }
        else {
            prev = now;
            stack[++top] = now;
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
node_t* successor(int key) {
    int top = -1;
    node_t* now = root;
    node_t* temp = NULL;
    while (now != leaf) {

        stack[++top] = now;

        if (now->key > key) {
            if (temp == NULL)
                temp = now;
            else if (temp->key > now->key) {
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
char color(int key) {
    node_t* now = find(key);
    return now->color;
}
node_t* find(int key) {
    node_t* now = root;
    while (now->key != key) {//find node
        //stack[++top] = now;
        if (now->key < key) {
            now = now->right;
        }
        else {
            now = now->left;
        }
    }
    return now;
}
node_t* findParent(int key) {
    node_t* parent = NULL;
    node_t* now = root;
    while (now->key != key) {//find node
        //stack[++top] = now;
        parent = now;
        if (now->key < key) {
            now = now->right;
        }
        else {
            now = now->left;
        }
    }
    return parent;
}
void rbDelete(int key) {
    node_t* y = del(key);
    node_t* x;
    if (y->left != leaf) {
        x = y->left;
    }
    else {
        x = y->right;
    }
    
    if (y->color == 'b') {
        deleteFixup(x);
    }
    free(y);
}
void deleteFixup(node_t* x) {
    while (x != root && x->color == 'b') {
        node_t* parent = stack[top];
        if (x == parent->left) {
            node_t* w = parent->right;
            if (w->color == 'r') {//case1
                w->color = 'b';
                parent->color = 'r';
                leftRotate(parent);

                stack[top] = w;
                stack[++top] = parent;

                w = parent->right;

            }

            if (w->left->color == 'b' && w->right->color == 'b') {//case2
                w->color = 'r';
                x = parent;
                parent = stack[--top];

            }
            else if (w->right->color == 'b') {//case3
                w->left->color = 'b';
                w->color = 'r';
                rightRotate(w);
                w = parent->right;
            }
            if (w->right->color == 'r') {
                w->color = parent->color;
                parent->color = 'b';
                w->right->color = 'b';
                leftRotate(parent);
                x = root;
            }
        }//left
        else {
            node_t* w = parent->left;
            if (w->color == 'r') {//case1
                w->color = 'b';
                parent->color = 'r';
                rightRotate(parent);

                stack[top] = w;
                stack[++top] = parent;

                w = parent->left;
            }
            if (w->left->color == 'b' && w->right->color == 'b') {//case2
                w->color = 'r';
                x = parent;
                parent = stack[--top];

            }
            else if (w->left->color == 'b') {//case3
                w->right->color = 'b';
                w->color = 'r';
                leftRotate(w);
                w = parent->left;
            }
            if (w->left->color == 'r') {
                w->color = parent->color;
                parent->color = 'b';
                w->left->color = 'b';
                rightRotate(parent);
                x = root;
            }
        }//right
        
    }
    x->color = 'b';
}
node_t* del(int key) {
    node_t* prev = NULL;
    node_t* now = root;
    while (now->key != key) {//find node
        stack[++top] = now;
        if (now->key < key) {
            prev = now;
            now = now->right;
        }
        else {
            prev = now;
            now = now->left;
        }
    }
    //char c = '0';
    if (now->left == leaf && now->right == leaf) {//자식 없음
        if (prev == NULL) {//root가 해당 노드
            root = NULL;
        }
        else if (prev->left == now) {
            prev->left = leaf;
        }
        else if (prev->right == now) {
            prev->right = leaf;
        }
        //c = now->color;
        //free(now);
    }
    else if (now->left != leaf && now->right != leaf) {//양쪽에 모두 자식있음
        node_t* ss = successor(key);

        int temp = ss->key;
        node_t* y = del(ss->key);
        now->key = temp;

        now = y;
    }
    else {//한쪽만 자식있음
        node_t* target = leaf;
        if (now->left != leaf) {
            target = now->left;
        }
        else if (now->right != leaf) {
            target = now->right;
        }

        if (prev == NULL) {
            root = NULL;
        }
        else if (prev->left == now) {
            prev->left = target;
        }
        else if (prev->right == now) {
            prev->right = target;
        }
        //c = now->color;
        //free(now);
    }
    return now;
}