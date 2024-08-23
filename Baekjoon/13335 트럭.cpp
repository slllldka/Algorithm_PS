#include <iostream>
#include <list>
#include <utility>

using namespace std;

typedef pair<int, int> i2;

int n, w, L;
int arr[1001];
list<i2> bridge;

int weightSum();

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> w >> L;
	for (int i = 1; i <= n; i++) {
		cin >> arr[i];
	}

	int idx = 0;
	int sum = 0;
	int time = 0;
	while (true) {
		time++;
		for (list<i2>::iterator iter = bridge.begin(); iter != bridge.end();) {
			(*iter).second--;
			if ((*iter).second == 0) {
				iter = bridge.erase(iter);
			}
			else {
				iter++;
			}
		}
		
		sum = weightSum();
		if (idx >= n && sum == 0) {
			break;
		}

		if (idx < n) {
			if (sum + arr[idx + 1] <= L) {
				bridge.push_back(i2(arr[idx + 1], w));
				idx++;
			}
		}
	}

	cout << time;

	return 0;
}

int weightSum() {
	if (bridge.empty()) {
		return 0;
	}
	else {
		int sum = 0;
		for (list<i2>::iterator iter = bridge.begin(); iter != bridge.end(); iter++) {
			sum += (*iter).first;
		}
		return sum;
	}
}