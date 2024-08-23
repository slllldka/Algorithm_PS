#include <iostream>
#include <utility>
#include <tuple>
#include <cstring>

using namespace std;

typedef pair<int, int> i2;
typedef tuple<int, int, int, int> i4;

int x[4] = { 1, 0, -1, 0 };
int y[4] = { 0, -1, 0, 1 };

int N;
int map[20][20];
int students[401][5];
i2 position[401];
i4 subPos;

void searchPosition(int);
int getSatisfaction();

int main() {
	cin >> N;
	for (int i = 0; i < N * N; i++) {
		for (int j = 0; j < 5; j++) {
			cin >> students[i][j];
		}
		searchPosition(i);
	}

	cout << getSatisfaction() << endl;
	return 0;
}

void searchPosition(int idx) {
	int studentNum = students[idx][0];
	int countLiking = 0, countEmpty = 0, newX = 0, newY = 0;
	int liking = 0, empty = 0, xPos = 0, yPos = 0;
	subPos = i4(-1, -1, N, N);

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (map[i][j] == 0) {
				countEmpty = 0;
				countLiking = 0;
				for (int k = 0; k < 4; k++) {
					newX = i + x[k];
					newY = j + y[k];
					if (newX >= 0 && newX < N && newY >= 0 && newY < N) {
						if ((map[newX][newY] == students[idx][1])
							|| (map[newX][newY] == students[idx][2])
							|| (map[newX][newY] == students[idx][3])
							|| (map[newX][newY] == students[idx][4])) {
							countLiking++;
						}
						else if (map[newX][newY] == 0) {
							countEmpty++;
						}
					}
				}

				tie(liking, empty, xPos, yPos) = subPos;
				if (countLiking > liking) {
					subPos = i4(countLiking, countEmpty, i, j);
				}
				else if (countLiking == liking) {
					if (countEmpty > empty) {
						subPos = i4(countLiking, countEmpty, i, j);
					}
					else if (countEmpty == empty) {
						if (xPos > i) {
							subPos = i4(countLiking, countEmpty, i, j);
						}
						else if (xPos == i) {
							if (yPos > j) {
								subPos = i4(countLiking, countEmpty, i, j);
							}
						}
					}
				}
			}
		}
	}

	map[get<2>(subPos)][get<3>(subPos)] = studentNum;
	position[studentNum] = i2(get<2>(subPos), get<3>(subPos));
}

int getSatisfaction() {
	int studentNum = 0, newX = 0, newY = 0, count = 0, sum = 0;
	for (int i = 0; i < N * N; i++) {
		studentNum = students[i][0];
		count = 0;
		for (int j = 0; j < 4; j++) {
			newX = position[studentNum].first + x[j];
			newY = position[studentNum].second + y[j];
			if (newX >= 0 && newX < N && newY >= 0 && newY < N) {
				if ((map[newX][newY] == students[i][1])
					|| (map[newX][newY] == students[i][2])
					|| (map[newX][newY] == students[i][3])
					|| (map[newX][newY] == students[i][4])) {
					count++;
				}
			}
		}
		switch (count) {
		case 0:
			break;
		case 1:
			sum += 1;
			break;
		case 2:
			sum += 10;
			break;
		case 3:
			sum += 100;
			break;
		case 4:
			sum += 1000;
			break;
		default:
			break;
		}
	}

	return sum;
}