#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 2000000

int N, M;
char nd[4] = { 1, 0, -1, 0 };
char md[4] = { 0, 1, 0, -1 };
char** arr;
char** v0;
char** v1;

typedef struct _d{
	char b;
	int n, m;
	int num;
}Data;

typedef struct _q {
	int f, r;
	Data* data;
}Queue;

void Initqueue(Queue* p) {
	p->f = 0;
	p->r = 0;
	p->data = (Data*)malloc(sizeof(Data) * MAX);
}
void Enqueue(Queue* p, Data item) {
	if (p->f == (p->r + 1) % MAX) {
		exit(1);
	}
	p->data[p->r] = item;
	(p->r)++;
}
Data Peek(Queue* p) {
	if (p->f == p->r) {
		exit(1);
	}
	return p->data[p->f];
}
void Dequeue(Queue* p) {
	if (p->f == p->r) {
		exit(1);
	}
	(p->f)++;
}

int BFS() {
	Data data;
	char b;
	int n, m, num, ret = -1;
	Queue q;

	data.b = 0;
	data.n = 0;
	data.m = 0;
	data.num = 1;
	Initqueue(&q);
	Enqueue(&q, data);

	while (q.f != q.r) {
		data = Peek(&q);
		Dequeue(&q);
		b = data.b;
		n = data.n;
		m = data.m;
		num = data.num;

		if ((n == N - 1) && (m == M - 1)) {
			return num;
		}

		if (b == 0) {
			if (v0[n][m] == 1) {
				continue;
			}
			else {
				v0[n][m] = 1;
			}
		}
		else if (b == 1) {
			if (v1[n][m] == 1) {
				continue;
			}
			else {
				v1[n][m] = 1;
			}
		}

		if (b == 1) {
			for (int i = 0; i < 4; i++) {
				data.b = 1;
				data.n = n + nd[i];
				data.m = m + md[i];
				data.num = num + 1;
				if ((data.n >= 0) && (data.n <= N - 1) && (data.m >= 0) && (data.m <= M - 1)) {
					if ((arr[data.n][data.m] == '0') && (v1[data.n][data.m] == 0)) {
						if ((data.n == N - 1) && (data.m == M - 1)) {
							return data.num;
						}
						else {
							Enqueue(&q, data);
						}
					}
				}
			}
		}
		else {
			for (int i = 0; i < 4; i++) {
				data.b = 0;
				data.n = n + nd[i];
				data.m = m + md[i];
				data.num = num + 1;
				if ((data.n >= 0) && (data.n <= N - 1) && (data.m >= 0) && (data.m <= M - 1)) {
					if (arr[data.n][data.m] == '0') {
						if (v0[data.n][data.m] == 0) {
							if ((data.n == N - 1) && (data.m == M - 1)) {
								return data.num;
							}
							else {
								Enqueue(&q, data);
							}
						}
					}
					else if (arr[data.n][data.m] == '1') {
						if (v1[data.n][data.m] == 0) {
							if ((data.n == N - 1) && (data.m == M - 1)) {
								return data.num;
							}
							else {
								data.b = 1;
								Enqueue(&q, data);
							}
						}
					}
				}
			}
		}
	}

	return ret;
}

int main() {
	int ret;
	scanf("%d %d", &N, &M);
	while (getchar() != '\n');
	arr = (char**)malloc(sizeof(char*) * N);
	v0 = (char**)malloc(sizeof(char*) * N);
	v1 = (char**)malloc(sizeof(char*) * N);
	for (int i = 0; i < N; i++) {
		arr[i] = (char*)malloc(sizeof(char) * (M + 1));
		fgets(arr[i], M + 1, stdin);
		while (getchar() != '\n');
		v0[i] = (char*)malloc(sizeof(char) * M);
		memset(v0[i], 0, sizeof(v0[i]));
		v1[i] = (char*)malloc(sizeof(char) * M);
		memset(v1[i], 0, sizeof(v1[i]));
	}

	ret = BFS();
	printf("%d", ret);
	return 0;
}