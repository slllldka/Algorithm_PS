#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main() {
	int N, M, count, dif, i, j, k, l;
	char A[52][52];
	char B[52][52];
	scanf("%d %d", &N, &M);
	while (getchar() != '\n');
	for (i = 0; i < N; i++) {
		fgets(A[i], M + 2, stdin);
	}
	for (i = 0; i < N; i++) {
		fgets(B[i], M + 2, stdin);
	}

	count = 0;
	for (i = 0; i < N - 2; i++) {
		for (j = 0; j < M - 2; j++) {
			if (A[i][j] != B[i][j]) {
				for (k = 0; k < 3; k++) {
					for (l = 0; l < 3; l++) {
						if (A[k + i][l + j] == '0') {
							A[k + i][l + j] = '1';
						}
						else {
							A[k + i][l + j] = '0';
						}
					}
				}
				count++;
			}
		}
	}

	dif = 0;
	for (i = 0; i < N; i++) {
		for (j = 0; j < M; j++) {
			if (A[i][j] != B[i][j]) {
				dif = 1;
				break;
			}
		}
	}

	if (dif == 0) {
		printf("%d", count);
	}
	else if (dif == 1) {
		printf("-1");
	}

	return 0;
}