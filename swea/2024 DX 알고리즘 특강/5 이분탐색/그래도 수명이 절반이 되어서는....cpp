#include <iostream>

#define max(a, b) (((a) > (b)) ? (a) : (b))
#define min(a, b) (((a) < (b)) ? (a) : (b))

using namespace std;

int N, K;
int driveWear[200000], dataArr[200000];
int maxWear, minWear;

bool available(int wear) {
	int dataIdx = 0, len = 0;
	for (int i = 0; i < N; i++) {
		if (driveWear[i] <= wear) {
			len++;
		}
		else {
			len = 0;
		}

		if (len == dataArr[dataIdx]) {
			dataIdx++;
			len = 0;
		}

		if (dataIdx == K) {
			break;
		}
	}

	return dataIdx == K;
}

int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	int T, start, end, mid, ans;
	cin >> T;
	for (int t = 1; t <= T; t++) {
		cin >> N >> K;
		maxWear = 200001;
		minWear = 0;
		for (int i = 0; i < N; i++) {
			cin >> driveWear[i];
			maxWear = max(maxWear, driveWear[i]);
			minWear = min(minWear, driveWear[i]);
		}
		for (int i = 0; i < K; i++) {
			cin >> dataArr[i];
		}

		start = minWear;
		end = maxWear;
		ans = end + 1;
		while (start <= end) {
			mid = (start + end) / 2;
			if (available(mid)) {
				ans = mid;
				end = mid - 1;
			}
			else {
				start = mid + 1;
			}
		}
		cout << '#' << t << ' ' << ans << '\n';
	}
	return 0;
}