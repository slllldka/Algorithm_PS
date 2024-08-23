#include <iostream>

using namespace std;

long long T, N, arr[101];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	arr[1] = 1;
	arr[2] = 1;
	arr[3] = 1;
	arr[4] = 2;
	arr[5] = 2;

	for (int i = 6; i <= 100; i++) {
		arr[i] = arr[i - 5] + arr[i - 1];
	}

	cin >> T;
	for (int i = 0; i < T; i++) {
		cin >> N;
		cout << arr[N] << '\n';
	}

	return 0;
}