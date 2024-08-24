#include <iostream>
#include <unordered_map>

using namespace std;

unordered_map<string, int> hashMap;

int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	int T, N, M, count;
	string input;
	cin >> T;
	for (int t = 1; t <= T; t++) {
		cin >> N >> M;
		hashMap.clear();
		for (int i = 0; i < N; i++) {
			cin >> input;
			hashMap[input] = 1;
		}

		count = 0;
		for (int i = 0; i < M; i++) {
			cin >> input;
			count += hashMap.count(input) > 0;
		}
		
		cout << '#' << t << ' ' << count << '\n';
	}
	return 0;
}