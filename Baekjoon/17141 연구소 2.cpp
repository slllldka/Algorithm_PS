#include <iostream>
#include <queue>
#include <tuple>
#include <vector>
#include <algorithm>
#include <utility>
#include <cstring>

using namespace std;

typedef pair<int, int> i2;
typedef tuple<int, int, int> i3;

int xVec[4] = { 1, 0, -1, 0 };
int yVec[4] = { 0, 1, 0, -1 };

int N, M, E;
int map[50][50];

queue<i3> q;

vector<int> combinationList;
vector<i2> virusSpaceList;

bool visit[50][50];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	E = 0;
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
			if (map[i][j] == 0) {
				E++;
			}
			else if (map[i][j] == 2) {
				virusSpaceList.push_back(i2(i, j));
			}
		}
	}

	if ((int)virusSpaceList.size() < M) {
		M = (int)virusSpaceList.size();
	}

	if (M == 0) {
		cout << -1;
		return 0;
	}

	E += (virusSpaceList.size() - M);
	if (E == 0) {
		cout << 0;
		return 0;
	}

	for (int i = 0; i < (int)virusSpaceList.size(); i++) {
		if (i < (int)virusSpaceList.size() - M) {
			combinationList.push_back(0);
		}
		else {
			combinationList.push_back(1);
		}
	}

	int minTime = -1;
	do {
		int filledSpace = 0;
		q = queue<i3>();
		memset(visit, false, sizeof(visit));

		for (int i = 0; i < (int)combinationList.size(); i++) {
			if (combinationList[i] == 1) {
				q.push(i3(virusSpaceList[i].first, virusSpaceList[i].second, 0));
				visit[virusSpaceList[i].first][virusSpaceList[i].second] = true;
			}
		}

		while (!q.empty()) {
			int x, y, t;
			tie(x, y, t) = q.front();
			q.pop();

			int newX, newY;
			for (int j = 0; j < 4; j++) {
				newX = x + xVec[j];
				newY = y + yVec[j];
				if (newX >= 0 && newX < N && newY >= 0 && newY < N) {
					if (!visit[newX][newY] && (map[newX][newY] != 1)) {
						visit[newX][newY] = true;
						filledSpace++;

						if (filledSpace == E) {
							if (minTime == -1) {
								minTime = t + 1;
							}
							else {
								minTime = minTime < (t + 1) ? minTime : (t + 1);
							}
						}
						else {
							q.push(i3(newX, newY, t + 1));
						}
					}
				}
			}
		}

	} while (next_permutation(combinationList.begin(), combinationList.end()));
	
	cout << minTime;

	return 0;
}