#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define min(a, b) (((a) < (b)) ? (a) : (b))

#define MAX 1000000

char v[100001];
int N, K, arr[100001];
int Min;

typedef struct _d {
	int p, num;
}Data;

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

void BFS() {
	int p, num;
	Data data;
	data.p = N;
	data.num = 0;
	Initqueue(&q);
	Enqueue(&q, data);
	Min = 1000000;

	while (q.f != q.r) {
		data = Peek(&q);
		Dequeue(&q);
		p = data.p;
		num = data.num;

		if (num >= Min) {
			continue;
		}
		if (v[p] == 1) {
			if (num >= arr[p]) {
				continue;
			}
			else {
				arr[p] = num;
			}
		}
		else if (v[p] == 0) {
			v[p] = 1;
			arr[p] = num;
		}

		data.p = p - 1;
		data.num = num + 1;
		if ((data.p >= 0) && (data.p <= 100000)) {
			if (data.p == K) {
				Min = min(Min, data.num);
			}
			else if (data.num < Min) {
				if (v[data.p] == 1) {
					if (data.num < arr[data.p]) {
						Enqueue(&q, data);
					}
				}
				else if (v[data.p] == 0) {
					Enqueue(&q, data);
				}
			}
		}

		data.p = p + 1;
		data.num = num + 1;
		if ((data.p >= 0) && (data.p <= 100000)) {
			if (data.p == K) {
				Min = min(Min, data.num);
			}
			else if (data.num < Min) {
				if (v[data.p] == 1) {
					if (data.num < arr[data.p]) {
						Enqueue(&q, data);
					}
				}
				else if (v[data.p] == 0) {
					Enqueue(&q, data);
				}
			}
		}

		data.p = p * 2;
		data.num = num;
		if ((data.p >= 0) && (data.p <= 100000)) {
			if (data.p == K) {
				Min = min(Min, data.num);
			}
			else if (data.num < Min) {
				if (v[data.p] == 1) {
					if (data.num < arr[data.p]) {
						Enqueue(&q, data);
					}
				}
				else if (v[data.p] == 0) {
					Enqueue(&q, data);
				}
			}
		}
	}
}

int main() {
	scanf("%d %d", &N, &K);
	if (N == K) {
		printf("0");
		return 0;
	}
	BFS();
	printf("%d", Min);
	return 0;
}