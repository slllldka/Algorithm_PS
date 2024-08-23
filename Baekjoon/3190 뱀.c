#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _d {
	int X;
	char C;
}Data;

typedef struct _node {
	int r, c;
	struct _node* next;
}Node;

typedef struct _ll {
	int num;
	Node* head;
}LL;

char arr[100][100];
int N, K, L, l, ret;
Data* data;
LL ll;

void InitLL(LL* p) {
	p->num = 0;
	p->head = (Node*)malloc(sizeof(Node));
	p->head->next = NULL;
}

void AddFirst(LL* p, int r, int c) {
	Node* cur = p->head;
	Node* temp = cur;
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->r = r;
	newNode->c = c;
	newNode->next = cur->next;
	temp->next = newNode;
	p->num++;
}

void RemoveLast(LL* p) {
	Node* cur = p->head;
	Node* temp;
	for (int i = 0; i < p->num - 1; i++) {
		cur = cur->next;
	}
	temp = cur;
	cur = cur->next;
	temp->next = NULL;
	free(cur);
	p->num--;
}



DestroyLL(LL* p) {
	Node* cur;
	Node* temp;
	cur = p->head;
	while (cur->next != NULL) {
		temp = cur;
		cur = cur->next;
		free(temp);
	}
	p->num = 0;
}

void Dummy(int r, int c, int t, char dir) {
	Node* cur = ll.head->next;
	char change;
	if (ret != 0) {
		return;
	}
	if ((r == -1) || (r == N) || (c == -1) || (c == N)) {
		ret = t;
		return;
	}
	
	while (cur != NULL) {
		if ((cur->r == r) && (cur->c == c)) {
			ret = t;
			return;
		}
		cur = cur->next;
	}


	AddFirst(&ll, r, c);
	if (t != 0) {
		if (arr[r][c] == 1) {
			arr[r][c] = 0;
		}
		else {
			RemoveLast(&ll);
		}
	}
	if (l < L) {
		if (data[l].X == t) {
			change = data[l].C;
			l++;
			if (change == 'L') {
				if (dir == 'L') {
					Dummy(r + 1, c, t + 1, 'D');
				}
				else if (dir == 'D') {
					Dummy(r, c + 1, t + 1, 'R');
				}
				else if (dir == 'R') {
					Dummy(r - 1, c, t + 1, 'U');
				}
				else if (dir == 'U') {
					Dummy(r, c - 1, t + 1, 'L');
				}
			}
			else if (change == 'D') {
				if (dir == 'L') {
					Dummy(r - 1, c, t + 1, 'U');
				}
				else if (dir == 'D') {
					Dummy(r, c - 1, t + 1, 'L');
				}
				else if (dir == 'R') {
					Dummy(r + 1, c, t + 1, 'D');
				}
				else if (dir == 'U') {
					Dummy(r, c + 1, t + 1, 'R');
				}
			}
		}
		else {
			if (dir == 'L') {
				Dummy(r, c - 1, t + 1, 'L');
			}
			else if (dir == 'D') {
				Dummy(r + 1, c, t + 1, 'D');
			}
			else if (dir == 'R') {
				Dummy(r, c + 1, t + 1, 'R');
			}
			else if (dir == 'U') {
				Dummy(r - 1, c, t + 1, 'U');
			}
		}
	}
	else {
		if (dir == 'L') {
			Dummy(r, c - 1, t + 1, 'L');
		}
		else if (dir == 'D') {
			Dummy(r + 1, c, t + 1, 'D');
		}
		else if (dir == 'R') {
			Dummy(r, c + 1, t + 1, 'R');
		}
		else if (dir == 'U') {
			Dummy(r - 1, c, t + 1, 'U');
		}
	}
}

int main() {
	int r, c;
	scanf("%d", &N);
	scanf("%d", &K);
	for (int i = 0; i < K; i++) {
		scanf("%d %d", &r, &c);
		arr[r - 1][c - 1] = 1;
	}
	scanf("%d", &L);
	data = (Data*)malloc(sizeof(Data) * L);
	for (int i = 0; i < L; i++) {
		scanf("%d %c", &data[i].X, &data[i].C);
		while (getchar() != '\n');
	}

	InitLL(&ll);
	l = 0;
	ret = 0;
	Dummy(0, 0, 0, 'R');
	printf("%d", ret);
	DestroyLL(&ll);
	return 0;
}