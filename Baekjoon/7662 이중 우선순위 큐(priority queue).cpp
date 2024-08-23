#include <iostream>
#include <queue>
#include <unordered_map>

using namespace std;

priority_queue<long long> minHeap;
priority_queue<long long> maxHeap;
unordered_map<long long, long long> hashMap;

int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int T = 0;
	cin >> T;
	for (int t = 0; t < T; t++) {
		minHeap = priority_queue<long long>();
		maxHeap = priority_queue<long long>();
		hashMap.clear();

		int Q = 0;
		char oper = 0;
		long long num = 0;
		cin >> Q;
		for (int i = 0; i < Q; i++) {
			cin >> oper >> num;
			if (oper == 'I') {
				if (hashMap.count(num) > 0) {
					hashMap[num]++;
				}
				else {
					hashMap[num] = 1;
				}
				minHeap.push(-num);
				maxHeap.push(num);
			}
			else if (oper == 'D') {
				if (num == 1) {
					while (!maxHeap.empty() && (hashMap[maxHeap.top()] == 0)) {
						maxHeap.pop();
					}
					
					if (!maxHeap.empty()) {
						hashMap[maxHeap.top()]--;
						maxHeap.pop();
					}
				}
				else {
					while (!minHeap.empty() && (hashMap[-minHeap.top()] == 0)) {
						minHeap.pop();
					}

					if (!minHeap.empty()) {
						hashMap[-minHeap.top()]--;
						minHeap.pop();
					}
				}
			}
		}

		while (!maxHeap.empty() && (hashMap[maxHeap.top()] == 0)) {
			maxHeap.pop();
		}

		if (maxHeap.empty()) {
			cout << "EMPTY\n";
			continue;
		}
		else {
			cout << maxHeap.top() << ' ';
		}

		while (hashMap[-minHeap.top()] == 0) {
			minHeap.pop();
		}

		cout << -minHeap.top() << '\n';
	}
	return 0;
}