#include <iostream>
#include <tuple>
#include <queue>

using namespace std;

typedef tuple<int, int, int> i3;

int x[4] = { 1, 0, -1, 0 };
int y[4] = { 0, -1, 0, 1 };

int T, W, H;
char map[1000][1000];
bool checkSG[1000][1000];

queue<i3> queueFire, queueSG;

int BFS();
int moveSG(int*);

int main() {
	int time = 0;
	string input = "";
	cin >> T;
	for (int testCase = 0; testCase < T; testCase++) {
		cin >> H >> W;
		queueFire = queue<i3>();
		queueSG = queue<i3>();
		for (int i = 0; i < W; i++) {
			cin >> input;
			for (int j = 0; j < H; j++) {
				map[i][j] = input[j];
				checkSG[i][j] = false;
				if (map[i][j] == '*') {
					queueFire.push(i3(0, i, j));
				}
				else if (map[i][j] == '@') {
					queueSG.push(i3(0, i, j));
					map[i][j] = '.';
					checkSG[i][j] = true;
				}
			}
		}
		
		time = BFS();
		if (time == -1) {
			cout << "IMPOSSIBLE" << endl;
		}
		else {
			cout << time << endl;
		}
	}
}

int BFS() {
	int level = 0;
	int ret = 0;
	while (!queueSG.empty()) {
		if (queueFire.empty()) {
			ret = moveSG(&level);
			if (ret != -1) {
				return ret;
			}
		}
		else {
			i3 data = queueFire.front();
			int fireLevel = get<0>(data);
			int fireX = get<1>(data);
			int fireY = get<2>(data);
			
			if (fireLevel == level) {
				queueFire.pop();
				int newX = 0, newY = 0;
				for (int i = 0; i < 4; i++) {
					newX = fireX + x[i];
					newY = fireY + y[i];
					if ((newX >= 0) && (newX < W) && (newY >= 0) && (newY < H)) {
						if (map[newX][newY] == '.') {
							map[newX][newY] = '*';
							queueFire.push(i3(fireLevel + 1, newX, newY));
						}
					}
				}
			}
			else {
				ret = moveSG(&level);
				if (ret != -1) {
					return ret;
				}
			}
		}
	}

	return -1;
}

int moveSG(int* level) {
	while (!queueSG.empty()) {
		i3 data = queueSG.front();
		int sgLevel = get<0>(data);
		int sgX = get<1>(data);
		int sgY = get<2>(data);
		if (sgLevel == *level) {
			queueSG.pop();
			int newX = 0, newY = 0;
			for (int i = 0; i < 4; i++) {
				newX = sgX + x[i];
				newY = sgY + y[i];
				if ((newX >= 0) && (newX < W) && (newY >= 0) && (newY < H)) {
					if (map[newX][newY] == '.') {
						if (checkSG[newX][newY] == false) {
							checkSG[newX][newY] = true;
							queueSG.push(i3(sgLevel + 1, newX, newY));
						}
					}
				}
				else {
					return (*level) + 1;
				}
			}
		}
		else {
			*level = (*level) + 1;
			return -1;
		}
	}

	return -1;
}