#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 2000000

int* visited;
int F, S, G, U, D;
int ret = -1;

typedef struct _d {
	int floor;
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
void BFS() {
	Data data;
	Queue q;
	int floor, num;
	data.floor = S;
	data.num = 0;
	Initqueue(&q);
	Enqueue(&q, data);
	for (int i = 0; i < F; i++) {
		visited[i] = -1;
	}

	while (q.f != q.r) {
		data = Peek(&q);
		Dequeue(&q);
		floor = data.floor;
		num = data.num;

		if (visited[floor] != -1) {
			if (num >= visited[floor]) {
				continue;
			}
		}
		else {
			visited[floor] = num;
		}

		//Up
		if ((floor + U >= 0) && (floor + U < F)) {
			if ((visited[floor + U] == -1) || (visited[floor + U] > num + 1)) {
				if (floor + U == G) {
					ret = num + 1;
					return;
				}
				data.floor = floor + U;
				data.num = num + 1;
				Enqueue(&q, data);
			}
		}
		//Down
		if ((floor - D >= 0) && (floor - D < F)) {
			if ((visited[floor - D] == -1) || (visited[floor - D] > num + 1)) {
				if (floor - D == G) {
					ret = num + 1;
					return;
				}
				data.floor = floor - D;
				data.num = num + 1;
				Enqueue(&q, data);
			}
		}
	}
}

int main() {
	scanf("%d %d %d %d %d", &F, &S, &G, &U, &D);
	visited = (int*)malloc(sizeof(int) * F);
	S--;
	G--;
	if (S == G) {
		ret = 0;
	}
	else {
		BFS();
	}
	if (ret == -1) {
		printf("use the stairs");
	}
	else {
		printf("%d", ret);
	}
	free(visited);
	return 0;
}