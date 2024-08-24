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

long long points[100000][3];
#include<iostream>

using namespace std;

long long innerProduct(long long src1[3], long long src2[3]) {
	return (src1[0] * src2[0] + src1[1] * src2[1] + src1[2] * src2[2]);
}

void crossProduct(long long src1[3], long long src2[3], long long dst[3]) {
	dst[0] = src1[1] * src2[2] - src1[2] * src2[1];
	dst[1] = src1[2] * src2[0] - src1[0] * src2[2];
	dst[2] = src1[0] * src2[1] - src1[1] * src2[0];
}

int main(int argc, char** argv)
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);
	
	int test_case;
	int T;
	long long N;
	long long vec1[3] = { 0, 0, 0 };
	long long vec2[3] = { 0, 0, 0 };
	long long normalVec[3] = { 0, 0, 0 };
	bool vec1Exist = false, vec2Exist = false;
	bool result = false;
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
		vec1[0] = 0;
		vec1[1] = 0;
		vec1[2] = 0;
		vec2[0] = 0;
		vec2[1] = 0;
		vec2[2] = 0;
		normalVec[0] = 0;
		normalVec[1] = 0;
		normalVec[2] = 0;
		vec1Exist = false;
		vec2Exist = false;
		result = true;

		cin >> N;
		for (int i = 0; i < N; i++) {
			cin >> points[i][0] >> points[i][1] >> points[i][2];
		}

		if (N <= 3) {
			result = true;
		}
		else {
			for (int i = 1; i < N; i++) {
				if (!vec1Exist) {
					vec1Exist = true;
					vec1[0] = points[i][0] - points[0][0];
					vec1[1] = points[i][1] - points[0][1];
					vec1[2] = points[i][2] - points[0][2];
				}
				else if(!vec2Exist){
					vec2[0] = points[i][0] - points[0][0];
					vec2[1] = points[i][1] - points[0][1];
					vec2[2] = points[i][2] - points[0][2];
					crossProduct(vec1, vec2, normalVec);
					if (normalVec[0] == 0 && normalVec[1] == 0 && normalVec[2] == 0) {
						continue;
					}
					else {
						vec2Exist = true;
					}
				}
				else {
					vec2[0] = points[i][0] - points[0][0];
					vec2[1] = points[i][1] - points[0][1];
					vec2[2] = points[i][2] - points[0][2];
					if (innerProduct(vec2, normalVec) == 0) {
						continue;
					}
					else {
						result = false;
						break;
					}

				}
			}
		}


		cout << '#' << test_case << ' ';
		if (result) {
			cout << "TAK\n";
		}
		else {
			cout << "NIE\n";
		}

		 /////////////////////////////////////////////////////////////////////////////////////////////


	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}