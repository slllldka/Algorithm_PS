#include <iostream>

#define min(a,b) (((a) < (b)) ? (a) : (b))

using namespace std;

int N, cost[1000][3], minCost[3], minTemp[3];

int main() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> cost[i][0] >> cost[i][1] >> cost[i][2];
	}

	for (int i = 0; i < N; i++) {
		if (i == 0) {
			minCost[0] = cost[0][0];
			minCost[1] = cost[0][1];
			minCost[2] = cost[0][2];
		}
		else {
			int first, second;
			first = minCost[1] + cost[i][0];
			second = minCost[2] + cost[i][0];
			minTemp[0] = min(first, second);
			first = minCost[0] + cost[i][1];
			second = minCost[2] + cost[i][1];
			minTemp[1] = min(first, second);
			first = minCost[0] + cost[i][2];
			second = minCost[1] + cost[i][2];
			minTemp[2] = min(first, second);

			minCost[0] = minTemp[0];
			minCost[1] = minTemp[1];
			minCost[2] = minTemp[2];
		}
	}

	cout << min(min(minCost[0], minCost[1]), minCost[2]);

	return 0;
}