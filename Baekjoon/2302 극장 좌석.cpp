#include <iostream>

using namespace std;

int N, M, arr[41], method[41];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> N >> M;
	for (int i = 1; i <= M; i++) {
		cin >> arr[i];
	}

	method[0] = 1;
	method[1] = 1;
	method[2] = 2;
	for (int i = 3; i <= 40; i++) {
		method[i] = method[i - 1] + method[i - 2];
	}

	if (M == 0) {
		cout << method[N];
		return 0;
	}

	int result = 1;
	int last = 0;
	for (int i = 1; i <= M; i++) {
		result *= method[arr[i] - 1 - last];
		last = arr[i];
	}
	result *= method[N - last];

	cout << result;
	return 0;
}