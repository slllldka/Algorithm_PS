#include <iostream>
#include <list>
#include <vector>

using namespace std;

int N, M, arr[49][49], idxArr[49][49];
int x[2500], y[2500];
int dirX[4] = { 0, 1, 0, -1 };
int dirY[4] = { -1, 0, 1, 0 };
int destroyIdx[5] = { 0, 3, 1, 0, 2 };

vector<int> beads;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N >> M;
	int idx = 0, xPos = N / 2, yPos = N / 2;
	x[0] = xPos;
	y[0] = yPos;
	idxArr[xPos][yPos] = 0;
	idx = 1;
	for (int i = 0; i < 2 * N - 1; i++) {
		for (int j = 0; j < i / 2 + 1; j++) {
			xPos += dirX[i % 4];
			yPos += dirY[i % 4];
			if (yPos < 0) {
				break;
			}
			x[idx] = xPos;
			y[idx] = yPos;
			idxArr[xPos][yPos] = idx;
			idx++;
		}
	}
	//cout << "Phase 1\n";

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> arr[i][j];
		}
	}

	beads.emplace_back(0);
	for (int i = 1; i < N * N; i++) {
		if (arr[x[i]][y[i]] == 0) {
			break;
		}
		beads.emplace_back(arr[x[i]][y[i]]);
	}

	int d, s, count = 0, score = 0;
	for (int i = 0; i < M; i++) {
		cin >> d >> s;

		//blizzard
		count = 0;
		d = destroyIdx[d];
		xPos = N / 2;
		yPos = N / 2;
		for (int j = 0; j < s; j++) {
			xPos += dirX[d];
			yPos += dirY[d];
			if ((idxArr[xPos][yPos] - count) < beads.size()) {
				beads.erase(beads.begin() + idxArr[xPos][yPos] - count);
			}
			else {
				break;
			}
			count++;
		}
		//cout << "blizzard\n";

		//explode
		bool exploded = false;
		int recentBead = -1;
		do {
			/*for (int e : beads) {
				cout << e;
			}
			cout << '\n';*/

			exploded = false;
			count = 0;
			recentBead = -1;
			auto iter = beads.begin();
			for (iter = beads.begin(); iter != beads.end();) {
				if (recentBead == *iter) {
					count++;
					iter++;
				}
				else {
					if (count >= 4) {
						exploded = true;
						iter -= count;
						for (int j = 0; j < count; j++) {
							iter = beads.erase(iter);
						}
						score += count * recentBead;
					}
					recentBead = *iter;
					count = 1;
					iter++;
				}
			}

			if (count >= 4) {
				exploded = true;
				iter = beads.end();
				iter -= count;
				for (int j = 0; j < count; j++) {
					iter = beads.erase(iter);
				}
				score += count * recentBead;
			}

			//cout << score << '\n';
		}
		while (exploded);
		//cout << "explode\n";

		//transform
		vector<int> temp;
		temp.emplace_back(0);

		count = 0;
		recentBead = -1;
		for (auto iter = beads.begin(); iter != beads.end();) {
			if (recentBead == *iter) {
				count++;
				iter++;
			}
			else {
				if (recentBead > 0) {
					temp.emplace_back(count);
					temp.emplace_back(recentBead);
					if (temp.size() == N * N) {
						recentBead = -1;
						count = 0;
						break;
					}
				}
				recentBead = *iter;
				count = 1;
				iter++;
			}
		}
		if (recentBead > 0 && count > 0) {
			temp.emplace_back(count);
			temp.emplace_back(recentBead);
		}

		beads = vector<int>(temp);
		//cout << "transform\n";
	}
	cout << score << '\n';

	return 0;
}