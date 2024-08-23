#include <iostream>
#include <vector>

using namespace std;

typedef pair<int, int> i2;

int N;
bool map[101][101];
vector<i2> points;

i2 Rotate_Point(i2, i2);
void Dragon_Curve(int, int, int, int);

int main() {
	int x, y, d, g, result = 0;
	for (int i = 0; i < 101; i++) {
		for (int j = 0; j < 101; j++) {
			map[i][j] = false;
		}
	}

	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> x >> y >> d >> g;
		Dragon_Curve(y, x, d, g);
	}

	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			if (map[i][j] && map[i + 1][j] && map[i][j + 1] && map[i + 1][j + 1]) {
				result++;
			}
		}
	}

	cout << result;
}

i2 Rotate_Point(i2 src, i2 target){
	int src_x = src.first;
	int src_y = src.second;
	int target_x = target.first;
	int target_y = target.second;
	int new_x = target_y - src_y + src_x;
	int new_y = -(target_x - src_x) + src_y;

	return i2(new_x, new_y);
}

void Dragon_Curve(int X, int Y, int D, int G) {
	points.clear();
	for (int i = 0; i <= G; i++) {
		if (i == 0) {
			points.push_back(i2(X, Y));
			if (D == 0) {
				points.push_back(i2(X, Y + 1));
			}
			else if (D == 1) {
				points.push_back(i2(X - 1, Y));
			}
			else if (D == 2) {
				points.push_back(i2(X, Y - 1));
			}
			else if (D == 3) {
				points.push_back(i2(X + 1, Y));
			}
		}
		else {
			i2 src = points.back();
			int size = points.size();
			for (int j = size - 2; j >= 0; j--) {
				points.push_back(Rotate_Point(src, points[j]));
			}
		}
	}

	for (int i = 0; i < (int)points.size(); i++) {
		i2 cur = points[i];
		map[cur.first][cur.second] = true;
	}
}
