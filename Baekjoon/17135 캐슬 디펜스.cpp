#include <iostream>
#include <list>
#include <utility>
#include <tuple>
#include <algorithm>
#include <cmath>

#define max(a, b) (((a) > (b)) ? (a) : (b))

using namespace std;

typedef pair<int, int> i2;
typedef tuple<int, int, bool> i2b;

int N, M, D;
int maxKilledEnemy = 0;

list<int> combiList;

list<i2b> enemyConstList, enemyList;
i2 archer[3];
list<i2b>::iterator nearestEnemy[3];

int getD(i2, i2);

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int input = 0;

	cin >> N >> M >> D;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> input;
			if (input == 1) {
				enemyConstList.push_back(i2b(i, j, true));
			}
		}
	}

	for (int i = 0; i < M; i++) {
		if (i < M - 3) {
			combiList.push_back(0);
		}
		else {
			combiList.push_back(1);
		}
	}

	do {
		int killedEnemy = 0;
		int idx = 0, archerIdx = 0;
		int x = 0, nearX = 0, y = 0, nearY = 0;
		bool valid = false, nearValid = false;
		for (int e : combiList) {
			if (e == 1) {
				archer[archerIdx++] = i2(N, idx);
			}
			idx++;
		}

		enemyList.assign(enemyConstList.begin(), enemyConstList.end());
		while (!enemyList.empty()) {
			//find nearest enemy
			nearestEnemy[0] = enemyList.end();
			nearestEnemy[1] = enemyList.end();
			nearestEnemy[2] = enemyList.end();
			for (list<i2b>::iterator iter = enemyList.begin();
				iter != enemyList.end(); iter++) {
				tie(x, y, valid) = *iter;
				for (int i = 0; i < 3; i++) {
					if (nearestEnemy[i] == enemyList.end()) {
						if (getD(archer[i], i2(x, y)) <= D) {
							nearestEnemy[i] = iter;
						}
					}
					else {
						tie(nearX, nearY, nearValid) = *nearestEnemy[i];
						if (getD(archer[i], i2(x, y)) <= D) {
							if (getD(archer[i], i2(x, y)) < getD(archer[i], i2(nearX, nearY))) {
								nearestEnemy[i] = iter;
							}
							else if (getD(archer[i], i2(x, y)) == getD(archer[i], i2(nearX, nearY))) {
								if (y < nearY) {
									nearestEnemy[i] = iter;
								}
							}
						}
					}
				}
			}

			//check killedEnemy
			for (int i = 0; i < 3; i++) {
				if (nearestEnemy[i] != enemyList.end()) {
					tie(x, y, valid) = *nearestEnemy[i];
					if (valid) {
						killedEnemy++;
						*nearestEnemy[i] = i2b(x, y, false);
					}
				}
			}

			//move, erase enemy
			for (list<i2b>::iterator iter = enemyList.begin()
				; iter != enemyList.end();) {
				tie(x, y, valid) = *iter;
				if (!valid) {
					iter = enemyList.erase(iter);
				}
				else {
					if (x + 1 == N) {
						iter = enemyList.erase(iter);
					}
					else {
						*iter = i2b(x + 1, y, true);
						iter++;
					}
				}
			}
		}

		maxKilledEnemy = max(maxKilledEnemy, killedEnemy);

	} while (next_permutation(combiList.begin(), combiList.end()));

	cout << maxKilledEnemy;
	return 0;
}

int getD(i2 p1, i2 p2) {
	return (int)(abs(p1.first - p2.first) + abs(p1.second - p2.second));
}