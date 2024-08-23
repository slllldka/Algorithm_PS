#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100000

char v[201];
int N, M, path[1000], arr[201][201];

typedef int Data;

typedef struct _q {
	int f, r;
	Data data[MAX];
}Queue;

Queue q;

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

int BFS(int start, int idx) {
	int p;
	Initqueue(&q);
	Enqueue(&q, start);

	while (q.f != q.r) {
		p = Peek(&q);
		Dequeue(&q);

		if (v[p] == 1) {
			continue;
		}
		else if (v[p] == 0) {
			v[p] = 1;
		}

		for (int i = 1; i <= N; i++) {
			if (arr[p][i] == 1) {
				if (v[i] == 0) {
					if (i == path[idx]) {
						return 1;
					}
					Enqueue(&q, i);
				}
			}
		}
	}

	return -1;
}

int main() {
	int ret;
	scanf("%d", &N);
	scanf("%d", &M);
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			scanf("%d", &arr[i][j]);
		}
	}
	for (int i = 0; i < M; i++) {
		scanf("%d", path + i);
	}

	if (M == 1) {
		printf("YES");
		return 0;
	}

	for (int i = 0; i < M - 1; i++) {
		memset(v, 0, sizeof(v));
		if (path[i] == path[i + 1]) {
			ret = 1;
		}
		else {
			ret = BFS(path[i], i + 1);
		}
		if (ret == -1) {
			printf("NO");
			return 0;
		}
	}
	printf("YES");
	return 0;
}