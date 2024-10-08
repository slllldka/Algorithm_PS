/////////////////////////////////////////////////////////////////////////////////////////////
// 기본 제공코드는 임의 수정해도 관계 없습니다. 단, 입출력 포맷 주의
// 아래 표준 입출력 예제 필요시 참고하세요.
// 표준 입력 예제
// int a;
// float b, c;
// double d, e, f;
// char g;
// char var[256];
// long long AB;
// cin >> a;                            // int 변수 1개 입력받는 예제
// cin >> b >> c;                       // float 변수 2개 입력받는 예제 
// cin >> d >> e >> f;                  // double 변수 3개 입력받는 예제
// cin >> g;                            // char 변수 1개 입력받는 예제
// cin >> var;                          // 문자열 1개 입력받는 예제
// cin >> AB;                           // long long 변수 1개 입력받는 예제
/////////////////////////////////////////////////////////////////////////////////////////////
// 표준 출력 예제
// int a = 0;                            
// float b = 1.0, c = 2.0;               
// double d = 3.0, e = 0.0; f = 1.0;
// char g = 'b';
// char var[256] = "ABCDEFG";
// long long AB = 12345678901234567L;
// cout << a;                           // int 변수 1개 출력하는 예제
// cout << b << " " << c;               // float 변수 2개 출력하는 예제
// cout << d << " " << e << " " << f;   // double 변수 3개 출력하는 예제
// cout << g;                           // char 변수 1개 출력하는 예제
// cout << var;                         // 문자열 1개 출력하는 예제
// cout << AB;                          // long long 변수 1개 출력하는 예제
/////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <utility>
#include <cmath>

using namespace std;
using i2 = pair<int, int>;

int sumArr[142];
i2 allPos[10001];
bool saved[10001];

i2 findPos(int n) {
	/*int start = 1, end = 141, middle;
	i2 ret = i2(0, 0);
	while (start <= end) {
		middle = (start + end) / 2;
		if (n <= sumArr[middle]) {
			if (n > sumArr[middle - 1]) {
				ret = i2(middle, n - sumArr[middle - 1]);
				break;
			}
			else {
				end = middle - 1;
			}
		}
		else {
			if (n <= sumArr[middle + 1]) {
				ret = i2(middle + 1, n - sumArr[middle]);
				break;
			}
			else {
				start = middle + 1;
			}
		}
	}
	return ret;*/

	if (!saved[n]) {
		int x = ceil((-1 + sqrt(1 + 8 * n)) / 2);
		int y = n - sumArr[x - 1];
		allPos[n] = i2(x, y);
		saved[n] = true;
	}
	return allPos[n];
}
int findMinCost(i2 sPos, i2 ePos) {
	if (sPos.first == ePos.first) {
		return (ePos.second - sPos.second);
	}
	else {
		if (ePos.second < sPos.second) {
			return (ePos.first - sPos.first + sPos.second - ePos.second);
		}
		else if (ePos.second == sPos.second) {
			return (ePos.first - sPos.first);
		}
		else {
			if ((ePos.second - sPos.second) <= (ePos.first - sPos.first)) {
				return (ePos.first - sPos.first);
			}
			else {
				return(ePos.second - sPos.second);
			}
		}
	}
}

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int test_case;
	int T;
	int s, e, ans;
	i2 sPos, ePos, temp;
	/*
	   아래의 freopen 함수는 input.txt 를 read only 형식으로 연 후,
	   앞으로 표준 입력(키보드) 대신 input.txt 파일로부터 읽어오겠다는 의미의 코드입니다.
	   //여러분이 작성한 코드를 테스트 할 때, 편의를 위해서 input.txt에 입력을 저장한 후,
	   freopen 함수를 이용하면 이후 cin 을 수행할 때 표준 입력 대신 파일로부터 입력을 받아올 수 있습니다.
	   따라서 테스트를 수행할 때에는 아래 주석을 지우고 이 함수를 사용하셔도 좋습니다.
	   freopen 함수를 사용하기 위해서는 #include <cstdio>, 혹은 #include <stdio.h> 가 필요합니다.
	   단, 채점을 위해 코드를 제출하실 때에는 반드시 freopen 함수를 지우거나 주석 처리 하셔야 합니다.
	*/
	//freopen("input.txt", "r", stdin);
	cin >> T;
	/*
	   여러 개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
	*/

	for (int i = 1; i <= 141; i++) {
		sumArr[i] = i * (i + 1) / 2;
	}

	for (test_case = 1; test_case <= T; ++test_case)
	{
		/////////////////////////////////////////////////////////////////////////////////////////////
		/*
			 이 부분에 여러분의 알고리즘 구현이 들어갑니다.
		 */
		cin >> s >> e;
		sPos = findPos(s);
		ePos = findPos(e);
		if (sPos.first < ePos.first) {
			ans = findMinCost(sPos, ePos);
		}
		else if (sPos.first == ePos.first) {
			if (sPos.second < ePos.second) {
				ans = findMinCost(sPos, ePos);
			}
			else {
				ans = findMinCost(ePos, sPos);
			}
		}
		else {
			ans = findMinCost(ePos, sPos);
		}
		cout << '#' << test_case << ' ' << ans << '\n';
		/////////////////////////////////////////////////////////////////////////////////////////////


	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}