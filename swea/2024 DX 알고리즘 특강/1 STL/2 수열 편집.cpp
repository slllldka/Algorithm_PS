#include <iostream>
#include <list>

using namespace std;

int T, N, M, L;
list<int> arr;

int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int inputInt, n1, n2;
	char inputChar;
	list<int>::iterator iter;

	cin >> T;
	for (int t = 1; t <= T; t++) {
		arr.clear();
		cin >> N >> M >> L;
		for (int i = 0; i < N; i++) {
			cin >> inputInt;
			arr.push_back(inputInt);
		}

		for (int i = 0; i < M; i++) {
			cin >> inputChar;
			if (inputChar == 'I') {
				cin >> n1 >> n2;
				iter = arr.begin();
				advance(iter, n1);
				arr.insert(iter, n2);
			}
			else if (inputChar == 'D') {
				cin >> n1;
				iter = arr.begin();
				advance(iter, n1);
				arr.erase(iter);
			}
			else if (inputChar == 'C') {
				cin >> n1 >> n2;
				iter = arr.begin();
				advance(iter, n1);
				*iter = n2;
			}
		}

		cout << '#' << t << ' ';
		if ((int)arr.size() >= (L + 1)) {
			iter = arr.begin();
			advance(iter, L);
			cout << *iter;
		}
		else {
			cout << -1;
		}
		cout << '\n';
	}
	return 0;
}