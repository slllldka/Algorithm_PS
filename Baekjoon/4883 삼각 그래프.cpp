#include <iostream>

#define min2(a, b) (((a) < (b)) ? (a) : (b))
#define min3(a, b, c) ((min2(a, b) < (c)) ? min2(a, b) : (c))
#define min4(a, b, c, d) ((min2(a, b) < min2(c, d)) ? min2(a, b) : min2(c, d))

using namespace std;

int N;
long long cost[100000][3];
long long minCost[100000][3];


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	for (int T = 1;; T++) {
		cin >> N;
		if (N == 0) {
			break;
		}

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < 3; j++) {
				cin >> cost[i][j];
			}
		}

		minCost[0][0] = 1000;
		minCost[0][1] = cost[0][1];
		minCost[0][2] = cost[0][1] + cost[0][2];

		for (int i = 1; i < N; i++) {
			minCost[i][0] = min2(minCost[i - 1][0], minCost[i - 1][1]) + cost[i][0];
			minCost[i][1] = min4(minCost[i - 1][0], minCost[i - 1][1]
				, minCost[i - 1][2], minCost[i][0]) + cost[i][1];
			minCost[i][2] = min3(minCost[i - 1][1], minCost[i - 1][2], minCost[i][1])
				+ cost[i][2];
		}


		cout << T <<". " << minCost[N - 1][1] << '\n';
	}

	return 0;
}