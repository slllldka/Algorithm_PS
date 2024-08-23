#include <iostream>
#include <map>

using namespace std;

map<int, int> heap;

int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int T = 0;
	cin >> T;
	for (int t = 0; t < T; t++) {
		heap.clear();

		int Q = 0;
		char oper = 0;
		int num = 0;
		cin >> Q;
		for (int i = 0; i < Q; i++) {
			cin >> oper >> num;
			if (oper == 'I') {
				if (heap.count(num) > 0) {
					heap[num]++;
				}
				else {
					heap[num] = 1;
				}
			}
			else if (oper == 'D') {
				if (num == 1) {
					if (!heap.empty()) {
						(*(heap.rbegin())).second--;
						if ((*(heap.rbegin())).second == 0) {
							heap.erase(--heap.end());
						}
					}
				}
				else {
					if (!heap.empty()) {
						(*(heap.begin())).second--;
						if ((*(heap.begin())).second == 0) {
							heap.erase(heap.begin());
						}
					}
				}
			}
		}

		if (heap.empty()) {
			cout << "EMPTY\n";
		}
		else {
			cout << (*(heap.rbegin())).first << ' ' << (*(heap.begin())).first << '\n';
		}
	}
	return 0;
}