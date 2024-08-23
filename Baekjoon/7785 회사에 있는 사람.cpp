#include <iostream>
#include <map>
#include <utility>

using namespace std;

using sb = pair<string, bool>;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	map<string, bool, greater<string>> Map;
	
	int N;
	string name, status;

	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> name >> status;
		if (status.compare("enter") == 0) {
			auto ret = Map.insert(sb(name, true));
			if (!ret.second) {
				Map[name] = true;
			}
		}
		else if (status.compare("leave") == 0) {
			Map[name] = false;
		}
	}

	for (auto a : Map) {
		if (a.second) {
			cout << a.first << '\n';
		}
	}

	return 0;
}