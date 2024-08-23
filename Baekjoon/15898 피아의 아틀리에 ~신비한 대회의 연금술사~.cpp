#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>

#define max(a, b) (((a) > (b)) ? (a) : (b))

using namespace std;

using pic = pair<int, char>;

int N, maxQ;
vector<int> cList;

pic kiln[5][5], test[5][5];
pic material[10][4][4][4];

void copyKilnToTest();
void rotateMaterials();
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int order[3] = {0}, rotate[3] = {0}, xPos[3] = {0}, yPos[3] = {0}, quality = 0;

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			kiln[i][j] = pic(0, 'W');
		}
	}

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 4; k++) {
				for (int m = 0; m < 4; m++) {
					material[i][j][k][m] = pic(0, 0);
				}
			}
		}
	}

	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 4; k++) {
				cin >> material[i][0][j][k].first;
			}
		}
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 4; k++) {
				cin >> material[i][0][j][k].second;
			}
		}
	}

	for (int i = 0; i < N; i++) {
		if ((i >= N - 3) && (i <= N - 1)) {
			cList.push_back(i - (N - 4));
		}
		else {
			cList.push_back(0);
		}
	}

	rotateMaterials();
	do {
		for (int i = 0; i < N; i++) {
			if (cList[i] == 1) {
				order[0] = i;
			}
			else if (cList[i] == 2) {
				order[1] = i;
			}
			else if (cList[i] == 3) {
				order[2] = i;
			}
		}

		for (rotate[0] = 0; rotate[0] < 4; rotate[0]++) {
			for (int xy1 = 0; xy1 < 4; xy1++) {
				xPos[0] = xy1 / 2;
				yPos[0] = xy1 % 2;
				for (rotate[1] = 0; rotate[1] < 4; rotate[1]++) {
					for (int xy2 = 0; xy2 < 4; xy2++) {
						xPos[1] = xy2 / 2;
						yPos[1] = xy2 % 2;
						for (rotate[2] = 0; rotate[2] < 4; rotate[2]++) {
							for (int xy3 = 0; xy3 < 4; xy3++) {
								xPos[2] = xy3 / 2;
								yPos[2] = xy3 % 2;

								copyKilnToTest();
								for (int idx = 0; idx < 3; idx++) {
									for (int x = 0; x < 4; x++) {
										for (int y = 0; y < 4; y++) {
											test[xPos[idx] + x][yPos[idx] + y].first += material[order[idx]][rotate[idx]][x][y].first;
											if (test[xPos[idx] + x][yPos[idx] + y].first < 0) {
												test[xPos[idx] + x][yPos[idx] + y].first = 0;
											}
											else if (test[xPos[idx] + x][yPos[idx] + y].first > 9) {
												test[xPos[idx] + x][yPos[idx] + y].first = 9;
											}

											if (material[order[idx]][rotate[idx]][x][y].second != 'W') {
												test[xPos[idx] + x][yPos[idx] + y].second = material[order[idx]][rotate[idx]][x][y].second;
											}
										}
									}
								}
								
								quality = 0;
								for (int i = 0; i < 5; i++) {
									for (int j = 0; j < 5; j++) {
										if (test[i][j].second == 'R') {
											quality += 7 * test[i][j].first;
										}
										else if (test[i][j].second == 'B') {
											quality += 5 * test[i][j].first;
										}
										else if (test[i][j].second == 'G') {
											quality += 3 * test[i][j].first;
										}
										else if (test[i][j].second == 'Y') {
											quality += 2 * test[i][j].first;
										}
									}
								}
								maxQ = max(maxQ, quality);
							}
						}
					}
				}
			}
		}

	} while (next_permutation(cList.begin(), cList.end()));

	cout << maxQ;

	return 0;
}

void copyKilnToTest() {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			test[i][j] = kiln[i][j];
		}
	}
}

void rotateMaterials() {
	for (int i = 0; i < N; i++) {
		for (int m = 0; m < 3; m++) {
			for (int j = 0; j < 4; j++) {
				for (int k = 0; k < 4; k++) {
					material[i][m + 1][k][3 - j] = material[i][m][j][k];
				}
			}
		}
	}
}