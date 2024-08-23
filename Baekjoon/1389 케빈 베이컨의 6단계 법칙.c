#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000
#define min(a, b) (((a) < (b)) ? (a) : (b))

char visited[101];
int N, M, arr[101][101], each[101][101], sum[101];

typedef struct _d {
	int idx;
	int num;
}Data;

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

void BFS(int start, int target) {
	int idx, num;
	Queue q;
	Data data;
	memset(visited, 0, sizeof(char) * 101);
	Initqueue(&q);
	data.idx = start;
	data.num = 0;
	Enqueue(&q, data);
	while (q.f != q.r) {
		data = Peek(&q);
		Dequeue(&q);
		idx = data.idx;
		num = data.num;

		if (idx == target) {
			each[start][target] = num;
			return;
		}

		if (visited[idx] == 1) {
			continue;
		}
		else if (visited[idx] == 0) {
			visited[idx] = 1;
		}

		data.num = num + 1;
		for (int i = 1; i <= N; i++) {
			if (idx != i) {
				if (arr[idx][i] == 1) {
					if (visited[i] == 0) {
						data.idx = i;
						Enqueue(&q, data);
					}
				}
			}
		}
	}
}

int main() {
	int s, e, output, Min = 100000;
	scanf("%d %d", &N, &M);
	for (int i = 0; i < M; i++) {
		scanf("%d %d", &s, &e);
		arr[s][e] = 1;
		arr[e][s] = 1;
	}

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (i != j) {
				if (each[j][i] > 0) {
					each[i][j] = each[j][i];
				}
				else if (each[j][i] == 0) {
					BFS(i, j);
				}
				sum[i] += each[i][j];
			}
		}
	}

	for (int i = 1; i <= N; i++) {
		if (sum[i] < Min) {
			Min = sum[i];
			output = i;
		}
	}
	printf("%d", output);
	return 0;
}