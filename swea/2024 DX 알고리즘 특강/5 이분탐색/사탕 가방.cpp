#include <iostream>

using namespace std;

long long N, M;
long long arr[100];

bool isPossible(long long numOfBags) {
	if (numOfBags == 0) {
		return true;
	}
	long long sum = 0;
	for (int i = 0; i < N; i++) {
		sum += arr[i] / numOfBags;
	}

	return sum >= M;
}

int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	long long T, maxArr, start, end, mid;
	long long maxTrue = 0;
	cin >> T;
	for (int t = 1; t <= T; t++) {
		maxArr = 0;
		maxTrue = 0;
		cin >> N >> M;
		for (int i = 0; i < N; i++) {
			cin >> arr[i];
			maxArr = maxArr > arr[i] ? maxArr : arr[i];
		}

		start = 0;
		end = maxArr;
		while (start <= end) {
			mid = (start + end) / 2;
			if (isPossible(mid)) {
				maxTrue = maxTrue > mid ? maxTrue : mid;
				start = mid + 1;
			}
			else {
				end = mid - 1;
			}
		}
		cout << '#' << t << ' ' << maxTrue << '\n';
	}
}

/*
가방의 최대 개수는 종류별 사탕 개수의 최댓값이다.
*/