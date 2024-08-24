#include <iostream>

using namespace std;

int N;
char tree[101];

int main() {
	int idx, trash;
	int available = 1;
	for (int t = 1; t <= 10; t++) {
		available = 1;
		cin >> N;
		for (int i = 1; i <= N; i++) {
			cin >> idx;
			cin >> tree[idx];
			if (idx * 2 <= N) {
				cin >> trash;
				if (idx * 2 + 1 <= N) {
					cin >> trash;
				}
				else {
					available = 0;
				}
			}
			else {
				if (tree[idx] == '+' || tree[idx] == '*' || tree[idx] == '-' || tree[idx] == '/') {
					available = 0;
				}
			}
		}
		
		cout << '#' << t << ' ' << available << '\n';
	}

	return 0;
}