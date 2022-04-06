#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <queue>
using namespace std;
FILE* input_fp;
FILE* output_fp;

//typedef struct node {
//    char text[17];
//    struct node* next;
//}node_t;

//typedef struct node {
//    int st;
//    struct node* next;
//}node_t;
char* dictionary[17][26000];
int dictionaryLength[17];
int table[26000];

int max(int x, int y) {
    return x > y ? x : y;
}
void resetTable(int len) {
    for (int i = 0; i < len; i++) {
        table[i] = -1;
    }
}
void printer(int st1, int st2, int textLen, int nowIdx) {
    if (nowIdx == st1) {
        fprintf(output_fp, "%s\n", dictionary[textLen][nowIdx]);
        return;
    }
    printer(st1, st2, textLen, table[nowIdx]);
    fprintf(output_fp, "%s\n", dictionary[textLen][nowIdx]);
    return;
}
//node_t* allocateNode() {
//    node_t* temp = (node_t*)malloc(sizeof(node_t));
//    temp->next = NULL;
//    temp->text[0] = '\0';
//    return temp;
//}
//node_t* allocateNode(int st) {
//    node_t* temp = (node_t*)malloc(sizeof(node_t));
//    temp->next = NULL;
//    temp->st = st;
//    return temp;
//}
int isDoublet(int t1Idx, int t2Idx, int txtLen) {
    
    int checker = 0;
    char* text1 = dictionary[txtLen][t1Idx];
    char* text2 = dictionary[txtLen][t2Idx];
    for (int i = 0; i < txtLen; i++) {
        if (text1[i] != text2[i]) {
            checker++;
        }
    }
    if (checker == 1)
        return 1;
    return 0;
}
int isPrev(char* text, int tableLen) {
    
    return 0;
}
int main() {
    input_fp = fopen("p10150.inp", "rt");
    output_fp = fopen("p10150.out", "wt");
    int len = 0;
    for (int j = 0; 1; j++) {
        char* line = (char*)malloc(sizeof(char) * 17);
        for (int i = 0; 1; i++) {
            fscanf(input_fp, "%c", &line[i]);
            if (line[i] == '\n') {
                line[i] = '\0';
                len = i;
                break;
            }
        }
        if (len == 0) {
            break;
        }
        dictionary[len][dictionaryLength[len]] = line;
        dictionaryLength[len]++;
    }//dictionary 받기 끝

    char text1[17] = { '\0' };
    char text2[17] = { '\0' };
    while (fscanf(input_fp, "%s %s", text1, text2) != EOF) {//라인 끝까지 반복
        int text1Len = strlen(text1);
        int text2Len = strlen(text2);
        int checker1 = 1;
        int st1 = 0;
        for (int i = 0; i < dictionaryLength[text1Len]; i++) {//text1 같은 단어가 dictionary에 있는지 확인
            checker1 = strcmp(dictionary[text1Len][i], text1);
            if (checker1 == 0) {
                st1 = i;
                break;
            }
        }

        int checker2 = 1;
        int st2 = 0;
        for (int i = 0; i < dictionaryLength[text2Len]; i++) {//text2 같은 단어가 dictionary에 있는지 확인
            checker2 = strcmp(dictionary[text2Len][i], text2);
            if (checker2 == 0) {
                st2 = i;
                break;
            }
        }

        if (text1Len != text2Len || checker1 || checker2) {//text1 과 2가 서로 다른 길이거나 dictionary에 단어가 없으면 정답 없음
            fprintf(output_fp, "No solution.\n");
        }
        else {
            resetTable(dictionaryLength[text1Len]);//테이블 초기화
            table[st1] = st1;
            queue<int> q;
            q.push(st1);
            while (q.front() != st2&& q.size()){//큐가 NULL이면 못찾음, 큐의 front가 st2 이면 정답 찾음
                int now = q.front();
                q.pop();
                for (int i = 0; i < dictionaryLength[text1Len]; i++) {
                    if (!isDoublet(now, i, text1Len) || table[i] != -1) {//더블릿 아니면 넘김, 테이블에 숫자 들어있으면 이미 한번 확인한 것이므로 넘김
                        continue;
                    }
                    table[i] = now;
                    q.push(i);
                }
            }
            if (table[st2] == -1) {//text2 발견 못한경우
                fprintf(output_fp, "No solution.\n");
            }
            else {
                printer(st1, st2, text1Len, st2);
            }
            
        }
        fprintf(output_fp, "\n");
    }

    fclose(input_fp);
    fclose(output_fp);
    return 0;
}
