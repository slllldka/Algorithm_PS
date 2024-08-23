#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10000
#define max(a, b) (((a) > (b)) ? (a) : (b))

char arr[52][52], visited[50][50];
int R, C, Max = 0;
int rd[4] = { 1, 0, -1, 0 };
int cd[4] = { 0, 1, 0, -1 };

typedef struct _d {
	int r, c, num;
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

void BFS(int sr, int sc) {
	int r, c, num;
	Queue q;
	Data data;
	Initqueue(&q);
	data.r = sr;
	data.c = sc;
	data.num = 0;
	Enqueue(&q, data);
	memset(visited, 0, sizeof(char) * 50 * 50);

	while (q.f != q.r) {
		data = Peek(&q);
		Dequeue(&q);
		r = data.r;
		c = data.c;
		num = data.num;
		if (visited[r][c] == 1) {
			continue;
		}
		else if (visited[r][c] == 0) {
			visited[r][c] = 1;
			Max = max(Max, num);
		}

		data.num = num + 1;
		for (int i = 0; i < 4; i++) {
			data.r = r + rd[i];
			data.c = c + cd[i];
			if ((data.r >= 0) && (data.r < R) && (data.c >= 0) && (data.c < C)) {
				if (visited[data.r][data.c] == 0) {
					if (arr[data.r][data.c] == 'L') {
						Enqueue(&q, data);
					}
				}
			}
		}
	}
}

int main() {
	scanf("%d %d", &R, &C);
	while (getchar() != '\n');
	for (int i = 0; i < R; i++) {
		fgets(arr[i], 52, stdin);
	}

	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			if (arr[i][j] == 'L') {
				BFS(i, j);
			}
		}
	}
	printf("%d", Max);
	return 0;
}