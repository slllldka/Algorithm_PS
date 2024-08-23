#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max(a, b) (((a) > (b)) ? (a) : (b))
#define MAX 3000000

int M, N, H;
int arr[100][100][100];

typedef struct _data {
	int m;
	int n;
	int h;
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

void BFS() {
	Queue q;
	Data data;
	int h, n, m, day, ret = 0;
	char v[100][100][100];

	Initqueue(&q);
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < N; j++) {
			for (int k = 0; k < M; k++) {
				v[i][j][k] = 0;
				if (arr[i][j][k] == 1) {
					data.day = 0;
					data.h = i;
					data.n = j;
					data.m = k;
					Enqueue(&q, data);
				}
			}
		}
	}

	while (q.f != q.r) {
		data = Peek(&q);
		Dequeue(&q);
		h = data.h;
		n = data.n;
		m = data.m;
		day = data.day;

		if (v[h][n][m] == 1) {
			continue;
		}
		else {
			v[h][n][m] = 1;
			ret = max(ret, day);
			if (arr[h][n][m] == -1) {
				continue;
			}
		}
		
		if ((h + 1 >= 0) && (h + 1 < H)) {
			data.h = h + 1;
			data.n = n;
			data.m = m;
			if (v[data.h][data.n][data.m] == 0) {
				if (arr[data.h][data.n][data.m] == 0) {
					arr[data.h][data.n][data.m] = 1;
					data.day = day + 1;
				}
				else if (arr[data.h][data.n][data.m] == -1) {
					data.day = day;
				}
				Enqueue(&q, data);
			}
		}
		if ((h - 1 >= 0) && (h - 1 < H)) {
			data.h = h - 1;
			data.n = n;
			data.m = m;
			if (v[data.h][data.n][data.m] == 0) {
				if (arr[data.h][data.n][data.m] == 0) {
					arr[data.h][data.n][data.m] = 1;
					data.day = day + 1;
				}
				else if (arr[data.h][data.n][data.m] == -1) {
					data.day = day;
				}
				Enqueue(&q, data);
			}
		}
		if ((n + 1 >= 0) && (n + 1 < N)) {
			data.h = h;
			data.n = n + 1;
			data.m = m;
			if (v[data.h][data.n][data.m] == 0) {
				if (arr[data.h][data.n][data.m] == 0) {
					arr[data.h][data.n][data.m] = 1;
					data.day = day + 1;
				}
				else if (arr[data.h][data.n][data.m] == -1) {
					data.day = day;
				}
				Enqueue(&q, data);
			}
		}
		if ((n - 1 >= 0) && (n - 1 < N)) {
			data.h = h;
			data.n = n - 1;
			data.m = m;
			if (v[data.h][data.n][data.m] == 0) {
				if (arr[data.h][data.n][data.m] == 0) {
					arr[data.h][data.n][data.m] = 1;
					data.day = day + 1;
				}
				else if (arr[data.h][data.n][data.m] == -1) {
					data.day = day;
				}
				Enqueue(&q, data);
			}
		}
		if ((m + 1 >= 0) && (m + 1 < M)) {
			data.h = h;
			data.n = n;
			data.m = m + 1;
			if (v[data.h][data.n][data.m] == 0) {
				if (arr[data.h][data.n][data.m] == 0) {
					arr[data.h][data.n][data.m] = 1;
					data.day = day + 1;
				}
				else if (arr[data.h][data.n][data.m] == -1) {
					data.day = day;
				}
				Enqueue(&q, data);
			}
		}
		if ((m - 1 >= 0) && (m - 1 < M)) {
			data.h = h;
			data.n = n;
			data.m = m - 1;
			if (v[data.h][data.n][data.m] == 0) {
				if (arr[data.h][data.n][data.m] == 0) {
					arr[data.h][data.n][data.m] = 1;
					data.day = day + 1;
				}
				else if (arr[data.h][data.n][data.m] == -1) {
					data.day = day;
				}
				Enqueue(&q, data);
			}
		}
	}

	for (int i = 0; i < H; i++) {
		for (int j = 0; j < N; j++) {
			for (int k = 0; k < M; k++) {
				if (arr[i][j][k] == 0) {
					printf("-1");
					free(q.data);
					return;
				}
			}
		}
	}
	free(q.data);
	printf("%d", ret);
	return;
}

int main() {
	scanf("%d %d %d", &M, &N, &H);
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < N; j++) {
			for (int k = 0; k < M; k++) {
				scanf("%d", &arr[i][j][k]);
			}
		}
	}
	BFS();
	return 0;
}