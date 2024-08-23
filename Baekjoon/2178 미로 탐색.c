#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define min(a, b) (((a) < (b)) ? (a) : (b))
#define MAX 20000

int N, M;
char arr[101][101];
char v[100][100];

typedef struct _data {
	int n;
	int m;
	int day;
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

int BFS(Data start) {
	int n, m, day;
	Data data;
	Queue q;
	Initqueue(&q);
	Enqueue(&q, start);

	while (q.f != q.r) {
		data = Peek(&q);
		Dequeue(&q);
		n = data.n;
		m = data.m;
		day = data.day;
		if ((n == N - 1) && (m == M - 1)) {
			return day;
		}
		if (v[n][m] == 1) {
			continue;
		}
		else {
			v[n][m] = 1;
		}

		if ((n + 1 >= 0) && (n + 1 < N)) {
			data.day = day + 1;
			data.n = n + 1;
			data.m = m;
			if (v[data.n][data.m] == 0) {
				if (arr[data.n][data.m] == '1') {
					Enqueue(&q, data);
				}
			}
		}
		if ((n - 1 >= 0) && (n - 1 < N)) {
			data.day = day + 1;
			data.n = n - 1;
			data.m = m;
			if (v[data.n][data.m] == 0) {
				if (arr[data.n][data.m] == '1') {
					Enqueue(&q, data);
				}
			}
		}
		if ((m + 1 >= 0) && (m + 1 < M)) {
			data.day = day + 1;
			data.n = n;
			data.m = m + 1;
			if (v[data.n][data.m] == 0) {
				if (arr[data.n][data.m] == '1') {
					Enqueue(&q, data);
				}
			}
		}
		if ((m - 1 >= 0) && (m - 1 < M)) {
			data.day = day + 1;
			data.n = n;
			data.m = m - 1;
			if (v[data.n][data.m] == 0) {
				if (arr[data.n][data.m] == '1') {
					Enqueue(&q, data);
				}
			}
		}
	}
}

int main() {
	Data start;
	int shortest;
	scanf("%d %d", &N, &M);
	getchar();

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			v[i][j] = 0;
		}
	}

	for (int i = 0; i < N; i++) {
		fgets(arr[i], 101, stdin);
		if (strlen(arr[i]) == 100) {
			while (getchar() != '\n');
		}
	}

	start.day = 1;
	start.n = 0;
	start.m = 0;
	shortest = BFS(start);
	printf("%d", shortest);
	return 0;
}