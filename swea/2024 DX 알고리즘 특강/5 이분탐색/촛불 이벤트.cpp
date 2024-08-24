#include <iostream>

using namespace std;

int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	bool exist;
	long long T, N, start, mid, end, sum;
	cin >> T;
	for (int t = 1; t <= T; t++) {
		cin >> N;
		start = 1;
		end = 1414213561;
		exist = false;
		while (start <= end) {
			mid = (start + end) / 2;
			sum = mid * (mid + 1) / 2;
			if (N == sum) {
				exist = true;
				break;
			}
			else if (N < sum) {
				end = mid - 1;
			}
			else {
				start = mid + 1;
			}
		}

		cout << '#' << t << ' ';
		if (exist) {
			cout << mid << '\n';
		}
		else {
			cout << -1 << '\n';
		}
	}
	return 0;
}