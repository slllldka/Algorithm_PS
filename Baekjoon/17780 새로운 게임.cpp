#include <iostream>
#include <list>
#include <utility>

using namespace std;

using i2 = pair<int, int>;

int map[13][13];
list<i2> piecesMap[13][13];
list<i2>::iterator piecesIter[10];
i2 piecesPos[10];

int N, K;
int xDir[5] = {0, 0, 0, -1, 1 };
int yDir[5] = {0, 1, -1, 0, 0 };

void start() {
	int x, y, newX, newY, d, Turn = 0;
	list<i2>::iterator iter;
	while (true) {
		Turn++;
		if (Turn > 1000) {
			cout << -1;
			return;
		}
		for (int i = 0; i < K; i++) {
			x = piecesPos[i].first;
			y = piecesPos[i].second;
			d = (*piecesIter[i]).second;
			newX = x + xDir[d];
			newY = y + yDir[d];
			iter = piecesIter[i];


			if (x >= 1 && x <= N && y >= 1 && y <= N) {
				if (piecesMap[x][y].size() >= 4) {
					cout << Turn;
					return;
				}
			}
			//cout << i << x << y << '\n';

			if (iter != piecesMap[x][y].begin()) {
				continue;
			}

			if (newX >= 1 && newX <= N && newY >= 1 && newY <= N) {
				if (map[newX][newY] == 0) {
					//white
					piecesMap[newX][newY].splice(piecesMap[newX][newY].end(), piecesMap[x][y], iter, piecesMap[x][y].end());
					while (iter != piecesMap[newX][newY].end()) {
						piecesPos[(*iter).first] = i2(newX, newY);
						iter++;
					}
				}
				else if (map[newX][newY] == 1) {
					//red
					iter = piecesMap[x][y].end();
					advance(iter, -1);
					piecesMap[x][y].reverse();
					piecesMap[newX][newY].splice(piecesMap[newX][newY].end(), piecesMap[x][y]);
					//cout << "red" << newX << newY;
					while (iter != piecesMap[newX][newY].end()) {
						//cout << ' ' << (*iter).first <<' ';
						piecesPos[(*iter).first] = i2(newX, newY);
						iter++;
					}
					//cout << '\n';
				}
				else {
					//blue
					if (d == 1) {
						(*piecesIter[i]).second = 2;
						d = 2;
					}
					else if (d == 2) {
						(*piecesIter[i]).second = 1;
						d = 1;
					}
					else if (d == 3) {
						(*piecesIter[i]).second = 4;
						d = 4;
					}
					else if (d == 4) {
						(*piecesIter[i]).second = 3;
						d = 3;
					}
					newX = x + xDir[d];
					newY = y + yDir[d];
					if (newX >= 1 && newX <= N && newY >= 1 && newY <= N) {
						if (map[newX][newY] == 0) {
							//white
							piecesMap[newX][newY].splice(piecesMap[newX][newY].end(), piecesMap[x][y], iter, piecesMap[x][y].end());
							while (iter != piecesMap[newX][newY].end()) {
								piecesPos[(*iter).first] = i2(newX, newY);
								iter++;
							}
						}
						else if (map[newX][newY] == 1) {
							//red
							iter = piecesMap[x][y].end();
							advance(iter, -1);
							piecesMap[x][y].reverse();
							piecesMap[newX][newY].splice(piecesMap[newX][newY].end(), piecesMap[x][y]);
							//cout << "red" << newX << newY;
							while (iter != piecesMap[newX][newY].end()) {
								//cout << ' ' << (*iter).first << ' ';
								piecesPos[(*iter).first] = i2(newX, newY);
								iter++;
							}
							//cout << '\n';
						}
					}
				}
			}
			else {
				//blue
				if (d == 1) {
					(*piecesIter[i]).second = 2;
					d = 2;
				}
				else if (d == 2) {
					(*piecesIter[i]).second = 1;
					d = 1;
				}
				else if (d == 3) {
					(*piecesIter[i]).second = 4;
					d = 4;
				}
				else if (d == 4) {
					(*piecesIter[i]).second = 3;
					d = 3;
				}
				newX = x + xDir[d];
				newY = y + yDir[d];
				if (newX >= 1 && newX <= N && newY >= 1 && newY <= N) {
					if (map[newX][newY] == 0) {
						//white
						piecesMap[newX][newY].splice(piecesMap[newX][newY].end(), piecesMap[x][y], iter, piecesMap[x][y].end());
						while (iter != piecesMap[newX][newY].end()) {
							piecesPos[(*iter).first] = i2(newX, newY);
							iter++;
						}
					}
					else if (map[newX][newY] == 1) {
						//red
						iter = piecesMap[x][y].end();
						advance(iter, -1);
						piecesMap[x][y].reverse();
						piecesMap[newX][newY].splice(piecesMap[newX][newY].end(), piecesMap[x][y]);
						//cout << "red" << newX << newY;
						while (iter != piecesMap[newX][newY].end()) {
							//cout << ' ' << (*iter).first << ' ';
							piecesPos[(*iter).first] = i2(newX, newY);
							iter++;
						}
						//cout << '\n';
					}
				}
			}

			if (newX >= 1 && newX <= N && newY >= 1 && newY <= N) {
				if (piecesMap[newX][newY].size() >= 4) {
					cout << Turn;
					return;
				}
			}
		}

		/*for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				cout << piecesMap[i][j].size() << ' ';
			}
			cout << '\n';
		}
		cout << '\n';*/
	}
}

int main() {
	int r, c, d;
	cin >> N >> K;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> map[i][j];
		}
	}

	for (int i = 0; i < K; i++) {
		cin >> r >> c >> d;
		piecesMap[r][c].push_back(i2(i, d));
		piecesIter[i] = piecesMap[r][c].end();
		advance(piecesIter[i], -1);
		piecesPos[i] = i2(r, c);
	}

	start();

	/*list<int> l, l2;
	list<int>::iterator iter, iter2;
	for (int i = 0; i < 10; i++) {
		l.push_back(i);
	}
	iter = l.begin();
	iter2 = l.end();
	advance(iter, 3);
	advance(iter2, -1);
	l.reverse();
	cout << (iter2 == l.begin());*/
	return 0;
}