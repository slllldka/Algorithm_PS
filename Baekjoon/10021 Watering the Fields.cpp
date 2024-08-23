#include <iostream>
#include <tuple>
#include <list>
#include <utility>
#include <queue>
#include <vector>

using namespace std;

using i2 = pair<int, int>;
using i3 = tuple<int, int, int>;

struct cmp {
	bool operator()(i3 edge1, i3 edge2) {
		int d1 = get<2>(edge1), d2 = get<2>(edge2);
		return (d1 > d2);
	}
};

int N, C;
i2 nodes[2000];
priority_queue<i3, vector<i3>, cmp> edges;
list<int> sets[2000];

int euclideanDistance(i2 node1, i2 node2) {
	return ((node1.first - node2.first) * (node1.first - node2.first)
		+ (node1.second - node2.second) * (node1.second - node2.second));
}

int kruskal() {
	int totalCost = 0;
	int count = 0;
	int connected[2000] = {};
	int numberOfSets = 0;
	for (int i = 0; i < N; i++) {
		connected[i] = -1;
	}

	while (!edges.empty()) {
		i3 edge = edges.top();
		edges.pop();
		int n1 = get<0>(edge), n2 = get<1>(edge), eD = get<2>(edge);
		if ((connected[n1] == -1) && (connected[n2] == -1)) {
			connected[n1] = numberOfSets;
			connected[n2] = numberOfSets;
			sets[numberOfSets].push_back(n1);
			sets[numberOfSets].push_back(n2);
			numberOfSets++;
		}
		else if (connected[n1] == -1 && connected[n2] >= 0) {
			connected[n1] = connected[n2];
			sets[connected[n2]].push_back(n1);
		}
		else if (connected[n1] >= 0 && connected[n2] == -1) {
			connected[n2] = connected[n1];
			sets[connected[n1]].push_back(n2);
		}
		else if (connected[n1] >= 0 && connected[n2] >= 0) {
			if (connected[n1] == connected[n2]) {
				continue;
			}
			else {
				int save = connected[n2];
				for (int node : sets[save]) {
					connected[node] = connected[n1];
				}
				sets[n1].splice(sets[connected[n1]].end(), sets[save]);
			}
		}

		totalCost += eD;
		count++;

		if (count == N - 1) {
			break;
		}
	}

	if (count == N - 1) {
		return totalCost;
	}
	else {
		return -1;
	}
}


int main() {
	int x_i, y_i, eD;
	cin >> N >> C;
	for (int i = 0; i < N; i++) {
		cin >> x_i >> y_i;
		nodes[i] = i2(x_i, y_i);
	}

	for (int i = 0; i < N - 1; i++) {
		for (int j = i + 1; j < N; j++) {
			eD = euclideanDistance(nodes[i], nodes[j]);
			if (eD >= C) {
				edges.push(i3(i, j, eD));
			}
		}
	}
	/*while (!edges.empty()) {
		i3 edge = edges.top();
		edges.pop();
		cout << get<2>(edge) << '\n';
	}*/

	cout << kruskal();
	return 0;
}