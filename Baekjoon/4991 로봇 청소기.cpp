#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
#include <tuple>
#include <utility>
#include <algorithm>

#define min(a, b) (((a) < (b)) ? (a) : (b))

using namespace std;

typedef pair<int, int> i2;
typedef tuple<int, int, int> i3;

int xVec[4] = { 1, 0, -1, 0 };
int yVec[4] = { 0, 1, 0, -1 };

int w, h;
char map[20][21];
int dist[11][11];
bool visit[20][20];

i2 dirtySpace[11];
vector<int> order;
vector<int> combinationList;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	while (true) {
		int dirtyNum = 0, tempDist = 0, minDist = 0;
		i2 robot = i2(0, 0), start = i2(0, 0), end = i2(0, 0);
		order.clear();
		combinationList.clear();
		memset(dist, 0, sizeof(dist));

		cin >> w >> h;
		if (w == 0 && h == 0) {
			break;
		}

		for (int i = 0; i < h; i++) {
			cin >> map[i];
			for (int j = 0; j < w; j++) {
				if (map[i][j] == '*') {
					dirtyNum++;
					dirtySpace[dirtyNum] = i2(i, j);
					order.push_back(dirtyNum);
				}
				else if (map[i][j] == 'o') {
					robot = i2(i, j);
				}
			}
		}

		for (int i = 0; i < dirtyNum; i++) {
			if (i < dirtyNum - 2) {
				combinationList.push_back(0);
			}
			else {
				combinationList.push_back(1);
			}
		}

		//distance between two points
		start = robot;
		for (int i = 1; i <= dirtyNum; i++) {
			queue<i3> q;
			tempDist = -1;
			end = dirtySpace[i];
			memset(visit, false, sizeof(visit));
			q.push(i3(start.first, start.second, 0));
			visit[start.first][start.second] = true;
			while (!q.empty()) {
				int x, y, d, newX, newY;
				tie(x, y, d) = q.front();
				q.pop();
				for (int j = 0; j < 4; j++) {
					newX = x + xVec[j];
					newY = y + yVec[j];
					if (newX >= 0 && newX < h && newY >= 0 && newY < w) {
						if (!visit[newX][newY]) {
							if (map[newX][newY] != 'x') {
								if (i2(newX, newY) == end) {
									tempDist = d + 1;
									q = queue<i3>();
									break;
								}
								else {
									visit[newX][newY] = true;
									q.push(i3(newX, newY, d + 1));
								}
							}
						}
					}
				}
			}

			dist[0][i] = tempDist;
			dist[i][0] = tempDist;
		}

		do {
			int startIdx = 0, endIdx = 0;
			bool savedStart = false;
			for (int i = 0; i < dirtyNum; i++) {
				if (combinationList[i] == 1) {
					if (!savedStart) {
						savedStart = true;
						startIdx = order[i];
						start = dirtySpace[order[i]];
					}
					else {
						endIdx = order[i];
						end = dirtySpace[order[i]];
					}
				}
			}

			queue<i3> q;
			tempDist = -1;
			memset(visit, false, sizeof(visit));
			q.push(i3(start.first, start.second, 0));
			visit[start.first][start.second] = true;
			while (!q.empty()) {
				int x, y, d, newX, newY;
				tie(x, y, d) = q.front();
				q.pop();
				for (int j = 0; j < 4; j++) {
					newX = x + xVec[j];
					newY = y + yVec[j];
					if (newX >= 0 && newX < h && newY >= 0 && newY < w) {
						if (!visit[newX][newY]) {
							if (map[newX][newY] != 'x') {
								if (i2(newX, newY) == end) {
									tempDist = d + 1;
									q = queue<i3>();
									break;
								}
								else {
									visit[newX][newY] = true;
									q.push(i3(newX, newY, d + 1));
								}
							}
						}
					}
				}
			}

			dist[startIdx][endIdx] = tempDist;
			dist[endIdx][startIdx] = tempDist;


		} while (next_permutation(combinationList.begin(), combinationList.end()));


		// get min distance
		minDist = 2147483647;
		do {
			bool canVisit = true;
			tempDist = 0;
			for (int i = 0; i < dirtyNum; i++) {
				if (i == 0) {
					if (dist[0][order[i]] == -1) {
						canVisit = false;
						break;
					}
					else {
						tempDist += dist[0][order[i]];
					}
				}
				else {
					if (dist[order[i - 1]][order[i]] == -1) {
						canVisit = false;
						break;
					}
					else {
						tempDist += dist[order[i - 1]][order[i]];
					}
				}
			}
			
			if (canVisit) {
				minDist = min(minDist, tempDist);
			}
		} while (next_permutation(order.begin(), order.end()));

		if (minDist == 2147483647) {
			cout << -1 << '\n';
		}
		else {
			cout << minDist << '\n';
		}
	}

	return 0;
}

