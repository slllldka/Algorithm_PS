#include <iostream>
#include <utility>
#include <algorithm>

#define max(a, b) (((a) > (b)) ? (a) : (b))

using namespace std;

using pii = pair<int, int>;

int currentStartDay = 31 + 28 + 1;
int LastDay = 31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + 30;
int dayPerMonth[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
pii flowers[100000];

int dayCoordinate(int month, int day) {
	int ret = 0;
	for (int i = 1; i < month; i++) {
		ret += dayPerMonth[i];
	}
	ret += day;

	return ret;
}

bool compare(pii e1, pii e2) {
	return (e1.first < e2.first);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int N, month, day, startDay, endDay;
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> month >> day;
		startDay = dayCoordinate(month, day);
		cin >> month >> day;
		endDay = dayCoordinate(month, day) - 1;
		flowers[i] = pii(startDay, endDay);
	}

	sort(flowers, flowers + N, compare);

	int num = 0, maxEndDay = 0;
	for (int i = 0; i < N;) {
		if (flowers[i].first <= currentStartDay) {
			maxEndDay = max(maxEndDay, flowers[i].second);
			i++;
		}
		else {
			if (maxEndDay > 0) {
				num++;
				if (maxEndDay >= LastDay) {
					cout << num;
					return 0;
				}
				currentStartDay = maxEndDay + 1;
				maxEndDay = 0;
			}
			else {
				cout << 0;
				return 0;
			}
		}
	}

	if (maxEndDay >= LastDay) {
		cout << (num + 1);
	}
	else {
		cout << 0;
	}
	return 0;
}