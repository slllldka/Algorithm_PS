#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX 10000

int R, C;
int rd[4] = { 1, 0, -1, 0 };
int cd[4] = { 0, 1, 0, -1 };
char arr[50][51];
char vh[50][50], vw[50][50];

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

int BFS(Queue* water, Data start) {
	Queue q;
	Data wdata;
	Data hdata;
	int r, c, num;

	Initqueue(&q);
	Enqueue(&q, start);

	while (q.f != q.r) {
		hdata = Peek(&q);
		Dequeue(&q);
		while (water->f != water->r) {
			wdata = Peek(water);
			if (wdata.num == hdata.num) {
				Dequeue(water);
				r = wdata.r;
				c = wdata.c;
				num = wdata.num;

				if (vw[r][c] == 1) {
					continue;
				}
				else if (vw[r][c] == 0) {
					vw[r][c] = 1;
				}

				for (int i = 0; i < 4; i++) {
					wdata.r = r + rd[i];
					wdata.c = c + cd[i];
					wdata.num = num + 1;
					if ((wdata.r >= 0) && (wdata.r < R) && (wdata.c >= 0) && (wdata.c < C)) {
						if ((arr[wdata.r][wdata.c] == '.') && (vw[wdata.r][wdata.c] == 0)) {
							arr[wdata.r][wdata.c] = '*';
							Enqueue(water, wdata);
						}
					}
				}
			}
			else if (wdata.num == (hdata.num + 1)){
				break;
			}
		}
		r = hdata.r;
		c = hdata.c;
		num = hdata.num;

		if (vh[r][c] == 1) {
			continue;
		}
		else if (vh[r][c] == 0) {
			vh[r][c] = 1;
		}

		for (int i = 0; i < 4; i++) {
			hdata.r = r + rd[i];
			hdata.c = c + cd[i];
			hdata.num = num + 1;
			if ((hdata.r >= 0) && (hdata.r < R) && (hdata.c >= 0) && (hdata.c < C)) {
				if (arr[hdata.r][hdata.c] == 'D') {
					return hdata.num;
				}
				else if ((arr[hdata.r][hdata.c] == '.') && (vh[hdata.r][hdata.c] == 0)) {
					Enqueue(&q, hdata);
				}
			}
		}
	}
	return -1;
}

int main() {
	Data start, w;
	Queue water;
	int ret;
	scanf("%d %d", &R, &C);
	while (getchar() != '\n');
	for (int i = 0; i < R; i++) {
		fgets(arr[i], C + 1, stdin);
		while (getchar() != '\n');
	}

	Initqueue(&water);
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			if (arr[i][j] == 'S') {
				start.r = i;
				start.c = j;
				start.num = 0;
				arr[i][j] = '.';
			}
			else if (arr[i][j] == '*') {
				w.r = i;
				w.c = j;
				w.num = 0;
				Enqueue(&water, w);
			}
		}
	}

	ret = BFS(&water, start);
	if (ret == -1) {
		printf("KAKTUS");
	}
	else {
		printf("%d", ret);
	}
	return 0;
}