#include <string.h>
#include <stdio.h>
#include <stdlib.h>

FILE* input, * output;

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
void swap(char* text, int a, int b) {
    if (a == b) {
        return;
    }
    char temp = text[a];
    text[a] = text[b];
    text[b] = temp;
    return;
}
void getPrev(char* text) {
    int len = strlen(text) - 1;
    char ans[1001] = "\0";
    strcpy(ans, text);
    int firstCharIndex = -1;
    for (int i = len; i > 0; i--) {
        if (text[i] < text[i - 1]) {
            firstCharIndex = i - 1;
            break;
        }
    }
    if (firstCharIndex == -1) {
        fprintf(output, "-1 ");
        return;
    }

    int secondCharIndex = -1;
    for (int i = firstCharIndex + 1, j = len; i < j; i++, j--) {
        swap(ans, i, j);
    }
    for (int i = firstCharIndex + 1; ans[i] != '\0'; i++) {
        if (ans[i] < ans[firstCharIndex]) {
            if (secondCharIndex == -1) {
                secondCharIndex = i;
            }
            else if (ans[i] > ans[secondCharIndex]) {
                secondCharIndex = i;
            }

        }
    }
    
    swap(ans, firstCharIndex, secondCharIndex);
    fprintf(output, "%s ", ans);
    return;
}
void getNext(char* text) {
    int firstCharIndex = -1;
    char ans[1001] = "";
    strcpy(ans, text);
    int len = strlen(text) - 1;
    for (int i = 0; i + 1 <= len; i++) {
        if (text[i] < text[i + 1]) {
            firstCharIndex = i;
        }
    }

    if (firstCharIndex == -1) {
        fprintf(output, "-1\n");
        return;
    }
    int secondCharIndex = -1;
    for (int i = firstCharIndex + 1; i<=len; i++) {
        if (text[i] > text[firstCharIndex]) {
            if (secondCharIndex == -1) {
                secondCharIndex = i;
            }
            else if (text[i] <= text[secondCharIndex]) {
                secondCharIndex = i;
            }
            
        }
    }
    swap(ans, firstCharIndex, secondCharIndex);

    for (int i = firstCharIndex + 1, j = len; i < j; i++, j--) {
        swap(ans, i, j);
    }
    fprintf(output, "%s\n", ans);
    return;
}
int main() {
    input = fopen("string.inp", "r");
    output = fopen("string.out", "w");
    //FILE* check = fopen("test.inp", "r");
    int T;
    fscanf(input, "%d", &T);
    
    while (T--) {
        char text[1001] = "";
        fscanf(input, "%s", text);
        
        getPrev(text);
        getNext(text);
    }
    /*fclose(output);
    output = fopen("string.out", "r");

    char tt[1001]=" ";
    char cc[1001]=" ";
    while (1) {
        if (fscanf(output, "%s ", tt) == -1 || fscanf(check, "%s ", cc) == -1) {
            break;
        }
        
        int a = strcmp(tt, cc);
        if (a != 0) {
            printf("%s\t%s\n", tt, cc);
            printf("check: %d\n", strcmp(tt, cc));
        }
    }
     fclose(check);
    */
    fclose(output);
    fclose(input);
    
    return 0;
}