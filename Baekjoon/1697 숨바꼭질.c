#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 200000

int N, K;
char* v;

typedef struct _data {
	int n;
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
	Queue q;
	Data data;
	int n, num, ret = 0;
	Initqueue(&q);
	data.n = N;
	data.num = 0;
	Enqueue(&q, data);

	while (q.f != q.r) {
		data = Peek(&q);
		n = data.n;
		num = data.num;
		Dequeue(&q);

		if (n == K) {
			ret = num;
			break;
		}

		if (v[n] == 1) {
			continue;
		}
		else {
			v[n] = 1;
		}

		//X-1
		if (n - 1 == K) {
			ret = num + 1;
			break;
		}
		else if ((n - 1 >= 0) && (n - 1 <= 100000)) {
			if (v[n - 1] == 0) {
				data.n = n - 1;
				data.num = num + 1;
				Enqueue(&q, data);
			}
		
		}
		//X+1
		if (n + 1 == K) {
			ret = num + 1;
			break;
		}
		else if ((n + 1 >= 0) && (n + 1 <= 100000)) {
			if (v[n + 1] == 0) {
				data.n = n + 1;
				data.num = num + 1;
				Enqueue(&q, data);
			}
		}
		//2X
		if (2 * n == K) {
			ret = num + 1;
			break;
		}
		else if ((2 * n >= 0) && (2 * n <= 100000)) {
			if (v[2 * n] == 0) {
				data.n = 2 * n;
				data.num = num + 1;
				Enqueue(&q, data);
			}
		}
	}
	return ret;
}

int main() {
	int ret;
	scanf("%d %d", &N, &K);
	v = (char*)malloc(sizeof(char) * MAX);
	memset(v, 0, sizeof(char) * MAX);
	ret = BFS();
	printf("%d", ret);

	free(v);
	return 0;
}