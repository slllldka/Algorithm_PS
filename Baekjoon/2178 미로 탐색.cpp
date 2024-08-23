#include <iostream>
#include <cstring>
#include <queue>
#include <tuple>

using namespace std;

typedef tuple<int, int, int> i3;

int N, M;

int ND[] = { 1, -1, 0, 0 };
int MD[] = { 0, 0, 1, -1 };

char maze[100][101];
int cost[100][100];

void Push(queue<i3>& _ref, i3& _cur) {
	int _n = get<0>(_cur);
	int _m = get<1>(_cur);
	int _cost = get<2>(_cur);

	for (int i = 0; i < 4; i++) {
		if (_n + ND[i] >= 0 && _n + ND[i] < N && _m + MD[i] >= 0 && _m + MD[i] < M) {
			if (maze[_n + ND[i]][_m + MD[i]] == '1') {
				if (cost[_n + ND[i]][_m + MD[i]] == -1) {
					_ref.push(i3(_n + ND[i], _m + MD[i], _cost + 1));
					cost[_n + ND[i]][_m + MD[i]] = _cost + 1;
				}
			}
		}
	}
}

void BFS() {
	queue<i3> q;
	i3 temp;

	q.push(i3(0, 0, 1));
	cost[0][0] = 1;

	while (!q.empty()) {
		temp = q.front();
		q.pop();
		Push(q, temp);
	}
}

int main() {
	memset(cost, -1, sizeof(cost));

	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		cin >> maze[i];
	}

	BFS();
	cout << cost[N - 1][M - 1];
}