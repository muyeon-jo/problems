#include <stdio.h>
#include <stdlib.h>
#include <string.h>
FILE* input_fp = fopen("bitmap.inp", "rt");
FILE* output_fp = fopen("bitmap.out", "wt");
int count = 0;

void compress(int start_x, int start_y, int end_x, int end_y, char** arr) {
	int one = 1;
	int zero = 1;
	int D = 0;
	if (end_x == start_x || end_y == start_y)
		return;
	for (int i = start_y; i < end_y; i++) {
		for (int j = start_x; j < end_x; j++) {
			if (arr[i][j] == '1') {
				zero = 0;
			}
			else {
				one = 0;
			}

			if (one == 0 && zero == 0) {
				D = 1;
				break;
			}
		}
	}
	int odd_x = 0, odd_y = 0;
	if ((start_x + end_x) % 2) {
		odd_x = 1;
	}
	if ((start_y + end_y) % 2) {
		odd_y = 1;
	}

	if (zero) {
		fprintf(output_fp, "0");
		count++;
	}
	else if (one) {
		fprintf(output_fp, "1");
		count++;
	}
	else {
		char p[4] = { '\0' };
		fprintf(output_fp, "D");
		count++;
		if (count >= 50) {
			fprintf(output_fp, "\n");
			count = 0;
		}
		compress(start_x, start_y, (start_x + end_x) / 2 + odd_x, (start_y + end_y) / 2 + odd_y, arr);
		compress((start_x + end_x) / 2 + odd_x, start_y, end_x, (start_y + end_y) / 2 + odd_y, arr);
		compress(start_x, (start_y + end_y) / 2+odd_y, (start_x + end_x) / 2 + odd_x, end_y, arr);
		compress((start_x + end_x) / 2+odd_x, (start_y + end_y) / 2+odd_y, end_x, end_y, arr);
	}

	if (count >= 50) {
		fprintf(output_fp, "\n");
		count = 0;
	}
}
void decompress(int start_x, int start_y, int end_x, int end_y, char** arr) {
	char temp;
	if (end_x == start_x || end_y == start_y)
		return;

	do {
		fscanf(input_fp, "%c", &temp);
	} while (temp == '\n');
	int odd_x = 0, odd_y = 0;
	if ((start_x + end_x) % 2) {
		odd_x = 1;
	}
	if ((start_y + end_y) % 2) {
		odd_y = 1;
	}
	if (temp == '0') {
		for (int i = start_y; i < end_y; i++) {
			for (int j = start_x; j < end_x; j++) {
				arr[i][j] = '0';
			}
		}
	}
	else if (temp == '1') {
		for (int i = start_y; i < end_y; i++) {
			for (int j = start_x; j < end_x; j++) {
				arr[i][j] = '1';
			}
		}
	}
	else {

		decompress(start_x, start_y, (start_x + end_x) / 2 + odd_x, (start_y + end_y) / 2 + odd_y, arr);
		decompress((start_x + end_x) / 2 + odd_x, start_y, end_x, (start_y + end_y) / 2 + odd_y, arr);
		decompress(start_x, (start_y + end_y) / 2 + odd_y, (start_x + end_x) / 2 + odd_x, end_y, arr);
		decompress((start_x + end_x) / 2 + odd_x, (start_y + end_y) / 2 + odd_y, end_x, end_y, arr);
	}
}
int main() {
	char type = '\0';
	int x, y;
	while (1) {
		count = 0;
		do {
			fscanf(input_fp, "%c", &type);
		} while (type == '\n');
		if (type == '#') {
			break;
		}
		fscanf(input_fp, "%d %d", &y, &x);
		if (type == 'B') {
			char** arr = (char**)malloc(sizeof(char*) * y);
			for (int i = 0; i < y; i++) {
				arr[i] = (char*)malloc(x);
			}
			for (int i = 0; i < y; i++) {
				for (int j = 0; j < x; j++) {
					do {
						fscanf(input_fp, "%c", &arr[i][j]);
					} while (arr[i][j] == '\n');
				}
			}
			fprintf(output_fp, "D %d %d\n", y, x);
			compress(0, 0, x, y, arr);
			
			
		}
		else {
			char** arr = (char**)malloc(sizeof(char*) * y);
			for (int i = 0; i < y; i++) {
				arr[i] = (char*)malloc(x);
			}
			for (int i = 0; i < y; i++) {
				for (int j = 0; j < x; j++) {
					arr[i][j] = '\0';
				}
			}
			fprintf(output_fp, "B %d %d\n", y, x);
			decompress(0, 0, x, y, arr);
			
			for (int i = 0; i < y; i++) {
				for (int j = 0; j < x; j++) {
					fprintf(output_fp, "%c", arr[i][j]);
					count++;
					if (count >= 50) {
						count = 0;
						fprintf(output_fp, "\n");
					}
				}
			}
		}
		if(count > 0)
			fprintf(output_fp, "\n");

	}

	fclose(input_fp);
	fclose(output_fp);
	return 0;
}