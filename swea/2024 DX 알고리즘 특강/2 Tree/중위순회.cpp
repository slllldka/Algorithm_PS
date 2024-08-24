#include <iostream>

using namespace std;

int N;
char tree[101];

void inorder(int idx) {
	if (idx <= N) {
		inorder(idx * 2);
		cout << tree[idx];
		inorder(idx * 2 + 1);
	}
}

int main() {
	int idx, trash;
	for (int t = 1; t <= 10; t++) {
		cin >> N;
		for (int i = 1; i <= N; i++) {
			cin >> idx;
			cin >> tree[idx];
			if (idx * 2 <= N) {
				cin >> trash;
				if (idx * 2 + 1 <= N) {
					cin >> trash;
				}
			}
		}
		
		cout << '#' << t << ' ';
		inorder(1);
		cout << '\n';
	}

	return 0;
}