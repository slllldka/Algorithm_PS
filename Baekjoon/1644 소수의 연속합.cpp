#include <iostream>
#include <cmath>
#include <vector>
#include <list>

using namespace std;

bool* visit;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int N, sum = 0, num = 0, left = 0, right = 0;
	vector<int> primes;

	cin >> N;

	if (N == 1) {
		cout << 0;
		return 0;
	}

	visit = new bool[N + 1];
	for (int i = 0; i <= N; i++) {
		visit[i] = false;
	}

	int start = 2;
	while (start <= (int)(sqrt(N))) {
		visit[start] = true;
		primes.push_back(start);
		for (int i = start * start; i <= N; i+=start) {
			visit[i] = true;
		}

		for (int i = start + 1; i <= N; i++) {
			if (!visit[i]) {
				start = i;
				break;
			}
		}
	}

	for (int i = start; i <= N; i++) {
		if (!visit[i]) {
			primes.push_back(i);
		}
	}

	sum = primes[0];
	for (left = 0; left < primes.size();) {
		if (sum < N) {
			right++;
			if (right >= primes.size()) {
				break;
			}
			else {
				sum += primes[right];
			}
		}
		else if (sum == N) {
			num++;

			sum -= primes[left];
			left++;
			right++;
			if (right >= primes.size()) {
				break;
			}
			else {
				sum += primes[right];
			}
		}
		else {
			sum -= primes[left];
			left++;
			if (left > right) {
				break;
			}
		}
	}

	cout << num;
	delete[] visit;

	return 0;
}