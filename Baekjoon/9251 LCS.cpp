#include <iostream>

#define max(a, b) (((a) > (b)) ? (a) : (b))

using namespace std;

string str1, str2;
int arr[1001][1001];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> str1 >> str2;

	int maxLength = 0;
	for (int i = 0; i <= str1.length(); i++) {
		for (int j = 0; j <= str2.length(); j++) {
			if (i == 0 || j == 0) {
				arr[i][j] = 0;
			}
			else {
				if (str1[i - 1] == str2[j - 1]) {
					arr[i][j] = arr[i - 1][j - 1] + 1;
					maxLength = max(maxLength, arr[i][j]);
				}
				else {
					arr[i][j] = max(arr[i - 1][j], arr[i][j - 1]);
				}
			}
		}
	}

	cout << maxLength;

	return 0;
}