#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <stack>
#define MAXDIGITS 100
#define PLUS 1
#define MINUS -1

using namespace std;

typedef struct {
    char digits[MAXDIGITS];
    int signbit;
    int lastdigit;
}bignum;
int max(int a, int b) {
    return a > b ? a : b;
}
int compare_bignum(bignum* a, bignum* b);
void initialize_bignum(bignum* c);
void zero_justify(bignum* n);
void digit_shift(bignum* n, int d);
void divide_bignum(bignum* a, bignum* b, bignum* c);
void multiply_bignum(bignum* a, bignum* b, bignum* c);
void subtract_bignum(bignum* a, bignum* b, bignum* c);
void add_bignum(bignum* a, bignum* b, bignum* c);
int main() {
    bignum a, b;
    initialize_bignum(&a);
    initialize_bignum(&b);
    a.digits[0] = 0;
    a.digits[1] = 2;
    a.digits[2] = 1;
    a.lastdigit = 2;
    b.digits[0] = 5;
    b.lastdigit = 0;
    bignum result;
    multiply_bignum(&a, &b, &result);
    return 0;
}
int compare_bignum(bignum* a, bignum* b) {
    //b�� �� ũ�� 1, a�� �� ũ�� -1, ������ 0
    if (a->signbit == MINUS && b->signbit == PLUS)
        return PLUS;
    if (a->signbit == PLUS && b->signbit == MINUS)
        return MINUS;

    //������ �ε����� �ٸ����
    if (b->lastdigit > a->lastdigit)
        return PLUS * a->signbit;
    if (b->lastdigit < a->lastdigit)
        return MINUS * a->signbit;

    //������ �ε����� �������
    for (int i = a->lastdigit; i >= 0; i--) {
        if (b->digits[i] > a->digits[i])
            return PLUS * a->signbit;
        if (b->digits[i] < a->digits[i])
            return MINUS * a->signbit;
    }
    //������ ���� ������ ���
    return 0;
}
void initialize_bignum(bignum* c) {//c �ʱ�ȭ
    for (int i = 0; i < MAXDIGITS; i++) {
        c->digits[i] = 0;
        c->signbit = PLUS;
    }
}
void zero_justify(bignum* n) {
    //lastdigit��ġ�� Ȯ���ϰ� ��ġ�� 0�� ��������� �ڸ����� �ϳ� �����
    while ((n->lastdigit > 0) && (n->digits[n->lastdigit] == 0)) {
        n->lastdigit--;
    }

    //lastdigit�� �缳�� �� �� 0�� ������ -0�� ���ϱ����� �÷����� �ٲ۴�
    if ((n->lastdigit == 0) && (n->digits[0] == 0)) {
        n->signbit = PLUS;
    }
}
void digit_shift(bignum* n, int d) {//n��  10^d��ŭ ������
    //n�� 0�̸� ����
    if (n->lastdigit == 0 && n->digits[0] == 0)
        return;
    for (int i = n->lastdigit; i >= 0; i--) {
        n->digits[i + d] = n->digits[i];
    }
    for (int i = 0; i < d; i++) {
        n->digits[i] = 0;

    }

    n->lastdigit += d;
}
void divide_bignum(bignum* a, bignum* b, bignum* c) {
    initialize_bignum(c);
    c->signbit = a->signbit * b->signbit;

    int asign = a->signbit;
    int bsign = b->signbit;

    a->signbit = PLUS;
    b->signbit = PLUS;

    bignum row, temp;
    initialize_bignum(&row);
    initialize_bignum(&temp);

    c->lastdigit = a->lastdigit;

    for (int i = a->lastdigit; i >= 0; i--) {
        digit_shift(&row, 1);
        row.digits[0] = a->digits[i];
        c->digits[i] = 0;
        while (compare_bignum(&row, b) != PLUS) {
            c->digits[i]++;
            subtract_bignum(&row, b, &temp);
            row = temp;
        }

    }
    zero_justify(c);
    a->signbit = asign;
    b->signbit = bsign;
}
void multiply_bignum(bignum* a, bignum* b, bignum* c) {//��
    initialize_bignum(c);

    //row�� a�������� ����
    bignum row = *a;
    bignum temp;

    for (int i = 0; i <= b->lastdigit; i++) {

        //digit��ŭ ������ �ݺ��ؼ� ���� ���
        for (int j = 1; j <= b->digits[i]; j++) {
            add_bignum(c, &row, &temp);
            *c = temp;
        }
        //���� ����� ����Ʈ
        digit_shift(&row, 1);
    }
    c->signbit = a->signbit * b->signbit;
    zero_justify(c);
}
void subtract_bignum(bignum* a, bignum* b, bignum* c) {//��
    initialize_bignum(c);

    if (a->signbit == MINUS || b->signbit == MINUS) {
        b->signbit = -1 * b->signbit;
        add_bignum(a, b, c);
        b->signbit = -1 * b->signbit;
        return;
    }

    if (compare_bignum(a, b) == PLUS) {
        subtract_bignum(b, a, c);
        c->signbit = MINUS;
        return;
    }

    c->lastdigit = max(a->lastdigit, b->lastdigit);
    int borrow = 0;
    int v;
    for (int i = 0; i <= c->lastdigit; i++) {
        v = a->digits[i] - borrow - b->digits[i];

        if (a->digits[i] > 0)
            borrow = 0;
        if (v < 0) {
            v = v + 10;
            borrow = 1;
        }
        c->digits[i] = (char)(v % 10);
    }

    zero_justify(c);
}
void add_bignum(bignum* a, bignum* b, bignum* c) {//��

    initialize_bignum(c);

    if (a->signbit == b->signbit)
        c->signbit = a->signbit;
    else {
        if (a->signbit == MINUS) {
            a->signbit = PLUS;
            subtract_bignum(b, a, c);
            a->signbit = MINUS;
        }
        else {
            b->signbit = PLUS;
            subtract_bignum(a, b, c);
            b->signbit = MINUS;
        }
        return;
    }

    c->lastdigit = max(a->lastdigit, b->lastdigit) + 1;

    int carry = 0;

    for (int i = 0; i <= c->lastdigit; i++) {
        int calced = carry + a->digits[i] + b->digits[i];
        c->digits[i] = (char)(calced) % 10;
        carry = calced / 10;
    }

    zero_justify(c);
}