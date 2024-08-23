#include <iostream>
#include <queue>
#include <utility>
#include <cstring>

using namespace std;

typedef pair<int, int> i2;

int N, * minCost;
queue<i2> q;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N;

	minCost = new int[1000001];
	memset(minCost, 0, sizeof(int) * 1000001);

	q.push(i2(1, 0));

	int num, cost;
	i2 data;
	while (!q.empty()) {
		data = q.front();
		num = data.first;
		cost = data.second;
		q.pop();
		if ((num * 3) <= 1000000) {
			if (minCost[num * 3] == 0) {
				minCost[num * 3] = cost + 1;
				q.push(i2(num * 3, cost + 1));
				if ((num * 3) == N) {
					break;
				}
			}
		}
		if ((num * 2) <= 1000000) {
			if (minCost[num * 2] == 0) {
				minCost[num * 2] = cost + 1;
				q.push(i2(num * 2, cost + 1));
				if ((num * 2) == N) {
					break;
				}
			}
		}
		if ((num + 1) <= 1000000) {
			if (minCost[num + 1] == 0) {
				minCost[num + 1] = cost + 1;
				q.push(i2(num + 1, cost + 1));
				if ((num + 1) == N) {
					break;
				}
			}
		}
	}

	num = N;
	cost = minCost[N];
	cout << cost << '\n' << N << ' ';
	while (num != 1) {
		cost--;
		if (num % 3 == 0) {
			if (minCost[num / 3] == cost) {
				num /= 3;
				cout << num << ' ';
				continue;
			}
		}
		if (num % 2 == 0) {
			if (minCost[num / 2] == cost) {
				num /= 2;
				cout << num << ' ';
				continue;
			}
		}
		if (num - 1 > 0) {
			if (minCost[num - 1] == cost) {
				num -= 1;
				cout << num << ' ';
				continue;
			}
		}
	}
	
	delete[] minCost;

	return 0;
}