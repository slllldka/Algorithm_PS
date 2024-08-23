#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX 1000

int N, size, fishnum;
int rd[4] = { 1, 0, -1, 0 };
int cd[4] = { 0, 1, 0, -1 };
int arr[20][20];
char visited[20][20];

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

int BFS(Data start, int tr, int tc){
	int r, c, num;
	Data data;
	Queue q;
	Initqueue(&q);
	Enqueue(&q, start);
	while (q.f != q.r) {
		data = Peek(&q);
		Dequeue(&q);
		r = data.r;
		c = data.c;
		num = data.num;
		if ((arr[r][c] >= 1) && (arr[r][c] <= 6) && (arr[r][c] > size)) {
			continue;
		}
		if (visited[r][c] == 1) {
			continue;
		}
		else if (visited[r][c] == 0) {
			visited[r][c] = 1;
		}

		for (int i = 0; i < 4; i++) {
			data.r = r + rd[i];
			data.c = c + cd[i];
			data.num = num + 1;
			if ((data.r >= 0) && (data.r < N) && (data.c >= 0) && (data.c < N)) {
				if ((data.r == tr) && (data.c == tc)) {
					return data.num;
				}
				if ((arr[data.r][data.c] <= size) && (visited[data.r][data.c] == 0)) {
					Enqueue(&q, data);
				}
			}
		}
	}
	return -1;
}

int main() {
	int ret, minimum, minr, minc, output;
	Data start;
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &arr[i][j]);
			if (arr[i][j] == 9) {
				start.r = i;
				start.c = j;
				start.num = 0;
				arr[i][j] = 0;
			}
		}
	}

	size = 2;
	fishnum = 0;
	output = 0;
	while (1) {
		minr = -1;
		minc = -1;
		minimum = -1;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if ((arr[i][j] < size) && (arr[i][j] >= 1) && (arr[i][j] <= 6)) {
					if ((minr == -1) && (minc == -1)) {
						ret = BFS(start, i, j);
						memset(visited, 0, sizeof(char) * 400);
						if (ret != -1) {
							minimum = ret;
							minr = i;
							minc = j;
						}
					}
					else {
						if (minimum >= abs(i - start.r) + abs(j - start.c)) {
							ret = BFS(start, i, j);
							memset(visited, 0, sizeof(char) * 400);
							if (ret != -1) {
								if (minimum > ret) {
									minimum = ret;
									minr = i;
									minc = j;
								}
								else if (minimum == ret) {
									if (i < minr) {
										minr = i;
										minc = j;
									}
									else if (i == minr) {
										if (j < minc) {
											minc = j;
										}
									}
								}
							}
						}
					}
				}
			}
		}

		if (minimum == -1) {
			break;
		}
		else if (minimum > 0) {
			arr[minr][minc] = 0;
			output += minimum;
			fishnum++;
			if (fishnum == size) {
				size++;
				fishnum = 0;
			}
			start.r = minr;
			start.c = minc;
			start.num = 0;
		}
	}

	printf("%d", output);
	return 0;
}