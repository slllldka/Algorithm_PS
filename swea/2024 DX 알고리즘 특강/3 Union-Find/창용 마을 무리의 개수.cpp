#include <iostream>
#include <list>

using namespace std;

int people[101];
int graphNum = 0;
list<int> graph[101];

int main() {
	int T, N, M, n1, n2;
	cin >> T;
	for (int t = 1; t <= T; t++) {
		cin >> N >> M;
		graphNum = 0;
		for (int i = 1; i < 101; i++) {
			people[i] = 0;
			graph[i].clear();
		}

		for (int i = 0; i < M; i++) {
			cin >> n1 >> n2;
			if (people[n1] == 0 && people[n2] == 0) {
				graphNum++;
				people[n1] = graphNum;
				people[n2] = graphNum;
				graph[graphNum].push_back(n1);
				graph[graphNum].push_back(n2);
			}
			else if (people[n1] == 0 && people[n2] > 0) {
				people[n1] = people[n2];
				graph[people[n2]].push_back(n1);
			}
			else if (people[n1] > 0 && people[n2] == 0) {
				people[n2] = people[n1];
				graph[people[n1]].push_back(n2);
			}
			else if (people[n1] > 0 && people[n2] > 0) {
				if (people[n1] != people[n2]) {
					int temp = people[n2];
					for (list<int>::iterator iter = graph[temp].begin();
						iter != graph[temp].end(); iter++) {
						people[*iter] = people[n1];
					}
					graph[people[n1]].splice(graph[people[n1]].end(), graph[temp]);
				}
			}
		}

		int count = 0;
		for (int i = 1; i <= graphNum; i++) {
			if (graph[i].size() > 0) {
				count++;
			}
		}
		for (int i = 1; i <= N; i++) {
			if (people[i] == 0) {
				count++;
			}
		}

		cout << '#' << t << ' ' << count << '\n';
	}
	return 0;
}