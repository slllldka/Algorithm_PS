#include <iostream>
#include <utility>
#include <list>
#include <queue>
#include <tuple>

using namespace std;
using i2 = pair<long long, long long>;
using dii = tuple<double, long long, long long>;

long long N;
i2 pos[1000];
long long connected[1000];
list<long long> graph[1000];
long long graphNum = 0;
priority_queue<dii> pq;

double lengthSquare(i2 pos1, i2 pos2) {
	return (pos1.first - pos2.first) * (pos1.first - pos2.first)
		+ (pos1.second - pos2.second) * (pos1.second - pos2.second);
}

long long kruskal() {
	long long count = 0;
	double totalCost = 0;
	while (!pq.empty()) {
		double cost;
		long long n1, n2;
		tie(cost, n1, n2) = pq.top();
		cost *= -1;
		pq.pop();

		if (connected[n1] == 0 && connected[n2] == 0) {
			graphNum++;
			connected[n1] = graphNum;
			connected[n2] = graphNum;
			graph[graphNum].push_back(n1);
			graph[graphNum].push_back(n2);
			count++;
			totalCost += cost;
		}
		else if (connected[n1] > 0 && connected[n2] == 0) {
			connected[n2] = connected[n1];
			graph[connected[n1]].push_back(n2);
			count++;
			totalCost += cost;
		}
		else if (connected[n1] == 0 && connected[n2] > 0) {
			connected[n1] = connected[n2];
			graph[connected[n2]].push_back(n1);
			count++;
			totalCost += cost;
		}
		else if (connected[n1] > 0 && connected[n2] > 0) {
			if (connected[n1] != connected[n2]) {
				long long temp = connected[n2];
				for (list<long long>::iterator iter = graph[temp].begin();
					iter != graph[temp].end(); iter++) {
					connected[*iter] = connected[n1];
				}
				graph[connected[n1]].splice(graph[connected[n1]].end(), graph[temp]);
				count++;
				totalCost += cost;
			}
		}

		if (count == N - 1) {
			break;
		}
	}
	long long ret = totalCost;
	if (totalCost - ret >= 0.5) {
		ret++;
	}
	return ret;
}

int main() {
	long long T;
	double E;
	cin >> T;
	for (long long t = 1; t <= T; t++) {
		cin >> N;
		graphNum = 0;
		for (long long i = 0; i < N; i++) {
			connected[i] = 0;
			graph[i].clear();
			cin >> pos[i].first;
		}
		for (long long i = 0; i < N; i++) {
			cin >> pos[i].second;
		}
		cin >> E;

		pq = priority_queue<dii>();
		for (long long i = 0; i < N - 1; i++) {
			for (long long j = i + 1; j < N; j++) {
				pq.push(dii(-E * lengthSquare(pos[i], pos[j]), i, j));
			}
		}

		cout << '#' << t << ' ' << kruskal() << '\n';
	}
	return 0;
}