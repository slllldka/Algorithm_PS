#include <iostream>
#include <list>
#include <queue>
#include <utility>

using namespace std;

using i2 = pair<int, int>;

int N, Q, maxUSADO = 0, minUSADO = 2147483647;
list<i2> graph[5001];

int getNumOfRecommendedVideos(int k, int v) {
	queue<i2> q;
	bool visited[5001] = {};
	int count = 0;
	for (int i = 1; i <= N; i++) {
		visited[i] = false;
	}

	q.push(i2(v, maxUSADO));
	
	while (!q.empty()) {
		int start = q.front().first, usado = q.front().second;
		q.pop();

		if (visited[start]) {
			continue;
		}
		else if (!visited[start]) {
			visited[start] = true;
		}

		if (usado >= k) {
			if (start != v) {
				count++;
			}
			for (i2 data : graph[start]) {
				if (!visited[data.first] && (data.second >= k)) {
					q.push(i2(data.first, usado < data.second ? usado : data.second));
				}
			}
		}
	}

	return count;
}

int main() {
	int p_i, q_i, r_i, k_i, v_i;
	cin >> N >> Q;
	for (int i = 0; i < (N - 1); i++) {
		cin >> p_i >> q_i >> r_i;
		graph[p_i].push_back(i2(q_i, r_i));
		graph[q_i].push_back(i2(p_i, r_i));
		maxUSADO = maxUSADO > r_i ? maxUSADO : r_i;
		minUSADO = minUSADO < r_i ? minUSADO : r_i;
	}

	for (int i = 0; i < Q; i++) {
		cin >> k_i >> v_i;
		cout << getNumOfRecommendedVideos(k_i, v_i) << '\n';
	}
}