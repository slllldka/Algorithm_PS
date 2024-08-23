#include <iostream>

using namespace std;

class node {
private:
	int idx, w;
	node* next;

public:
	node(int _idx, int _w) : idx(_idx), w(_w) {
		next = NULL;
	}

	int getidx() {
		return idx;
	}

	int getw() {
		return w;
	}

	void setnext(node* ptr) {
		next = ptr;
	}
	node* getnext() {
		return next;
	}
};

class graph {
private:
	int num;
	node** heads;

public:
	graph(int _num) : num(_num) {
		heads = new node * [_num];
		for (int i = 0; i < _num; i++) {
			heads[i] = new node(i, 0);
		}
	}

	void addEdge(int start, int end, int weight) {
		node* cur = heads[start];
		node* newnode = new node(end, weight);
		while (cur->getnext() != NULL) {
			cur = cur->getnext();
		}
		cur->setnext(newnode);
	}

	int getnum() {
		return num;
	}

	int Bellman_Ford(long long arr[]) {
		node* cur;
		for (int i = 0; i < num; i++) {
			arr[i] = 2147483647;
		}
		arr[0] = 0;

		for (int j = 0; j < num - 1; j++) {
			for (int i = 0; i < num; i++) {
				cur = heads[i]->getnext();
				while (cur != NULL) {
					if ((arr[i] != 2147483647) && (arr[cur->getidx()] > arr[i] + cur->getw())) {
						arr[cur->getidx()] = arr[i] + cur->getw();
					}
					cur = cur->getnext();
				}
			}
		}

		for (int i = 0; i < num; i++) {
			cur = heads[i]->getnext();
			while (cur != NULL) {
				if ((arr[i] != 2147483647) && (arr[cur->getidx()] > arr[i] + cur->getw())) {
					return 0;
				}
				cur = cur->getnext();
			}
		}

		return 1;
	}

	~graph() {
		node* cur;
		node* temp;
		for (int i = 0; i < num; i++) {
			cur = heads[i];
			while (cur != NULL) {
				temp = cur;
				cur = cur->getnext();
				delete temp;
			}
		}
		delete[]heads;
	}
};



int main() {
	long long* arr;
	int N, M, A, B, C;
	cin >> N >> M;
	graph g(N);
	arr = new long long[N];
	for (int i = 0; i < M; i++) {
		cin >> A >> B >> C;
		g.addEdge(A - 1, B - 1, C);
	}

	if (g.Bellman_Ford(arr) == 1) {
		for (int i = 1; i < N; i++) {
			if (arr[i] == 2147483647) {
				printf("-1\n");
			}
			else {
				printf("%lld\n", arr[i]);
			}
		}
	}
	else {
		printf("-1\n");
	}

	return 0;
}