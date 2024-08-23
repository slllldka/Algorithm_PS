#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max(a, b) (((a) > (b)) ? (a) : (b)) 

int K, V, E, ret;
char* arr;

typedef struct _node {
	int n;
	struct _node* next;
}Node;

typedef struct _graph {
	int num;
	Node** heads;
}Graph;

void CreateGraph(Graph* p) {
	p->heads = (Node**)malloc(sizeof(Node*) * 20000);
	for (int i = 0; i < 20000; i++) {
		p->heads[i] = (Node*)malloc(sizeof(Node));
		p->heads[i]->next = NULL;
	}
}
void DestroyGraph(Graph* p) {
	Node* cur, * temp;
	for (int i = 0; i < p->num; i++) {
		cur = p->heads[i]->next;
		while (cur != NULL) {
			temp = cur;
			cur = cur->next;
			free(temp);
		}
		p->heads[i]->next = NULL;
	}
}
void AddEdge(Graph* p, int s, int e) {
	Node* cur;
	Node* newnode1 = (Node*)malloc(sizeof(Node));
	Node* newnode2 = (Node*)malloc(sizeof(Node));
	newnode1->n = s;
	newnode1->next = NULL;
	cur = p->heads[e];
	while (cur->next != NULL) {
		cur = cur->next;
	}
	cur->next = newnode1;

	newnode2->n = e;
	newnode2->next = NULL;
	cur = p->heads[s];
	while (cur->next != NULL) {
		cur = cur->next;
	}
	cur->next = newnode2;
}
void DFS(Graph* p, int start, int num) {
	Node* cur;

	if ((ret == 0) || (arr[start] != 0)) {
		return;
	}

	arr[start] = num;

	cur = p->heads[start]->next;
	while (cur != NULL) {
		if (ret == 0) {
			return;
		}
		if (arr[cur->n] == 0) {
			if (num == 1) {
				DFS(p, cur->n, 2);
			}
			else if (num == 2) {
				DFS(p, cur->n, 1);
			}
		}
		else {
			if (arr[start] == arr[cur->n]) {
				ret = 0;
			}
		}
		cur = cur->next;
	}
}

int main() {
	char output[5][4];
	int s, e;
	Graph g;
	arr = (char*)malloc(sizeof(char) * 20000);
	CreateGraph(&g);
	scanf("%d", &K);
	for (int i = 0; i < K; i++) {
		scanf("%d %d", &V, &E);
		if (V == 1) {
			sprintf(output[i], "NO");
			continue;
		}
		g.num = V;
		memset(arr, 0, sizeof(char) * V);
		for (int j = 0; j < E; j++) {
			scanf("%d %d", &s, &e);
			AddEdge(&g, s - 1, e - 1);
		}
		ret = 1;
		for (int k = 0; k < V; k++) {
			if (ret == 0) {
				break;
			}
			if (arr[k] == 0) {
				DFS(&g, k, 1);
			}
		}
		if (ret == 1) {
			sprintf(output[i], "YES");
		}
		else if(ret == 0){
			sprintf(output[i], "NO");
		}
		DestroyGraph(&g);
	}

	for (int i = 0; i < K; i++) {
		printf("%s\n", output[i]);
	}

	free(arr);
	for (int i = 0; i < 20000; i++) {
		free(g.heads[i]);
	}
	free(g.heads);
	return 0;
}