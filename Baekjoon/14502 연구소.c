#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 500
#define max(a, b) (((a) > (b)) ? (a) : (b))

char visited[8][8];
int N, M, vir, wall, arr[8][8];
int rd[4] = { 1, 0, -1, 0 };
int cd[4] = { 0 ,1 ,0, -1 };

typedef struct _d {
	int r, c;
}Data;

Data start[10];

typedef struct _q {
	int f, r;
	Data data[MAX];
}Queue;

void Initqueue(Queue* p) {
	p->f = 0;
	p->r = 0;
}
void Enqueue(Queue* p, Data item) {
	if (p->f == (p->r + 1) % MAX) {
		exit(1);
	}
	p->data[p->r] = item;
	(p->r)++;
}
void Dequeue(Queue* p) {
	if (p->f == p->r) {
		exit(1);
	}
	(p->f)++;
}
Data Peek(Queue* p) {
	if (p->f == p->r) {
		exit(1);
	}
	return p->data[p->f];
}

int BFS() {
	Queue q;
	Data data;
	int r, c, ret = 0;

	Initqueue(&q);
	for (int i = 0; i < vir; i++) {
		Enqueue(&q, start[i]);
	}

	while (q.f != q.r) {
		data = Peek(&q);
		Dequeue(&q);
		r = data.r;
		c = data.c;

		if (visited[r][c] == 1) {
			continue;
		}
		else if (visited[r][c] == 0) {
			ret++;
			visited[r][c] = 1;
		}

		for (int i = 0; i < 4; i++) {
			data.r = r + rd[i];
			data.c = c + cd[i];
			if ((data.r >= 0) && (data.r < N) && (data.c >= 0) && (data.c < M)) {
				if ((arr[data.r][data.c] == 0) && (visited[data.r][data.c] == 0)) {
					Enqueue(&q, data);
				}
			}
		}
	}
	return (N * M - ret - wall - 3);
}

int main() {
	int num = 0, Max = 0, ret = 0;
	vir = 0;
	wall = 0;
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%d", &arr[i][j]);
			if (arr[i][j] == 2) {
				start[vir].r = i;
				start[vir].c = j;
				vir++;
			}
			else if (arr[i][j] == 1) {
				wall++;
			}
		}
	}

	for (int i = 0; i < N * M - 2; i++) {
		if (arr[i / M][i % M] == 0) {
			arr[i / M][i % M] = 1;
			for (int j = i + 1; j < N * M - 1; j++) {
				if (arr[j / M][j % M] == 0) {
					arr[j / M][j % M] = 1;
					for (int k = j + 1; k < N * M; k++) {
						if (arr[k / M][k % M] == 0) {
							arr[k / M][k % M] = 1;
							memset(visited, 0, sizeof(char) * 64);
							ret = BFS();
							Max = max(Max, ret);
							arr[k / M][k % M] = 0;
						}
					}
					arr[j / M][j % M] = 0;
				}
			}
			arr[i / M][i % M] = 0;
		}
	}

	printf("%d", Max);
	return 0;
}