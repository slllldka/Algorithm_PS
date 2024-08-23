#include <iostream>
#include <cmath>
#include <cstring>

#define min(a, b) (((a) < (b)) ? (a) : (b))
#define max(a, b) (((a) > (b)) ? (a) : (b))

using namespace std;

int x[4] = { 0, -1, 0, 1 };
int y[4] = { -1, 0, 1, 0 };

int N, K;
int arr1[100], arr2[100][100], controlNum[100][100];

int findMinMaxDifference();
void controlFishNum(int, int);
void serialize(int, int);
void printArr1();
void printArr2(int, int);

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> N >> K;
	for (int i = 0; i < N; i++) {
		cin >> arr1[i];
	}

	int sideLen = -1, dirIdx = -1;
	int xPos = -1, yPos = -1;
	int xLen = -1, yLen = -1;
	int tidyingNum = 0;
	while (true) {
		if (findMinMaxDifference() <= K) {
			break;
		}

		//add 1 to minimum
		int minNum = 10001;
		for (int i = 0; i < N; i++) {
			minNum = min(minNum, arr1[i]);
		}
		for (int i = 0; i < N; i++) {
			if (minNum == arr1[i]) {
				arr1[i]++;
			}
		}

		//levitation ver1
		memset(arr2, 0, sizeof(arr2));
		sideLen = (int)sqrt(N);
		if (sideLen * (sideLen + 1) <= N) {
			dirIdx = (sideLen % 2) * 2 + 1;
			xPos = sideLen / 2;
			yPos = sideLen / 2;
			xLen = sideLen + 1;
			yLen = N - sideLen * sideLen;
		}
		else {
			dirIdx = (sideLen % 2) * 2;
			if (sideLen % 2 == 0) {
				xPos = sideLen / 2 - 1;
				yPos = sideLen / 2;
			}
			else {
				xPos = sideLen / 2;
				yPos = sideLen / 2;
			}
			xLen = sideLen;
			yLen = N - sideLen * (sideLen - 1);
		}

		int count = 0;
		arr2[xPos][yPos] = arr1[count++];
		for (int i = 1; i <= sideLen - 1; i++) {
			for (int k = 0; k < 2; k++) {
				for (int j = 0; j < i; j++) {
					xPos += x[dirIdx];
					yPos += y[dirIdx];
					arr2[xPos][yPos] = arr1[count++];
				}
				dirIdx = (dirIdx + 3) % 4;
			}
		}
		for (int i = 0; i < sideLen - 1; i++) {
			xPos += x[dirIdx];
			yPos += y[dirIdx];
			arr2[xPos][yPos] = arr1[count++];
		}

		if (yPos == 0) {
			xPos++;
		}
		else {
			yPos++;
		}
		for (; count < N; count++) {
			arr2[xPos][yPos++] = arr1[count];
		}

		//control Num
		controlFishNum(xLen, yLen);

		//serialization
		serialize(xLen, yLen);
		
		//levitation ver2
		memset(arr2, 0, sizeof(arr2));
		xLen = 4;
		yLen = N / 4;
		count = 0;
		for (int i = 0; i < yLen; i++) {
			arr2[2][yLen - i - 1] = arr1[count++];
		}
		for (int i = 0; i < yLen; i++) {
			arr2[1][i] = arr1[count++];
		}
		for (int i = 0; i < yLen; i++) {
			arr2[0][yLen - i - 1] = arr1[count++];
		}
		for (int i = 0; i < yLen; i++) {
			arr2[3][i] = arr1[count++];
		}

		//control Num
		controlFishNum(xLen, yLen);

		//serialization
		serialize(xLen, yLen);

		tidyingNum++;
	}

	cout << tidyingNum;

	return 0;
}

int findMinMaxDifference() {
	int minNum = 10001, maxNum = 0;
	for (int i = 0; i < N; i++) {
		minNum = min(minNum, arr1[i]);
		maxNum = max(maxNum, arr1[i]);
	}

	return (maxNum - minNum);
}

void controlFishNum(int xLen, int yLen) {
	int newX = 0, newY = 0, d = 0;
	memset(controlNum, 0, sizeof(controlNum));
	for (int i = 0; i < xLen; i++) {
		for (int j = 0; j < yLen; j++) {
			if (arr2[i][j] != 0) {
				for (int k = 2; k < 4; k++) {
					newX = i + x[k];
					newY = j + y[k];
					if (newX >= 0 && newX < xLen && newY >= 0 && newY < yLen) {
						if (arr2[newX][newY] != 0) {
							if (arr2[i][j] > arr2[newX][newY]) {
								d = (arr2[i][j] - arr2[newX][newY]) / 5;
								controlNum[i][j] -= d;
								controlNum[newX][newY] += d;
							}
							else if (arr2[i][j] < arr2[newX][newY]) {
								d = (arr2[newX][newY] - arr2[i][j]) / 5;
								controlNum[i][j] += d;
								controlNum[newX][newY] -= d;
							}
						}
					}
				}
			}
		}
	}
	for (int i = 0; i < xLen; i++) {
		for (int j = 0; j < yLen; j++) {
			arr2[i][j] += controlNum[i][j];
		}
	}
}
void serialize(int xLen, int yLen) {
	int count = 0;
	for (int i = 0; i < yLen; i++) {
		for (int j = xLen - 1; j >= 0; j--) {
			if (arr2[j][i] != 0) {
				arr1[count++] = arr2[j][i];
			}
		}
	}
}
void printArr1() {
	for (int i = 0; i < N; i++) {
		cout << arr1[i] << ' ';
	}
	cout << '\n';
}
void printArr2(int xLen, int yLen) {
	for (int i = 0; i < xLen; i++) {
		for (int j = 0; j < yLen; j++) {
			cout << arr2[i][j] << ' ';
		}
		cout << '\n';
	}
}