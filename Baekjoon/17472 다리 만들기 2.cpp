#include <iostream>
#include <queue>
#include <utility>
#include <tuple>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

using pii = pair<int, int>;
using tiii = tuple<int, int, int>;

int xDir[4] = { 1, 0, -1, 0 };
int yDir[4] = { 0, -1, 0, 1 };

int N, M, islandNum = 0;
int country[10][10];
bool visit[10][10];

queue<pii> q;
queue<tiii> terminals;
map<int, int> bridgesMap;
vector<pii> bridges;

void findIsland();
void findAllBridges();
int getKey(int, int);
bool compare(pii, pii);
int findMinimumBridges();
bool isConnected(vector<int>&);

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> country[i][j];
		}
	}

	findIsland();
	findAllBridges();
	cout << findMinimumBridges();

	return 0;
}

void findIsland() {
	int x = 0, y = 0, newX = 0, newY = 0;
	islandNum = 1;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (!visit[i][j]) {
				visit[i][j] = true;
				if (country[i][j] == 1) {
					country[i][j] = islandNum;
					q = queue<pii>();
					q.push(pii(i, j));
					while (!q.empty()) {
						x = q.front().first;
						y = q.front().second;
						q.pop();
						for (int d = 0; d < 4; d++) {
							newX = x + xDir[d];
							newY = y + yDir[d];
							if (newX >= 0 && newX < N && newY >= 0 && newY < M) {
								if (!visit[newX][newY]) {
									visit[newX][newY] = true;
									if (country[newX][newY] == 1) {
										country[newX][newY] = islandNum;
										q.push(pii(newX, newY));
									}
								}

								if (country[newX][newY] == 0) {
									terminals.push(tiii(x, y, d));
								}
							}
						}
					}
					islandNum++;
				}
			}
		}
	}
	islandNum--;
}

void findAllBridges() {
	int x, y, d, island, len, key;
	while (!terminals.empty()) {
		tie(x, y, d) = terminals.front();
		terminals.pop();

		island = country[x][y];
		len = -1;

		x += xDir[d];
		y += yDir[d];
		len++;
		while ((x >= 0) && (x < N) && (y >= 0) && (y < M)) {
			if (country[x][y] > 0) {
				if (country[x][y] != island) {
					if (len >= 2) {
						key = getKey(island, country[x][y]);
						if (!bridgesMap.insert({ key, len }).second) {
							if (bridgesMap[key] > len) {
								bridgesMap[key] = len;
							}
						}
					}
				}
				break;
			}
			x += xDir[d];
			y += yDir[d];
			len++;
		}
	}
	for (auto iter = bridgesMap.begin(); iter != bridgesMap.end(); iter++) {
		//cout << (*iter).first << ' ' << (*iter).second << '\n';
		bridges.push_back((*iter));
	}
	sort(bridges.begin(), bridges.end(), compare);
}

int getKey(int s, int e) {
	if (s >= e) {
		return (10 * e + s);
	}
	else {
		return (10 * s + e);
	}
}

bool compare(pii a, pii b) {
	return (a.second < b.second);
}

int findMinimumBridges() {
	vector<int> check;
	int minLen = 0, start, end, count = 1, temp;
	for (int i = 0; i <= islandNum; i++) {
		check.push_back(0);
	}

	for (pii bridge : bridges) {
		start = bridge.first / 10;
		end = bridge.first - start * 10;
		//cout << start << ' ' << end << '\n';
		if (check[start] * check[end] == 0) {
			if (check[start] == 0 && check[end] == 0) {
				//cout << "1?" << '\n';
				check[start] = count;
				check[end] = count;
				count++;
			}
			else if (check[start] == 0 && check[end] > 0) {
				//cout << "2?" << '\n';
				check[start] = check[end];
			}
			else if (check[start] > 0 && check[end] == 0) {
				//cout << "3?" << '\n';
				check[end] = check[start];
			}
			minLen += bridge.second;
		}
		else {
			if (check[start] != check[end]) {
				//cout << "4?" << '\n';
				temp = check[end];
				for (int i = 1; i <= islandNum; i++) {
					if (check[i] == temp) {
						check[i] = check[start];
					}
				}
				minLen += bridge.second;
			}
		}

		if (isConnected(check)) {
			return minLen;
		}
	}

	return -1;
}

bool isConnected(vector<int>& check) {
	int start = check[1];
	if (start == 0) {
		return false;
	}

	for (int i = 2; i <= islandNum; i++) {
		if (check[i] != start) {
			return false;
		}
	}
	return true;
 }