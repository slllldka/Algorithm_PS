#include <iostream>
#include <queue>

using namespace std;
using i2 = pair<int, int>;

priority_queue<i2> pq;

int main() {
	int T, N, K;
	int arr[10] = {};
	cin >> T;
	for (int t = 1; t <= T; t++) {
		cin >> N;
		for (int i = 0; i < N; i++) {
			cin >> arr[i];
		}
		cin >> K;

		pq = priority_queue<i2>();
		pq.push(i2(0, K));
		while (!pq.empty()) {
			int cost, x;
			cost = -pq.top().first;
			x = pq.top().second;
			pq.pop();

			if (x == 0) {
				cout << '#' << t << ' ' << cost << '\n';
				break;
			}
			
			for (int i = 0; i < N; i++) {
				pq.push(i2(-(cost + x % arr[i]), x / arr[i]));
			}
		}
	}
	return 0;
}