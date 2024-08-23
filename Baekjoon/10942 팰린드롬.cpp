#include <iostream>

using namespace std;

int N, M;
int arr[2000];
int pLen1[2000];
int pLen2[2000];

int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> arr[i];
	}

	for (int i = 0; i < N; i++) {
		int len = 1;
		for (int j = 1; j < 1000; j++) {
			if ((i - j >= 0) && (i + j < N)) {
				if (arr[i - j] == arr[i + j]) {
					len += 2;
				}
				else {
					break;
				}
			}
			else {
				break;
			}
		}
		pLen1[i] = len;
	}

	for (int i = 0; i < N - 1; i++) {
		int len = 0;
		for (int j = 0; j < 1000; j++) {
			if ((i - j >= 0) && (i + 1 + j < N)) {
				if (arr[i - j] == arr[i + 1 + j]) {
					len += 2;
				}
				else {
					break;
				}
			}
			else {
				break;
			}
		}
		pLen2[i] = len;
	}

	cin >> M;
	for (int i = 0; i < M; i++) {
		int s = 0, e = 0;
		int mid = 0, len = 0;
		cin >> s >> e;
		s--;
		e--;
		mid = (s + e) / 2;
		len = e - s + 1;
		if ((s + e) % 2 == 0) {
			if (pLen1[mid] >= len) {
				cout << 1 << '\n';
			}
			else {
				cout << 0 << '\n';
			}
		}
		else {
			if (pLen2[mid] >= len) {
				cout << 1 << '\n';
			}
			else {
				cout << 0 << '\n';
			}
		}
	}

	return 0;
}