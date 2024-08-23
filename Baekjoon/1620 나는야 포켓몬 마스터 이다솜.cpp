#include <iostream>
#include <map>
#include <utility>
#include <string>

using namespace std;

using pis = pair<int, string>;
using psi = pair<string, int>;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	map<int, string> pokemonMapID;
	map<string, int> pokemonMapName;
	int N, M;
	string name;

	cin >> N >> M;
	for (int i = 1; i <= N; i++) {
		cin >> name;
		pokemonMapID.insert(pis(i, name));
		pokemonMapName.insert(psi(name, i));
	}

	for (int i = 0; i < M; i++) {
		bool isNum = true;
		cin >> name;
		for (int e : name) {
			isNum = isdigit(e);
			if (!isNum) {
				break;
			}
		}

		if (isNum) {
			cout << pokemonMapID[stoi(name)] << '\n';
		}
		else {
			cout << pokemonMapName[name] << '\n';
		}
	}

	return 0;
}