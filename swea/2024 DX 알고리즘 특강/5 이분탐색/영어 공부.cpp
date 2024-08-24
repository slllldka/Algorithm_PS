#include <iostream>

using namespace std;

int n, p;
int nArr[200000];
int newNArr[200001];

bool available(int period) {
	if (period <= p + 1) {
		return true;
	}
	int start = 1, end = 0, len = 0, left = p;
	while (start <= n && end <= n) {
		if (start > end) {
			end++;
			if (start == end) {
				len += newNArr[end];
				left -= newNArr[end];
			}
		}
		else {
			if (left >= 0) {
				if (len + (end - start + 1) + 1 + left >= period) {
					if (newNArr[start - 1] + newNArr[end + 1] >= left) {
						return true;
					}
				}
				end++;
				len += newNArr[end];
				left -= newNArr[end];
			}
			else {
				len -= newNArr[start];
				left += newNArr[start];
				start++;
			}
		}
	}
	return false;
}

int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	int T, start, end, mid, maxPeriod;
	cin >> T;
	for (int t = 1; t <= T; t++) {
		cin >> n >> p;
		for (int i = 0; i < n; i++) {
			cin >> nArr[i];
		}
		newNArr[0] = nArr[0];
		for (int i = 1; i < n; i++) {
			newNArr[i] = nArr[i] - nArr[i - 1] - 1;
		}
		newNArr[n] = 1000000 - nArr[n - 1];

		maxPeriod = 0;
		start = p + 1;
		end = n + p;
		while (start <= end) {
			mid = (start + end) / 2;
			if (available(mid)) {
				start = mid + 1;
				maxPeriod = maxPeriod > mid ? maxPeriod : mid;
			}
			else {
				end = mid - 1;
			}
		}
		cout << '#' << t << ' ' << maxPeriod << '\n';
	}
	return 0;
}

/*
"이분탐색"으로 최대 길이를 탐색
"투포인터"를 사용하여 특정 길이가 가능한지 판단!!
*/