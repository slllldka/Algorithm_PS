#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char visited[10001];
int arr[10001];

typedef struct _n {
	int idx;
	struct _n* next;
}Node;

typedef struct _g {
	int num;
	Node** heads;
}Graph;

void InitGraph(Graph* p, int n) {
	p->num = n;
	p->heads = (Node**)malloc(sizeof(Node*) * (n + 1));
	for (int i = 1; i <= n; i++) {
		p->heads[i] = (Node*)malloc(sizeof(Node));
		p->heads[i]->next = NULL;
	}
}
void DestroyGraph(Graph* p) {
	int n = p->num;
	Node* temp;
	Node* cur;
	for (int i = 1; i <= n; i++) {
		cur = p->heads[i];
		while (cur != NULL) {
			temp = cur;
			cur = cur->next;
			free(temp);
		}
	}
	free(p->heads);
}
void AddEdge(Graph* p, int s, int e) {
	Node* cur;
	Node* newnode = (Node*)malloc(sizeof(Node));
	newnode->idx = e;
	newnode->next = NULL;
	cur = p->heads[s];
	while (cur->next != NULL) {
		cur = cur->next;
	}
	cur->next = newnode;
}

void Find(Graph* p, int idx, int start) {
	if (visited[start] == 1) {
		return;
	}
	Node* cur;
	visited[start] = 1;
	if (idx != start) {
		arr[idx]++;
	}
	cur = p->heads[start]->next;
	while (cur != NULL) {
		if (visited[cur->idx] == 0) {
			Find(p, idx, cur->idx);
		}
		cur = cur->next;
	}
}

int main() {
	Graph g;
	int N, M, s, e, Max;
	scanf("%d %d", &N, &M);
	InitGraph(&g, N);
	for (int i = 0; i < M; i++) {
		scanf("%d %d", &s, &e);
		AddEdge(&g, e, s);
	}

	for (int i = 1; i <= N; i++) {
		memset(visited, 0, sizeof(visited));
		Find(&g, i, i);
	}

	Max = arr[1];
	for (int i = 2; i <= N; i++) {
		if (arr[i] > Max) {
			Max = arr[i];
		}
	}
	for (int i = 1; i <= N; i++) {
		if (arr[i] == Max) {
			printf("%d ", i);
		}
	}
	return 0;
}