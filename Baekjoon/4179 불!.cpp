#include <iostream>
#include <queue>
#include <tuple>

using namespace std;

typedef tuple<int, int, int> i3;

int x[4] = { 1, 0, -1, 0 };
int y[4] = { 0, -1, 0, 1 };

int R, C;
char map[1000][1000];
bool check[1000][1000];

queue<i3> queueFire, queueJH;

int BFS();

int main() {
	string input = "";
	cin >> R >> C;
	for (int i = 0; i < R; i++) {
		cin >> input;
		for (int j = 0; j < C; j++) {
			check[i][j] = false;
			map[i][j] = input[j];
			if (map[i][j] == 'J') {
				queueJH.push(i3(0, i, j));
				map[i][j] = '.';
				check[i][j] = true;
			}
			else if (map[i][j] == 'F') {
				queueFire.push(i3(0, i, j));
			}
		}
	}

	int result = BFS();
	if (result == -1) {
		cout << "IMPOSSIBLE";
	}
	else {
		cout << result;
	}
	return 0;
}

int BFS() {
	int level = 0;
	while (!queueJH.empty()) {
		if (!queueFire.empty()) {
			i3 fire = queueFire.front();
			int fireLevel = get<0>(fire);
			int fireX = get<1>(fire);
			int fireY = get<2>(fire);
			if (fireLevel == level) {
				for (int i = 0; i < 4; i++) {
					if (((fireX + x[i]) >= 0 && (fireX + x[i]) < R)
						&& ((fireY + y[i]) >= 0 && (fireY + y[i]) < C)) {
						if (map[fireX + x[i]][fireY + y[i]] == '.') {
							map[fireX + x[i]][fireY + y[i]] = 'F';
							queueFire.push(i3(fireLevel + 1, fireX + x[i], fireY + y[i]));
						}
					}
				}

				queueFire.pop();
			}
			else {
				while (!queueJH.empty()) {
					i3 jh = queueJH.front();
					int jhLevel = get<0>(jh);
					int jhX = get<1>(jh);
					int jhY = get<2>(jh);
					if (jhLevel == level) {
						for (int i = 0; i < 4; i++) {
							if (((jhX + x[i]) >= 0 && (jhX + x[i]) < R)
								&& ((jhY + y[i]) >= 0 && (jhY + y[i]) < C)) {
								if (map[jhX + x[i]][jhY + y[i]] == '.') {
									if (check[jhX + x[i]][jhY + y[i]] == false) {
										queueJH.push(i3(jhLevel + 1, jhX + x[i], jhY + y[i]));
										check[jhX + x[i]][jhY + y[i]] = true;
									}
								}
							}
							else {
								return (level + 1);
							}
						}
						queueJH.pop();
					}
					else {
						break;
					}
				}

				level++;
			}
		}
		else {
			while (!queueJH.empty()) {
				i3 jh = queueJH.front();
				int jhLevel = get<0>(jh);
				int jhX = get<1>(jh);
				int jhY = get<2>(jh);
				if (jhLevel == level) {
					for (int i = 0; i < 4; i++) {
						if (((jhX + x[i]) >= 0 && (jhX + x[i]) < R)
							&& ((jhY + y[i]) >= 0 && (jhY + y[i]) < C)) {
							if (map[jhX + x[i]][jhY + y[i]] == '.') {
								if (check[jhX + x[i]][jhY + y[i]] == false) {
									queueJH.push(i3(jhLevel + 1, jhX + x[i], jhY + y[i]));
									check[jhX + x[i]][jhY + y[i]] = true;
								}
							}
						}
						else {
							return (level + 1);
						}
					}
					queueJH.pop();
				}
				else {
					break;
				}
			}

			level++;
		}
	}

	return -1;
}