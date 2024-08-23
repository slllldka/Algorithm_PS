#include <iostream>
#include <utility>
#include <queue>
#include <tuple>
#include <cstdlib>

#define max(a, b) (((a) > (b)) ? (a) : (b))

using namespace std;

typedef pair<int, int> i2;					//type, map_idx
typedef pair<i2, int> i3;					//type, map_idx, score
typedef tuple<i2, i2, i2, i2, int, int> st;	//pos * 4, total_score, dice_idx

int dice_num[10];
int max_score = 0;

i2 map_part1[19];													// 0
i2 map_special_1[3] = { i2(13, 0), i2(16, 0), i2(19, 0) };			// 1
i2 map_special_2[2] = { i2(22, 0), i2(24, 0) };						// 2
i2 map_special_3[3] = { i2(28, 0), i2(27, 0), i2(26, 0) };			// 3
i2 map_final[4] = { i2(25, 0), i2(30, 0), i2(35, 0), i2(40, 0) };	// 4

i3 move_piece(int, int, int, bool);
void bfs();

int main() {
	for (int i = 0; i < 19; i++) {
		map_part1[i] = i2(2 * (i + 1), 0);
	}


	for (int i = 0; i < 10; i++) {
		cin >> dice_num[i];
	}
	
	bfs();
	

	cout << max_score;

	return 0;
}

i3 move_piece(int type, int idx, int num, bool start) {
	if (num == 0) {
		int score = 0;

		if (type == 0) {
			map_part1[idx].second = 1;
			score = map_part1[idx].first;
		}
		else if (type == 1) {
			map_special_1[idx].second = 1;
			score = map_special_1[idx].first;
		}
		else if (type == 2) {
			map_special_2[idx].second = 1;
			score = map_special_2[idx].first;
		}
		else if (type == 3) {
			map_special_3[idx].second = 1;
			score = map_special_3[idx].first;
		}
		else if (type == 4) {
			map_final[idx].second = 1;
			score = map_final[idx].first;
		}

		return i3(i2(type, idx), score);
	}

	if (type == 0) {
		if (start) {
			map_part1[idx].second = 0;
			if (idx % 5 == 4) {
				if (idx / 5 == 0) {
					return move_piece(1, 0, num - 1, false);
				}
				else if (idx / 5 == 1) {
					return move_piece(2, 0, num - 1, false);
				}
				else if (idx / 5 == 2) {
					return move_piece(3, 0, num - 1, false);
				}
			}
			else {
				if (idx + num < 19) {
					return move_piece(0, idx + num, 0, false);
				}
				else {
					return move_piece(4, 3, num - 19 + idx, false);
				}
			}
		}
		else {
			if (idx + num < 19) {
				return move_piece(0, idx + num, 0, false);
			}
			else {
				return move_piece(4, 3, num - 19 + idx, false);
			}
		}
	}
	else if (type == 1) {
		if (start) {
			map_special_1[idx].second = 0;
		}

		if (idx + num < 3) {
			return move_piece(1, idx + num, 0, false);
		}
		else {
			return move_piece(4, 0, num - 3 + idx, false);
		}
	}
	else if (type == 2) {
		if (start) {
			map_special_2[idx].second = 0;
		}

		if (idx + num < 2) {
			return move_piece(2, idx + num, 0, false);
		}
		else {
			return move_piece(4, 0, num - 2 + idx, false);
		}
	}
	else if (type == 3) {
		if (start) {
			map_special_3[idx].second = 0;
		}

		if (idx + num < 3) {
			return move_piece(3, idx + num, 0, false);
		}
		else {
			return move_piece(4, 0, num - 3 + idx, false);
		}
	}
	else if (type == 4) {
		if (start) {
			map_final[idx].second = 0;
		}

		if (idx + num < 4) {
			return move_piece(4, idx + num, 0, false);
		}
		else {
			//cout << "arrive" << endl;
			return i3(i2(100, 100), 0);
		}
	}
	else {
		cerr << "type_error" << endl;
		exit(0);
	}
}

void bfs() {
	queue<st> q;
	q.push(st(i2(-1, -1), i2(-1, -1), i2(-1, -1), i2(-1, -1), 0, 0));

	while (!q.empty()) {
		bool move_start = false;
		st data = q.front();
		q.pop();

		i2 pos[4] = { get<0>(data), get<1>(data), get<2>(data), get<3>(data) };
		int score = get<4>(data);
		int idx = get<5>(data);

		if (idx >= 10) {
			max_score = max(score, max_score);
			//cout << score << endl;
			continue;
		}

		for (int i = 0; i < 4; i++) {
			if (pos[i].first < 5) {
				i2 temp = pos[i];
				i3 result;
				if (pos[i] == i2(-1, -1)) {
					if (!move_start) {
						move_start = true;
						result = move_piece(0, 0, dice_num[idx] - 1, true);
					}
					else {
						continue;
					}
				}
				else {
					result = move_piece(pos[i].first, pos[i].second, dice_num[idx], true);
				}

				int count = 0;
				for (; count < 4; count++) {
					if (pos[count].first < 5) {
						if ((pos[count].first == result.first.first) && (pos[count].second == result.first.second)) {
							break;
						}
					}
				}

				if (count == 4) {
					pos[i] = result.first;
					q.push(st(pos[0], pos[1], pos[2], pos[3], score + result.second, idx + 1));
					pos[i] = temp;
				}
			}
		}

	}
}


//bfs ?? or algorithm ??