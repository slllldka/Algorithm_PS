#include <iostream>
#include <list>

using namespace std;

int N, M;
list<int> cryptoList;

int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	list<int>::iterator iter;
	int inputInt, x, y, s, count;
	char inputChar;
	for (int t = 1; t <= 10; t++) {
		cin >> N;
		cryptoList.clear();
		for (int i = 0; i < N; i++) {
			cin >> inputInt;
			cryptoList.push_back(inputInt);
		}
		cin >> M;
		for (int i = 0; i < M; i++) {
			cin >> inputChar;
			if (inputChar == 'I') {
				cin >> x >> y;
				iter = cryptoList.begin();
				advance(iter, x);
				for (int j = 0; j < y; j++) {
					cin >> s;
					iter = cryptoList.insert(iter, s);
					iter++;
				}
			}
			else if (inputChar == 'D') {
				iter = cryptoList.begin();
				cin >> x >> y;
				advance(iter, x);
				for (int j = 0; j < y; j++) {
					iter = cryptoList.erase(iter);
				}
			}
			else if (inputChar == 'A') {
				cin >> y;
				for (int j = 0; j < y; j++) {
					cin >> s;
					cryptoList.push_back(s);
				}
			}
		}
		
		cout << '#' << t << ' ';
		count = 0;
		for (iter = cryptoList.begin(); iter != cryptoList.end(); iter++) {
			cout << *iter << ' ';
			count++;
			if (count == 10) {
				break;
			}
		}
		cout << '\n';
	}

	return 0;
}