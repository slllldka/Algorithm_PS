#include <iostream>

#define min(a, b) (((a) < (b)) ? (a) : (b))

using namespace std;

int arr[10][10], paperLeft[6] = {0, 5, 5, 5, 5, 5};
int N = 0, currentN = 0, minNum = 26;

void findValidPaper(int, int, int, int);

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			cin >> arr[i][j];
			if (arr[i][j] == 1) {
				N++;
			}
		}
	}

	currentN = N;
	findValidPaper(0, 5, 0, 0);
	if (minNum == 26) {
		cout << -1;
	}
	else {
		cout << minNum;
	}
	
	return 0;
}

void findValidPaper(int num, int recentP, int startX, int startY) {
	bool valid = true;
	//cout << num << '\n';
	
	if (currentN == 0) {
		minNum = min(minNum, num);
		return;
	}
	else if (num >= minNum) {
		return;
	}

	int maxPaper = 0;
	for (int p = recentP; p >= 1; p--) {
		if ((currentN >= p * p) && (paperLeft[p] > 0) ) {
			maxPaper = 0;
			for (int i = p; i >= 1; i--) {
				maxPaper += paperLeft[i] * i * i;
			}

			if (maxPaper < currentN) {
				break;
			}
			for (int i = 0; i < 11 - p; i++) {
				for (int j = 0; j < 11 - p; j++) {
					if ((N != currentN) && (p == recentP) && (i == 0) && (j == 0)) {
						i = startX;
						j = startY;
						continue;
					}
					valid = true;
					for (int x = 0; x < p; x++) {
						for (int y = 0; y < p; y++) {
							if (arr[i + x][j + y] == 0) {
								valid = false;
								break;
							}
						}
					}

					if (valid) {
						for (int x = 0; x < p; x++) {
							for (int y = 0; y < p; y++) {
								arr[i + x][j + y] = 0;
							}
						}
						currentN -= p * p;
						paperLeft[p]--;
						findValidPaper(num + 1, p, i, j);
						for (int x = 0; x < p; x++) {
							for (int y = 0; y < p; y++) {
								arr[i + x][j + y] = 1;
							}
						}
						currentN += p * p;
						paperLeft[p]++;
					}
				}
			}
		}
	}
}