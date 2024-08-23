#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX 100000

typedef struct _d {
	int x;
	int y;
	int num;
}Data;

int n;
char visited[100];
Data start, cs[100], end;

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
	Data data;
	Queue q;
	int x, y, num;
	data.x = start.x;
	data.y = start.y;
	data.num = start.num;
	Initqueue(&q);
	Enqueue(&q, data);

	while (q.f != q.r) {
		data = Peek(&q);
		Dequeue(&q);
		x = data.x;
		y = data.y;
		num = data.num;

		if (num != -1) {
			if (visited[num] == 1) {
				continue;
			}
			else {
				visited[num] = 1;
			}
		}

		if (abs(end.x - x) + abs(end.y - y) <= 1000) {
			return 1;
		}
		for (int i = 0; i < n; i++) {
			if (visited[cs[i].num] == 0) {
				if (abs(cs[i].x - x) + abs(cs[i].y - y) <= 1000) {
					Enqueue(&q, cs[i]);
				}
			}
		}
	}
	return -1;
}

int main() {
	int t, ret[50];
	scanf("%d", &t);
	for (int i = 0; i < t; i++) {
		memset(visited, 0, sizeof(char) * 101);
		scanf("%d", &n);
		scanf("%d %d", &start.x, &start.y);
		start.num = -1;
		for (int j = 0; j < n; j++) {
			scanf("%d %d", &cs[j].x, &cs[j].y);
			cs[j].num = j;
		}
		scanf("%d %d", &end.x, &end.y);
		end.num = -1;
		ret[i] = BFS();
	}
	for (int i = 0; i < t; i++) {
		if (ret[i] == 1) {
			printf("happy\n");
		}
		else if (ret[i] == -1) {
			printf("sad\n");
		}
	}
}