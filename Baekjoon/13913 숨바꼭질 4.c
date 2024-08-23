#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX 100000

char visited[100001];
int arr[100001];

typedef struct _d {
	int t, prev, now;
}Data;

typedef struct _q {
	int f, r;
	Data data[MAX];
}Queue;

void Initqueue(Queue* p) {
	p->f = p->r = 0;
}
void Enqueue(Queue* p, Data item) {
	if (p->f == (p->r + 1) % MAX) {
		exit(1);
	}
	p->data[p->r] = item;
	p->r = (p->r + 1) % MAX;
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
	p->f = (p->f + 1) % MAX;
}

int BFS(int start, int end) {
	Queue q;
	Data data;
	int t, prev, now;
	Initqueue(&q);
	data.t = 0;
	data.prev = start;
	data.now = start;
	Enqueue(&q, data);

	while (q.f != q.r) {
		data = Peek(&q);
		Dequeue(&q);
		t = data.t;
		prev = data.prev;
		now = data.now;

		if (visited[now] == 1) {
			continue;
		}
		visited[now] = 1;
		arr[now] = prev;
		if (now == end) {
			return t;
		}

		data.t++;
		data.prev = now;
		for (int i = 0; i < 3; i++) {
			if (i == 0) {
				data.now = now + 1;
			}
			else if (i == 1) {
				data.now = now - 1;
			}
			else if (i == 2) {
				data.now = 2 * now;
			}
			
			if (data.now >= 0 && data.now <= 100000) {
				if (visited[data.now] == 0) {
					Enqueue(&q, data);
				}
			}
		}
	}
}

int main() {
	int N, K, time, next, * output;
	scanf("%d %d", &N, &K);
	time = BFS(N, K);
	printf("%d\n", time);
	output = (int*)malloc(sizeof(int) * (time + 1));
	output[time] = K;
	next = arr[K];
	for (int i = time - 1; i >= 0; i--) {
		output[i] = next;
		if (next != -1) {
			next = arr[next];
		}
	}

	for (int i = 0; i <= time; i++) {
		printf("%d ", output[i]);
	}
	free(output);
	return 0;
}