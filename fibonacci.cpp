#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int SIZE = 2;
int M;
long long findCirculation(int m) {
	long long i, fi0, fi1, temp;
	fi0 = 1;
	fi1 = 1;
	for (i = 3; fi0 != 0 || fi1 != 1; i++) {
		temp = fi1;
		fi1 = fi1 + fi0;
		fi1 %= m;
		fi0 = temp;
	}
	return i - 2;
}
long long fibo(long long n, int m) {
	long long i, fi0, fi1, temp;
	if (n == 1 || n == 2)
		return 1;
	if (n == 0)
		return 0;
	fi0 = 1;
	fi1 = 1;
	for (i = 3; i <= n; i++) {
		temp = fi1;
		fi1 = fi1 + fi0;
		fi1 %= m;
		fi0 = temp;
	}
	return fi1;
}
long long** allocateMatrix(int size) {
	long long** temp = (long long**)malloc(sizeof(long long*) * size);
	for (int i = 0; i < size; i++) {
		temp[i] = (long long*)malloc(sizeof(long long) * size);
	}
	for (long long i = 0; i < size; i++) {
		temp[i][i] = 0;
	}
	return temp;
}
void matrixCalc (long long left[][2], long long right[][2], long long result[][2]) {
	
	long long temp[2][2] = { 0 };
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			for (int k = 0; k < SIZE; k++) {
				temp[i][j] += (left[i][k] % M * right[k][j] % M) % M;
			}
			temp[i][j] %= M;
		}
	}
	for (long long i = 0; i < SIZE; i++) {
		for (long long j = 0; j < SIZE; j++) {
			result[i][j] = temp[i][j];
		}
	}
}
long long** findAns(long long a[][2], long long b) {

	long long temp[2][2] = { 0 };
	long long** result = allocateMatrix(SIZE);

	for (int i = 0; i < SIZE; i++) {
		temp[i][i] = 1;
	}

	while (b) {
		if (b % 2) {
			matrixCalc(temp, a, temp);
		}
		b /= 2;
		matrixCalc(a, a, a);
	}
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			result[i][j] = temp[i][j];
		}
	}
	return result;
}
int main() {
	FILE* input_fp, * output_fp;
	input_fp = fopen("fibonacci.inp", "rt");
	output_fp = fopen("fibonacci.out", "wt");

	long long a[4];
	int T, ans = 0;
	long long fa[4];

	fscanf(input_fp, "%d", &T);
	while (T > 0) {
		fscanf(input_fp, "%lld %lld %lld %lld %d", &a[0], &a[1], &a[2], &a[3], &M);
		//long long cir_index = findCirculation(m);
		
		for (int i = 0; i < 4; i++) {
			long long A[2][2] = { 0 };
			A[0][0] = 1;
			A[0][1] = 1;
			A[1][0] = 1;
			long long** t1 = findAns(A, a[i]);
			fa[i] = t1[0][1] % M;
			/*
			fa = fibo(a , m);
			fb = fibo(b , m);
			fc = fibo(c , m);
			fd = fibo(d , m);
			*/
			/*
			fa = fibo(a % cir_index, m);
			fb = fibo(b % cir_index, m);
			fc = fibo(c % cir_index, m);
			fd = fibo(d % cir_index, m);
			*/
		}
		fa[0] = (fa[0] * fa[1]) % M;
		fa[2] = (fa[2] * fa[3]) % M;
		ans = (fa[0] + fa[2]) % M;

		fprintf(output_fp, "%d\n", ans);
		T--;
	}

	fclose(input_fp);
	fclose(output_fp);
	return 0;
	return 0;
}