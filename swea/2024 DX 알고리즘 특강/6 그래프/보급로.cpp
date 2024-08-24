#include <iostream>
#include <climits>
#include <queue>

using namespace std;

class i3 {
public:
	int first, second, third; // cost, x, y
	i3() {
		first = 0;
		second = 0;
		third = 0;
	}
	i3(int first, int second, int third) {
		this->first = first;
		this->second = second;
		this->third = third;
	}
};

struct compare {
public:
	bool operator()(const i3& ref1, const i3& ref2) {
		return ref1.first <= ref2.first;
	}
};

int xDir[4] = { 1, 0, -1, 0 };
int yDir[4] = { 0, 1, 0, -1 };

int N;
int map[100][100];
int d[100][100];

int dijkstra() {
	int cost, x, y, newX, newY;
	priority_queue<i3, vector<i3>, compare> pq;
	pq.push(i3(0, 0, 0));
	while (!pq.empty()) {
		cost = -pq.top().first;
		x = pq.top().second;
		y = pq.top().third;
		pq.pop();
		if ((x == (N - 1)) && (y == (N - 1))) {
			break;
		}

		for (int i = 0; i < 4; i++) {
			newX = x + xDir[i];
			newY = y + yDir[i];
			if (newX >= 0 && newX < N && newY >= 0 && newY < N) {
				if (newX != x || newY != y) {
					if (cost + map[newX][newY] < d[newX][newY]) {
						d[newX][newY] = cost + map[newX][newY];
						pq.push(i3(-d[newX][newY], newX, newY));
					}
				}
			}
		}
	}
	return d[x][y];
}

int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	int T;
	string input;
	cin >> T;
	for (int t = 1; t <= T; t++) {
		cin >> N;
		for (int i = 0; i < N; i++) {
			cin >> input;
			for (int j = 0; j < N; j++) {
				map[i][j] = input[j] - '0';
				d[i][j] = INT32_MAX;
			}
		}

		cout << '#' << t << ' ' << dijkstra() << '\n';
	}
	return 0;
}