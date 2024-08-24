#include <iostream>
#include <queue>

using namespace std;

priority_queue<int> maxHeap, minHeap;

int main() {
	int T, N, x, temp1, temp2;
	long long sum = 0;
	cin >> T;
	for (int t = 1; t <= T; t++) {
		maxHeap = priority_queue<int>();
		minHeap = priority_queue<int>();
		sum = 0;
		cin >> N >> x;
		maxHeap.push(x);
		for (int i = 1; i <= N; i++) {
			cin >> x;
			minHeap.push(-x);
			cin >> x;
			maxHeap.push(x);

			if (maxHeap.top() > -minHeap.top()) {
				temp1 = maxHeap.top();
				temp2 = minHeap.top();
				maxHeap.pop();
				minHeap.pop();
				maxHeap.push(-temp2);
				minHeap.push(-temp1);
			}
			sum += maxHeap.top();
			sum %= 20171109;
		}
		cout << '#' << t << ' ' << sum << '\n';
	}
}