#include <iostream>

using namespace std;

int R, C, M, King_C = -1;

class shark {
private:
	int r = 0, c = 0, s = 0, d = 0, z = 0, code = -1;
	bool alive = false;
	bool dirty = false;
public:
	static shark** Map;
	shark() {}
	shark(int _r, int _c, int _s, int _d, int _z, int _code) :r(_r), c(_c), s(_s), d(_d), z(_z), code(_code) {
		alive = true;
		Map[r][c] = *this;
	}
	shark(shark& ref) {
		r = ref.r;
		c = ref.c;
		s = ref.s;
		d = ref.d;
		z = ref.z;
		code = ref.code;
		alive = ref.alive;
		dirty = ref.dirty;
	}

	void Move_Up(int distance) {
		if (distance > 0) {
			if (distance > r) {
				int first = r;
				r = 0;
				d = 2;
				Move_Down(distance - first);
			}
			else {
				r -= distance;
			}
		}
	}
	void Move_Down(int distance) {
		if (distance > 0) {
			if (distance > R - 1 - r) {
				int first = r;
				r = R - 1;
				d = 1;
				Move_Up(distance - (R - 1 - first));
			}
			else {
				r += distance;
			}
		}
	}
	void Move_Right(int distance) {
		if (distance > 0) {
			if (distance > C - 1 - c) {
				int first = c;
				c = C - 1;
				d = 4;
				Move_Left(distance - (C - 1 - first));
			}
			else {
				c += distance;
			}
		}
	}
	void Move_Left(int distance) {
		if (distance > 0) {
			if (distance > c) {
				int first = c;
				c = 0;
				d = 3;
				Move_Right(distance - first);
			}
			else {
				c -= distance;
			}
		}
	}

	void Move() {
		int distance = 0;
		if (d == 1 || d == 2) {
			distance = s % (R * 2 - 2);
		}
		else if (d == 3 || d == 4) {
			distance = s % (C * 2 - 2);
		}

		if (d == 1) {
			Move_Up(distance);
		}
		else if (d == 2) {
			Move_Down(distance);
		}
		else if (d == 3) {
			Move_Right(distance);
		}
		else if (d == 4) {
			Move_Left(distance);
		}
		dirty = true;
	}

	void Update() {
		if (dirty) {
			if (Map[r][c].alive) {
				if (code == Map[r][c].code) {
					dirty = false;
				}
				else {
					if (Map[r][c].dirty) {
						shark temp = *this;
						alive = false;
						dirty = false;
						Map[r][c].Update();
						temp.Update();
					}
					else {
						if (z > Map[r][c].z) {
							set_Map();
							alive = false;
							dirty = false;
						}
						else {
							alive = false;
							dirty = false;
						}
					}
				}
			}
			else {
				set_Map();
				alive = false;
				dirty = false;
			}
		}
	}

	void set_Map() {
		Map[r][c].r = r;
		Map[r][c].c = c;
		Map[r][c].s = s;
		Map[r][c].d = d;
		Map[r][c].z = z;
		Map[r][c].alive = true;
		Map[r][c].dirty = false;
		Map[r][c].code = code;
	}

	int get_r() {
		return r;
	}
	int get_c() {
		return c;
	}
	int get_s() {
		return s;
	}
	int get_d() {
		return d;
	}
	int get_z() {
		return z;
	}
	int get_code() {
		return code;
	}
	bool get_alive() {
		return alive;
	}
	void set_alive(bool val) {
		alive = val;
	}
	bool get_dirty() {
		return dirty;
	}
};
shark** shark::Map = NULL;

void King_Move();
int King_Fishing();
void Shark_Move();


int main() {
	int r, c, s, d, z, result = 0;

	cin >> R >> C >> M;

	shark::Map = new shark * [R];
	for (int i = 0; i < R; i++) {
		shark::Map[i] = new shark[C];
	}

	for (int i = 0; i < M; i++) {
		cin >> r >> c >> s >> d >> z;
		shark(r - 1, c - 1, s, d, z, i);
	}

	for (int i = 0; i < C; i++) {
		King_Move();
		result += King_Fishing();
		Shark_Move();
	}

	cout << result;

	for (int i = 0; i < R; i++) {
		delete[]shark::Map[i];
	}
	delete[]shark::Map;

	return 0;
}

void King_Move() {
	King_C++;
}
int King_Fishing() {
	int ret;
	for (int i = 0; i < R; i++) {
		if (shark::Map[i][King_C].get_alive()) {
			ret = shark::Map[i][King_C].get_z();
			shark::Map[i][King_C].set_alive(false);
			return ret;
		}
	}
	return 0;
}
void Shark_Move() {
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			if (shark::Map[i][j].get_alive()) {
				shark::Map[i][j].Move();
			}
		}
	}
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			if (shark::Map[i][j].get_alive()) {
				shark::Map[i][j].Update();
			}
		}
	}
}