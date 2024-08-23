#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>

#define min(a, b) (a) < (b) ? (a) : (b)

using namespace std;

int N;
int minDiff = 1000;
int num[11];
int graph[11][10];
bool electionDistrict[11];
bool firstVisit[11], secondVisit[11];
vector<int> cList;

void searchGraph(bool, bool(&visit)[11], int);

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int input, firstNum = 0, secondNum = 0, firstSum = 0, secondSum = 0, diff = 0;
	bool firstConn = false, secondConn = false;

	cin >> N;
	
	for (int i = 1; i <= N; i++) {
		cin >> num[i];
	}

	for (int i = 1; i <= N; i++) {
		cin >> input;
		for (int j = 0; j < input; j++) {
			cin >> graph[i][j];
		}
	}

	for (int i = 1; i <= N / 2; i++) {
		firstNum = i;
		secondNum = N - i;
		cList.clear();
		for (int j = 0; j < firstNum; j++) {
			cList.push_back(0);
		}
		for (int j = 0; j < secondNum; j++) {
			cList.push_back(1);
		}

		do {
			firstConn = true;
			secondConn = true;
			firstSum = 0;
			secondSum = 0;
			memset(electionDistrict, false, sizeof(electionDistrict));
			memset(firstVisit, false, sizeof(firstVisit));
			memset(secondVisit, false, sizeof(secondVisit));
			for (int j = 0; j < N; j++) {
				if (cList[j] == 0) {
					electionDistrict[j + 1] = true;
					firstSum += num[j + 1];
				}
				else {
					electionDistrict[j + 1] = false;
					secondSum += num[j + 1];
				}
			}

			for (int j = 1; j <= N; j++) {
				if (electionDistrict[j]) {
					searchGraph(true, firstVisit, j);
					for (int k = 1; k <= N; k++) {
						if (electionDistrict[k] && !firstVisit[k]) {
							firstConn = false;
							break;
						}
					}
					break;
				}
			}
			for (int j = 1; j <= N; j++) {
				if (!electionDistrict[j]) {
					searchGraph(false, secondVisit, j);
					for (int k = 1; k <= N; k++) {
						if (!electionDistrict[k] && !secondVisit[k]) {
							secondConn = false;
							break;
						}
					}
					break;
				}
			}

			if (firstConn && secondConn) {
				diff = firstSum > secondSum
					? (firstSum - secondSum) : (secondSum - firstSum);
				minDiff = min(minDiff, diff);
			}

		} while (next_permutation(cList.begin(), cList.end()));
	}

	if (minDiff == 1000) {
		cout << -1;
	}
	else {
		cout << minDiff;
	}

	return 0;
}

void searchGraph(bool which, bool(&visit)[11], int node) {
	visit[node] = true;
	for (int i = 0; i < N; i++) {
		if (graph[node][i] != 0) {
			if (electionDistrict[graph[node][i]] == which) {
				if (!visit[graph[node][i]]) {
					searchGraph(which, visit, graph[node][i]);
				}
			}
		}
		else {
			return;
		}
	}
}