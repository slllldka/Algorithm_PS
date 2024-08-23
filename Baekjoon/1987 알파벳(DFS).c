#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max(a, b) (((a) > (b)) ? (a) : (b))

int R, C, m = 1;
char arr[20][21];
char v[20][20];
char alpha[26];

typedef struct _d {
	int r, c;
	int num;
}Data;

void DFS(Data start) {
	Data data;
	int r, c, num;
	r = start.r;
	c = start.c;
	num = start.num;

	if (m == 26 || m == R * C) {
		return;
	}

	if (v[r][c] == 1) {
		return;
	}
	else {
		v[r][c] = 1;
		alpha[arr[r][c] - 'A'] = 1;
	}
	
	if (num == R * C) {
		m = num;
		return;
	}

	//R 증가
	if ((r + 1 >= 0) && (r + 1 <= R - 1)) {
		if (v[r + 1][c] == 0) {
			data.r = r + 1;
			data.c = c;
			data.num = num + 1;
			if (alpha[arr[r + 1][c] - 'A'] == 1) {
				m = max(m, num);
				if ((m == 26) || (m == R * C)) {
					return;
				}
			}
			else{
				DFS(data);
			}
		}
	}
	//R 감소
	if ((r - 1 >= 0) && (r - 1 <= R - 1)) {
		if (v[r - 1][c] == 0) {
			data.r = r - 1;
			data.c = c;
			data.num = num + 1;
			if (alpha[arr[r - 1][c] - 'A'] == 1) {
				m = max(m, num);
				if ((m == 26) || (m == R * C)) {
					return;
				}
			}
			else {
				DFS(data);
			}
		}
	}
	//C 증가
	if ((c + 1 >= 0) && (c + 1 <= C - 1)) {
		if (v[r][c + 1] == 0) {
			data.r = r;
			data.c = c + 1;
			data.num = num + 1;
			if (alpha[arr[r][c + 1] - 'A'] == 1) {
				m = max(m, num);
				if ((m == 26) || (m == R * C)) {
					return;
				}
			}
			else {
				DFS(data);
			}
		}
	}
	//C 감소
	if ((c - 1 >= 0) && (c - 1 <= C - 1)) {
		if (v[r][c - 1] == 0) {
			data.r = r;
			data.c = c - 1;
			data.num = num + 1;
			if (alpha[arr[r][c - 1] - 'A'] == 1) {
				m = max(m, num);
				if ((m == 26) || (m == R * C)) {
					return;
				}
			}
			else {
				DFS(data);
			}
		}
	}
	v[r][c] = 0;
	alpha[arr[r][c] - 65] = 0;
}

int main() {
	Data start;
	scanf("%d %d", &R, &C);
	while (getchar() != '\n');
	for (int i = 0; i < R; i++) {
		fgets(arr[i], C + 1, stdin);
		while (getchar() != '\n');
	}
	start.r = 0;
	start.c = 0;
	start.num = 1;
	memset(alpha, 0, sizeof(arr));
	DFS(start);
	printf("%d", m);
	return 0;
}