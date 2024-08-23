#include <iostream>
#include <algorithm>
#include <climits>

using namespace std;

int N;
int hills[1000];

void solve() {
	int minCost = INT32_MAX;
	int minHeight = hills[0], maxHeight = hills[N - 1];
	int start, end;
	int cost;
	if (maxHeight - minHeight <= 17) {
		minCost = 0;
		cout << 0;
		return;
	}

	start = minHeight;
	end = minHeight + 17;
	while (end <= maxHeight) {
		cost = 0;
		for (int i = 0; i < N; i++) {
			if (hills[i] < start && hills[i] < end) {
				cost += (start - hills[i]) * (start - hills[i]);
			}
			
			if (hills[i] > start && hills[i] > end) {
				cost += (end - hills[i]) * (end - hills[i]);
			}
		}

		minCost = minCost < cost ? minCost : cost;
		start++;
		end++;
	}
	cout << minCost;
}

int main() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> hills[i];
	}
	sort(hills, hills + N);
	solve();
	return 0;
}

/*
������ ������ 0���� 100�̹Ƿ� (0,17) ~ (83, 100) ���� Ž���ϸ鼭 �ּ� ����� ���ϸ� �ȴ�.
*/