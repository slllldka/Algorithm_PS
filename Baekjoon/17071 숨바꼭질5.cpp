#include <iostream>
#include <queue>
#include <utility>

using namespace std;

typedef pair<int, int> i2;

int N, K;
int Time = 1;

queue<i2> q;
int check[500001][2];

int moveSister();

int main() {
	cin >> N >> K;
	if (N == K) {
		cout << 0;
	}
	else {
		cout << moveSister();
	}
	return 0;
}

int moveSister() {
	q.push(i2(N, 1));
	while (!q.empty()) {
		i2 data = q.front();
		int sister = data.first;
		int time = data.second;
		q.pop();

		if (time > Time) {
			int brother = K + Time * (Time + 1) / 2;
			if (brother > 500000) {
				return -1;
			}
			else {
				if (Time % 2 == 0) {
					if (check[brother][0] != 0) {
						if (Time >= check[brother][0]) {
							return Time;
						}
					}
				}
				else {
					if (check[brother][1] != 0) {
						if (Time >= check[brother][1]) {
							return Time;
						}
					}
				}
			}
			Time++;
		}

		int newSister = 0;
		//-1
		newSister = sister - 1;
		if (newSister >= 0 && newSister <= 500000) {
			if (time % 2 == 0) {
				if (check[newSister][0] == 0) {
					check[newSister][0] = time;
					q.push(i2(newSister, time + 1));
				}
			}
			else {
				if (check[newSister][1] == 0) {
					check[newSister][1] = time;
					q.push(i2(newSister, time + 1));
				}
			}
		}

		//+1
		newSister = sister + 1;
		if (newSister >= 0 && newSister <= 500000) {
			if (time % 2 == 0) {
				if (check[newSister][0] == 0) {
					check[newSister][0] = time;
					q.push(i2(newSister, time + 1));
				}
			}
			else {
				if (check[newSister][1] == 0) {
					check[newSister][1] = time;
					q.push(i2(newSister, time + 1));
				}
			}
		}

		//*2
		newSister = sister * 2;
		if (newSister >= 0 && newSister <= 500000) {
			if (time % 2 == 0) {
				if (check[newSister][0] == 0) {
					check[newSister][0] = time;
					q.push(i2(newSister, time + 1));
				}
			}
			else {
				if (check[newSister][1] == 0) {
					check[newSister][1] = time;
					q.push(i2(newSister, time + 1));
				}
			}
		}
	}

	int brother = K + Time * (Time + 1) / 2;
	while (brother <= 500000) {
		if (Time % 2 == 0) {
			if (Time >= check[brother][0]) {
				return Time;
			}
		}
		else {
			if (Time >= check[brother][1]) {
				return Time;
			}
		}
		Time++;
		brother += Time;
	}
	
	return -1;
}