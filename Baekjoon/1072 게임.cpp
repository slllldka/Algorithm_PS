/*#include <iostream>
#include <cmath>

using namespace std;

int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	long long x = 0, y = 0, z = 0;
	cin >> x >> y;
	z = 100 * y / x;

	if (z >= 99) {
		cout << -1 << '\n';
	}
	else {
		double answer = ((z + 1) * x - 100 * y) / (double(99 - z));
		cout << int(ceil(answer)) << '\n';
	}
	
	return 0;
}*/

#include <iostream>

using namespace std;

int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	long long x = 0, y = 0, z = 0;
	cin >> x >> y;
	z = 100 * y / x;

	if (z >= 99) {
		cout << -1 << '\n';
		return 0;
	}

	int start = 1;
	int end = 1000000000;
	int ans = -1;
	while (start <= end) {
		int mid = (start + end) / 2;
		if ((100 * (y + mid) / (x + mid)) > z) {
			ans = mid;
			end = mid - 1;
		}
		else {
			start = mid + 1;
		}
	}

	cout << ans << '\n';

	return 0;
}