#include <iostream>

using namespace std;

long long N, M, cumulativeSum[100001];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int input, first, second;
	cin >> N >> M;
	cumulativeSum[0] = 0;
	for (int i = 0; i < N; i++) {
		cin >> input;
		cumulativeSum[i + 1] = cumulativeSum[i] + input;
	}

	for (int i = 0; i < M; i++) {
		cin >> first >> second;
		cout << cumulativeSum[second] - cumulativeSum[first - 1] << '\n';
	}

	return 0;
}