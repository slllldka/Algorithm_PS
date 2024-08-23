#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define min(a, b) (((a) < (b)) ? (a) : (b))
#define MAX 10000

char visited[50][50];
int N, M, arr[50][50], total;
int rd[4] = { 1, 0, -1, 0 };
int cd[4] = { 0, 1, 0, -1 };

typedef struct _d {
	int r, c, t;
}Data;

typedef struct _q {
	int f, r;
	Data data[MAX];
}Queue;

Queue q;

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

int BFS(Queue* p) {
	int r, c, t, count = 0;
	Data data;
	memset(visited, 0, sizeof(char) * 2500);
	while (p->f != p->r) {
		data = Peek(p);
		Dequeue(p);
		r = data.r;
		c = data.c;
		t = data.t;
		if (visited[r][c] == 1) {
			continue;
		}
		else if (visited[r][c] == 0) {
			visited[r][c] = 1;
			if (arr[r][c] == 0) {
				count++;
			}
		}

		if (count == total) {
			return t;
		}

		data.t = t + 1;
		for (int i = 0; i < 4; i++) {
			data.r = r + rd[i];
			data.c = c + cd[i];
			if ((data.r >= 0) && (data.r < N) && (data.c >= 0) && (data.c < N)) {
				if (((arr[data.r][data.c] == 0) || (arr[data.r][data.c] == 2))
					&& (visited[data.r][data.c] == 0)) {
					Enqueue(p, data);
				}
			}
		}
	}

	if (count < total) {
		return -1;
	}
}

int main() {
	int count = 0, check = 0;
	int Min = 1000000, ret;
	Data virus[10];
	scanf("%d %d", &N, &M);
	total = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &arr[i][j]);
			if (arr[i][j] == 2) {
				virus[count].r = i;
				virus[count].c = j;
				virus[count].t = 0;
				count++;
			}
			else if (arr[i][j] == 0) {
				total++;
			}
		}
	}

	if (M == 1) {
		for (int i = 0; i < count; i++) {
			Initqueue(&q);
			Enqueue(&q, virus[i]);
			ret = BFS(&q);
			if (ret != -1) {
				Min = min(Min, ret);
			}
		}
	}
	else if (M == 2) {
		for (int i = 0; i < count - 1; i++) {
			for (int j = i + 1; j < count; j++) {
				Initqueue(&q);
				Enqueue(&q, virus[i]);
				Enqueue(&q, virus[j]);
				ret = BFS(&q);
				if (ret != -1) {
					Min = min(Min, ret);
				}
			}
		}
	}
	else if (M == 3) {
		for (int i = 0; i < count - 2; i++) {
			for (int j = i + 1; j < count - 1; j++) {
				for (int k = j + 1; k < count; k++) {
					Initqueue(&q);
					Enqueue(&q, virus[i]);
					Enqueue(&q, virus[j]);
					Enqueue(&q, virus[k]);
					ret = BFS(&q);
					if (ret != -1) {
						Min = min(Min, ret);
					}
				}
			}
		}
	}
	else if (M == 4) {
		for (int i = 0; i < count - 3; i++) {
			for (int j = i + 1; j < count - 2; j++) {
				for (int k = j + 1; k < count - 1; k++) {
					for (int l = k + 1; l < count; l++) {
						Initqueue(&q);
						Enqueue(&q, virus[i]);
						Enqueue(&q, virus[j]);
						Enqueue(&q, virus[k]);
						Enqueue(&q, virus[l]);
						ret = BFS(&q);
						if (ret != -1) {
							Min = min(Min, ret);
						}
					}
				}
			}
		}
	}
	else if (M == 5) {
		for (int i = 0; i < count - 4; i++) {
			for (int j = i + 1; j < count - 3; j++) {
				for (int k = j + 1; k < count - 2; k++) {
					for (int l = k + 1; l < count - 1; l++) {
						for (int m = l + 1; m < count; m++) {
							Initqueue(&q);
							Enqueue(&q, virus[i]);
							Enqueue(&q, virus[j]);
							Enqueue(&q, virus[k]);
							Enqueue(&q, virus[l]);
							Enqueue(&q, virus[m]);
							ret = BFS(&q);
							if (ret != -1) {
								Min = min(Min, ret);
							}
						}
					}
				}
			}
		}
	}
	else if (M == 6) {
		for (int i = 0; i < count - 5; i++) {
			for (int j = i + 1; j < count - 4; j++) {
				for (int k = j + 1; k < count - 3; k++) {
					for (int l = k + 1; l < count - 2; l++) {
						for (int m = l + 1; m < count - 1; m++) {
							for (int n = m + 1; n < count; n++) {
								Initqueue(&q);
								Enqueue(&q, virus[i]);
								Enqueue(&q, virus[j]);
								Enqueue(&q, virus[k]);
								Enqueue(&q, virus[l]);
								Enqueue(&q, virus[m]);
								Enqueue(&q, virus[n]);
								ret = BFS(&q);
								if (ret != -1) {
									Min = min(Min, ret);
								}
							}
						}
					}
				}
			}
		}
	}
	else if (M == 7) {
		for (int i = 0; i < count - 6; i++) {
			for (int j = i + 1; j < count - 5; j++) {
				for (int k = j + 1; k < count - 4; k++) {
					for (int l = k + 1; l < count - 3; l++) {
						for (int m = l + 1; m < count - 2; m++) {
							for (int n = m + 1; n < count - 1; n++) {
								for (int o = n + 1; o < count; o++) {
									Initqueue(&q);
									Enqueue(&q, virus[i]);
									Enqueue(&q, virus[j]);
									Enqueue(&q, virus[k]);
									Enqueue(&q, virus[l]);
									Enqueue(&q, virus[m]);
									Enqueue(&q, virus[n]);
									Enqueue(&q, virus[o]);
									ret = BFS(&q);
									if (ret != -1) {
										Min = min(Min, ret);
									}
								}
							}
						}
					}
				}
			}
		}
	}
	else if (M == 8) {
		for (int i = 0; i < count - 7; i++) {
			for (int j = i + 1; j < count - 6; j++) {
				for (int k = j + 1; k < count - 5; k++) {
					for (int l = k + 1; l < count - 4; l++) {
						for (int m = l + 1; m < count - 3; m++) {
							for (int n = m + 1; n < count - 2; n++) {
								for (int o = n + 1; o < count - 1; o++) {
									for (int p = o + 1; p < count; p++) {
										Initqueue(&q);
										Enqueue(&q, virus[i]);
										Enqueue(&q, virus[j]);
										Enqueue(&q, virus[k]);
										Enqueue(&q, virus[l]);
										Enqueue(&q, virus[m]);
										Enqueue(&q, virus[n]);
										Enqueue(&q, virus[o]);
										Enqueue(&q, virus[p]);
										ret = BFS(&q);
										if (ret != -1) {
											Min = min(Min, ret);
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	else if (M == 9){
		for (int i = 0; i < count - 8; i++) {
			for (int j = i + 1; j < count - 7; j++) {
				for (int k = j + 1; k < count - 6; k++) {
					for (int l = k + 1; l < count - 5; l++) {
						for (int m = l + 1; m < count - 4; m++) {
							for (int n = m + 1; n < count - 3; n++) {
								for (int o = n + 1; o < count - 2; o++) {
									for (int p = o + 1; p < count - 1; p++) {
										for (int r = p + 1; r < count; r++) {
											Initqueue(&q);
											Enqueue(&q, virus[i]);
											Enqueue(&q, virus[j]);
											Enqueue(&q, virus[k]);
											Enqueue(&q, virus[l]);
											Enqueue(&q, virus[m]);
											Enqueue(&q, virus[n]);
											Enqueue(&q, virus[o]);
											Enqueue(&q, virus[p]);
											Enqueue(&q, virus[r]);
											ret = BFS(&q);
											if (ret != -1) {
												Min = min(Min, ret);
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	else if (M == 10) {
		Initqueue(&q);
		for (int i = 0; i < count; i++) {
			Enqueue(&q, virus[i]);
		}
		ret = BFS(&q);
		if (ret != -1) {
			Min = min(Min, ret);
		}
	}
	if (Min == 1000000) {
		printf("-1");
	}
	else {
		printf("%d", Min);
	}
	return 0;
}