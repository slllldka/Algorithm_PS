#include <iostream>
#include <queue>

using namespace std;

priority_queue<int> pq;

int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	int T, N, operNum, x;
	cin >> T;
	for (int t = 1; t <= T; t++) {
		pq = priority_queue<int>();
		cout << '#' << t << ' ';
		cin >> N;
		for (int i = 0; i < N; i++) {
			cin >> operNum;
			if (operNum == 1) {
				cin >> x;
				pq.push(x);
			}
			else if (operNum == 2) {
				if (pq.empty()) {
					cout << -1 << ' ';
				}
				else {
					cout << pq.top() << ' ';
					pq.pop();
				}
			}
		}
		cout << '\n';
	}
}