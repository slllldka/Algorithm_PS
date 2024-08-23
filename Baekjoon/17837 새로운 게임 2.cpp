#include <iostream>
#include <list>
#include <utility>

using namespace std;

typedef pair<int, int> i2;

int N, K;
int board[12][12];
i2 d_arr[4] = { i2(0, 1), i2(0, -1), i2(-1, 0), i2(1, 0) };

list<i2> pieces[12][12];

pair<i2, list<i2>::iterator> find(int);
i2 move(i2, list<i2>::iterator);
i2 white(int, int, int, int, list<i2>::iterator);
i2 red(int, int, int, int, list<i2>::iterator);
i2 blue(int, int, int, int, list<i2>::iterator);
int change_d(int);
int turn();
void print_all();

int main() {
	int r = 0, c = 0, d = 0;
	cin >> N >> K;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> board[i][j];
		}
	}

	for (int i = 1; i <= K; i++) {
		cin >> r >> c >> d;
		pieces[r - 1][c - 1].push_back(i2(i, d));
	}

	for (int i = 1; i <= 1000; i++) {
		if (turn() == 1) {
			cout << i;
			return 0;
		}
	}

	cout << -1;
	return 0;
}

pair<i2, list<i2>::iterator> find(int idx) {
	list<i2>::iterator iter;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			for (iter = pieces[i][j].begin(); iter !=pieces[i][j].end(); iter++) {
				if ((*iter).first == idx) {
					return pair<i2, list<i2>::iterator>(i2(i, j), iter);
				}
			}
		}
	}
}

i2 move(i2 pos, list<i2>::iterator iter) {
	int r = pos.first, c = pos.second, d = (*iter).second;
	i2 direction = d_arr[d - 1];

	r += direction.first;
	c += direction.second;

	if (r < 0 || r >= N || c < 0 || c >= N) {
		r -= direction.first * 2;
		c -= direction.second * 2;
		return blue(r, c, pos.first, pos.second, iter);
	}
	else {
		if (board[r][c] == 0) {
			return white(r, c, pos.first, pos.second, iter);
		}
		else if (board[r][c] == 1) {
			return red(r, c, pos.first, pos.second, iter);
		}
		else if (board[r][c] == 2) {
			r -= direction.first * 2;
			c -= direction.second * 2;
			return blue(r, c, pos.first, pos.second, iter);
		}
	}
}

i2 white(int r, int c, int org_r, int org_c, list<i2>::iterator iter) {
	pieces[r][c].splice(pieces[r][c].end(), pieces[org_r][org_c], iter, pieces[org_r][org_c].end());
	return i2(r, c);
}
i2 red(int r, int c, int org_r, int org_c, list<i2>::iterator iter) {
	list<i2> move_list;
	move_list.splice(move_list.begin(), pieces[org_r][org_c], iter, pieces[org_r][org_c].end());
	move_list.reverse();
	pieces[r][c].splice(pieces[r][c].end(), move_list);
	return i2(r, c);
}
i2 blue(int r, int c, int org_r, int org_c, list<i2>::iterator iter) {
	(*iter).second = change_d((*iter).second);
	if (r < 0 || r >= N || c < 0 || c >= N) {
		return i2(org_r, org_c);
	}
	else {
		if (board[r][c] == 2) {
			return i2(org_r, org_c);
		}
		else if (board[r][c] == 0) {
			return white(r, c, org_r, org_c, iter);
		}
		else if (board[r][c] == 1) {
			return red(r, c, org_r, org_c, iter);
		}
	}
}
int change_d(int d) {
	if (d == 1 || d == 3) {
		return (d + 1);
	}
	else if (d == 2 || d == 4) {
		return (d - 1);
	}
}

int turn() {
	i2 pos = i2(0, 0);
	for (int i = 1; i <= K; i++) {
		//cout << i - 1 << endl;
		//print_all();

		pair<i2, list<i2>::iterator> data = find(i);
		pos = move(data.first, data.second);
		if (pieces[pos.first][pos.second].size() >= 4) {
			return 1;
		}
	}

	return 0;
}

void print_all() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << '<';

			for (i2 data : pieces[i][j]) {
				cout << data.first << '(' << data.second << ')' << ' ';
			}

			cout << '>' << ' ';
		}

		cout << endl;
	}
	cout << endl;
}