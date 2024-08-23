#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 50000

char visited[100][100];
int R, C, arr[100][100];
int rd[4] = { 1, 0, -1, 0 };
int cd[4] = { 0, 1, 0, -1 };

typedef struct _d {
	int r, c;
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

int Do() {
	int r, c, ret = 0;
	Queue q, cheese;
	Data data;
	Initqueue(&q);
	Initqueue(&cheese);
	data.r = data.c = 0;
	Enqueue(&q, data);
	memset(visited, 0, sizeof(visited));

	while (q.f != q.r) {
		data = Peek(&q);
		Dequeue(&q);
		r = data.r;
		c = data.c;

		if (visited[r][c] == 1) {
			continue;
		}
		else {
			visited[r][c] = 1;
		}

		for (int i = 0; i < 4; i++) {
			data.r = r + rd[i];
			data.c = c + cd[i];
			if (data.r >= 0 && data.r < R && data.c >= 0 && data.c < C) {
				if (arr[data.r][data.c] == 0) {
					Enqueue(&q, data);
				}
				else if (arr[data.r][data.c] == 1) {
					visited[data.r][data.c] = 1;
					Enqueue(&cheese, data);
				}
			}
		}
	}
	while (cheese.f != cheese.r) {
		data = Peek(&cheese);
		Dequeue(&cheese);
		if (arr[data.r][data.c] == 1) {
			arr[data.r][data.c] = 0;
			ret++;
		}
	}
	return ret;
}

int main() {
	int total = 0, time = 0, output;
	scanf("%d %d", &R, &C);
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			scanf("%d", &arr[i][j]);
			if (arr[i][j] == 1) {
				total++;
			}
		}
	}

	while (1) {
		output = total;
		total -= Do();
		time++;
		if (total == 0) {
			break;
		}
	}
	printf("%d\n%d", time, output);
	return 0;
}