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

#include<iostream>

#define min(a, b) (((a) < (b)) ? (a) : (b))

constexpr int inf = 100000, MAX_SIZE = 400;

using namespace std;

int weight[401][401];
int result[401][401];
bool visit[401];

class pii {
public:
	int first = 0, second = 0;
	
	pii(){}
	pii(int _first, int _second): first(_first), second(_second){}
};

template <typename T>
class stackk {
private:
	T arr[MAX_SIZE];
	int topIdx = -1;
public:
	stackk(){}

	bool empty() {
		return (topIdx == -1);
	}
	void push(T item) {
		arr[++topIdx] = item;
	}
	void pop() {
		topIdx--;
	}
	T& top() {
		return arr[topIdx];
	}
	

};

int main(int argc, char** argv)
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	int test_case;
	int T;

	int N = 0, M = 0;
	int s = 0, e = 0, c = 0;
	int minCycle = inf;
	int tempCycle = 0;
	int start = 0, end = 0;
	
	bool canMove = false;

	stackk<pii> stackNode;

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
	for (test_case = 1; test_case <= T; ++test_case)
	{

		/////////////////////////////////////////////////////////////////////////////////////////////
		/*
			 이 부분에 여러분의 알고리즘 구현이 들어갑니다.
		 */

		cin >> N >> M;
		
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				weight[i][j] = inf;
				result[i][j] = inf;
			}
		}

		for (int i = 0; i < M; i++) {
			cin >> s >> e >> c;
			weight[s][e] = c;
		}

		//floyd-warshall
		/*
		for (int j = 1; j <= N; j++) {
			for (int i = 1; i <= N; i++) {
				if (result[i][j] == inf) {
					result[i][j] = weight[i][j];
				}
				for (int k = 1; k <= N; k++) {
					if (result[j][k] == inf) {
						result[i][j] = weight[i][j];
					}

					if (i == j && j == k) {
						result[i][k] = weight[i][k];
					}
					else if (i != j && j != k) {
						result[i][k] = min(result[i][k], result[i][j] + result[j][k]);
					}
				}
			}
		}
		
		minCycle = inf;
		for (int i = 1; i <= N; i++) {
			minCycle = min(minCycle, result[i][i]);
		}*/

		//DFS
		minCycle = inf;
		for (int i = 1; i <= N; i++) {
			visit[i] = false;
		}

		for (int i = 1; i <= N; i++) {
			stackNode.push(pii(i, 0));
			visit[i] = true;
			tempCycle = 0;
			while (!stackNode.empty()) {
				start = stackNode.top().first;
				canMove = false;

				if (weight[start][i] != inf) {
					minCycle = min(minCycle, tempCycle + weight[start][i]);
				}
				else {
					for (int j = stackNode.top().second + 1; j <= N; j++) {
						if (!visit[j]) {
							if (tempCycle + weight[start][j] >= minCycle) {
								continue;
							}
							visit[j] = true;
							canMove = true;
							tempCycle += weight[start][j];
							stackNode.top().second = j;
							stackNode.push(pii(j, 0));
							break;
						}
					}
				}

				if (!canMove) {
					stackNode.pop();
					end = start;
					if (!stackNode.empty()) {
						start = stackNode.top().first;
						visit[end] = false;
						tempCycle -= weight[start][end];
					}
				}
			}
		}
		 /////////////////////////////////////////////////////////////////////////////////////////////


		cout << '#' << test_case << ' ';
		if (minCycle == inf) {
			cout << -1;
		}
		else {
			cout << minCycle;
		}
		cout << '\n';

	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}