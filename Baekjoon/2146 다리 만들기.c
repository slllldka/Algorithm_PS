#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100000

char v[100][100];
int N, set;
int arr[100][100], area[100][100], len[100][100];
int rd[4] = { 1, 0, -1, 0 };
int cd[4] = { 0, 1, 0, -1 };

typedef struct _d {
	int r, c, num, n;
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

void BFS1(int sr, int sc, int n, Queue* p) {
	Data data;
	Queue q;
	int r, c;
	data.r = sr;
	data.c = sc;
	Initqueue(&q);
	Enqueue(&q, data);
	while (q.f != q.r) {
		data = Peek(&q);
		Dequeue(&q);
		r = data.r;
		c = data.c;

		if (v[r][c] == 1) {
			continue;
		}
		else if (v[r][c] == 0) {
			v[r][c] = 1;
		}

		for (int i = 0; i < 4; i++) {
			data.r = r + rd[i];
			data.c = c + cd[i];
			if ((data.r >= 0) && (data.r < N) && (data.c >= 0) && (data.c < N)) {
				if (arr[data.r][data.c] == 1) {
					Enqueue(&q, data);
				}
				else if (arr[data.r][data.c] == 0) {
					if (v[data.r][data.c] == 0) {
						v[data.r][data.c] = 1;
						area[data.r][data.c] = n;
						len[data.r][data.c] = 1;
						data.num = 1;
						data.n = n;
						Enqueue(p, data);
					}
					else if (v[data.r][data.c] == 1) {
						if (area[data.r][data.c] != n) {
							set = -1;
							return;
						}
					}
				}
			}
		}
	}
}
int BFS2(Queue* p) {
	int r, c, num, n;
	Data data;
	while (p->f != p->r) {
		data = Peek(p);
		Dequeue(p);
		r = data.r;
		c = data.c;
		num = data.num;
		n = data.n;

		if ((len[r][c] != 1) && (v[r][c] == 1)) {
			continue;
		}
		else if ((len[r][c] != 1) && (v[r][c] == 0)) {
			v[r][c] = 1;
			len[r][c] = num;
			area[r][c] = n;
		}

		for (int i = 0; i < 4; i++) {
			data.r = r + rd[i];
			data.c = c + cd[i];
			data.num = num + 1;
			data.n = n;
			if ((data.r >= 0) && (data.r < N) && (data.c >= 0) && (data.c < N)) {
				if (arr[data.r][data.c] == 0) {
					if (v[data.r][data.c] == 1) {
						if (area[data.r][data.c] != n) {
							return len[data.r][data.c] + num;
						}
					}
					else if (v[data.r][data.c] == 0) {
						Enqueue(p, data);
					}
				}
			}
		}
	}
}

int main() {
	int count = 0, ret;
	Queue queue;
	Initqueue(&queue);
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &arr[i][j]);
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if ((arr[i][j] == 1) && (v[i][j] == 0)) {
				BFS1(i, j, count, &queue);
				if (set == -1) {
					printf("1");
					return 0;
				}
				count++;
			}
		}
	}

	ret = BFS2(&queue);
	printf("%d", ret);
	return 0;
}