#include <iostream>
#include <utility>
#include <queue>
#include <cmath>

using namespace std;

typedef pair<int, int> i2;

int N, M;

int* dist;

queue<i2> q;

int BFS();

int main() {
	int input = 0;
	cin >> N;
	cin >> M;
	dist = new int[N + 1];
	for (int i = 0; i <= N; i++) {
		dist[i] = 0;
	}
	for (int i = 0; i < M; i++) {
		cin >> input;
		q.push(i2(input, 0));
	}

	cout << BFS();
}

int BFS() {
	while (!q.empty()) {
		i2 data = q.front();
		int num = data.first;
		int d = data.second;
		q.pop();

		int newPW = 0;
		for (int i = 0; i <= (int)log2(N); i++) {
			if ((num & (1 << i)) > 0) {
				newPW = num - (1 << i);
			}
			else {
				newPW = num + (1 << i);
			}

			if (newPW <= N) {
				if (dist[newPW] == 0) {
					dist[newPW] = d + 1;
					q.push(i2(newPW, d + 1));
				}
			}
		}
	}

	int max = 0;
	for (int i = 0; i <= N; i++) {
		max = max >= dist[i] ? max : dist[i];
	}

	return max;
}