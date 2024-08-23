#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define min(a, b) (((a) < (b)) ? (a) : (b))
#define MAX 100000

int N, M;
char arr[11][11];

typedef struct _data {
	int rn;
	int rm;
	int bn;
	int bm;
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

int BFS(Data start) {
	Queue q;
	Data data;
	int rn, rm, bn, bm, num, ret = 0;
	Initqueue(&q);
	Enqueue(&q, start);
	while (q.f != q.r) {
		data = Peek(&q);
		Dequeue(&q);
		rn = data.rn;
		rm = data.rm;
		bn = data.bn;
		bm = data.bm;
		num = data.num;

		//1. 둘다 #이면 못감
		//2. 변동하지 않는 index가 같은 경우 하나는 #, 하나는 다른 구슬이면 못감

		//n증가
		if ((arr[rn + 1][rm] != '#') || (arr[bn + 1][bm] != '#')) {
			if ((((rn + 1 != bn) || (rm != bm)) || (arr[bn + 1][bm] != '#'))
				&& (((bn + 1 != rn) || (rm != bm)) || (arr[rn + 1][rm] != '#'))) {
				while ((arr[data.rn][data.rm] != '#') && (arr[data.rn][data.rm] != 'O')) {
					data.rn++;
				}
				while ((arr[data.bn][data.bm] != '#') && (arr[data.bn][data.bm] != 'O')) {
					data.bn++;
				}
				if (arr[data.bn][data.bm] != 'O') {
					if (arr[data.rn][data.rm] == 'O') {
						ret = num + 1;
						break;
					}
					else {
						data.rn--;
						data.bn--;
						data.num++;
						if ((data.rn == data.bn) && (data.rm == data.bm)) {
							if (rn > bn) {
								data.bn--;
							}
							else {
								data.rn--;
							}
						}
						if (data.num < 10) {
							Enqueue(&q, data);
						}
					}
				}
			}
		}
		data.rn = rn;
		data.rm = rm;
		data.bn = bn;
		data.bm = bm;
		data.num = num;
		//n감소
		if ((arr[rn - 1][rm] != '#') || (arr[bn - 1][bm] != '#')) {
			if ((((rn - 1 != bn) || (rm != bm)) || (arr[bn - 1][bm] != '#'))
				&& (((bn - 1 != rn) || (rm != bm)) || (arr[rn - 1][rm] != '#'))) {
				while ((arr[data.rn][data.rm] != '#') && (arr[data.rn][data.rm] != 'O')) {
					data.rn--;
				}
				while ((arr[data.bn][data.bm] != '#') && (arr[data.bn][data.bm] != 'O')) {
					data.bn--;
				}
				if (arr[data.bn][data.bm] != 'O') {
					if (arr[data.rn][data.rm] == 'O') {
						ret = num + 1;
						break;
					}
					else {
						data.rn++;
						data.bn++;
						data.num++;
						if ((data.rn == data.bn) && (data.rm == data.bm)) {
							if (rn < bn) {
								data.bn++;
							}
							else {
								data.rn++;
							}
						}
						if (data.num < 10) {
							Enqueue(&q, data);
						}
					}
				}
			}
		}
		data.rn = rn;
		data.rm = rm;
		data.bn = bn;
		data.bm = bm;
		data.num = num;
		//m증가
		if ((arr[rn][rm + 1] != '#') || (arr[bn][bm + 1] != '#')) {
			if ((((rm + 1 != bm) || (rn != bn)) || (arr[bn][bm+1] != '#'))
				&& (((bm + 1 != rm) || (rn != bn)) || (arr[rn][rm+1] != '#'))){
			while ((arr[data.rn][data.rm] != '#') && (arr[data.rn][data.rm] != 'O')) {
				data.rm++;
			}
			while ((arr[data.bn][data.bm] != '#') && (arr[data.bn][data.bm] != 'O')) {
				data.bm++;
			}
			if (arr[data.bn][data.bm] != 'O') {
				if (arr[data.rn][data.rm] == 'O') {
					ret = num + 1;
					break;
				}
				else {
					data.rm--;
					data.bm--;
					data.num++;
					if ((data.rn == data.bn) && (data.rm == data.bm)) {
						if (rm > bm) {
							data.bm--;
						}
						else {
							data.rm--;
						}
					}
					if (data.num < 10) {
						Enqueue(&q, data);
					}
				}
			}
			}
		}
		data.rn = rn;
		data.rm = rm;
		data.bn = bn;
		data.bm = bm;
		data.num = num;
		//m감소
		if ((arr[rn][rm - 1] != '#') || (arr[bn][bm - 1] != '#')) {
			if ((((rm - 1 != bm) || (rn != bn)) || (arr[bn][bm - 1] != '#'))
				&& (((bm - 1 != rm) || (rn != bn)) || (arr[rn][rm - 1] != '#'))) {
				while ((arr[data.rn][data.rm] != '#') && (arr[data.rn][data.rm] != 'O')) {
					data.rm--;
				}
				while ((arr[data.bn][data.bm] != '#') && (arr[data.bn][data.bm] != 'O')) {
					data.bm--;
				}
				if (arr[data.bn][data.bm] != 'O') {
					if (arr[data.rn][data.rm] == 'O') {
						ret = num + 1;
						break;
					}
					else {
						data.rm++;
						data.bm++;
						data.num++;
						if ((data.rn == data.bn) && (data.rm == data.bm)) {
							if (rm < bm) {
								data.bm++;
							}
							else {
								data.rm++;
							}
						}
						if (data.num < 10) {
							Enqueue(&q, data);
						}
					}
				}
			}
		}
	}
	if (ret == 0) {
		ret = -1;
	}
	return ret;
}

int main() {
	Data start;
	int ret = 0;
	scanf("%d %d", &N, &M);
	while (getchar() != '\n');
	for (int i = 0; i < N; i++) {
		fgets(arr[i], M + 1, stdin);
		while (getchar() != '\n');
	}

	for (int i = 1; i < N - 1; i++) {
		for (int j = 1; j < M - 1; j++) {
			if (arr[i][j] == 'R') {
				start.rn = i;
				start.rm = j;
				ret++;
				if (ret == 2) {
					break;
				}
			}
			else if (arr[i][j] == 'B') {
				start.bn = i;
				start.bm = j;
				ret++;
				if (ret == 2) {
					break;
				}
			}
		}
	}
	arr[start.rn][start.rm] = '.';
	arr[start.bn][start.bm] = '.';
	start.num = 0;

	ret = BFS(start);
	printf("%d", ret);
	return 0;
}