#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000000

char visited[300][300];
int l, tr, tc;
int rd[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };
int cd[8] = { 2, 1, -1, -2, -2, -1, 1, 2 };

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

int BFS(int sr, int sc) {
	int r, c, num;
	Queue q;
	Data data;
	Initqueue(&q);
	data.r = sr;
	data.c = sc;
	data.num = 0;
	Enqueue(&q, data);

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
		}

		data.num = num + 1;
		for (int i = 0; i < 8; i++) {
			data.r = r + rd[i];
			data.c = c + cd[i];
			if ((data.r >= 0) && (data.r < l) && (data.c >= 0) && (data.c < l)) {
				if (visited[data.r][data.c] == 0) {
					if ((data.r == tr) && (data.c == tc)) {
						return data.num;
					}
					else {
						Enqueue(&q, data);
					}
				}
			}
		}
	}
}

int main() {
	int T, * output, sr, sc;
	scanf("%d", &T);
	output = (int*)malloc(sizeof(int) * T);
	for (int i = 0; i < T; i++) {
		scanf("%d", &l);
		scanf("%d %d", &sr, &sc);
		scanf("%d %d", &tr, &tc);
		memset(visited, 0, sizeof(char) * 90000);
		if ((sr == tr) && (sc == tc)) {
			output[i] = 0;
		}
		else {
			output[i] = BFS(sr, sc);
		}
	}

	for (int i = 0; i < T; i++) {
		printf("%d\n", output[i]);
	}
	free(output);
	return 0;
}