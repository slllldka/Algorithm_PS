#include<iostream>
#include <string>
#include <cstdio>

using namespace std;

int T, N;
string fileName[50];

void printFiles(int);
void setFileName(int);

int main(int argc, char** argv)
{
	int test_case;
	int T;
	/*
	   �Ʒ��� freopen �Լ��� input.txt �� read only �������� �� ��,
	   ������ ǥ�� �Է�(Ű����) ��� input.txt ���Ϸκ��� �о���ڴٴ� �ǹ��� �ڵ��Դϴ�.
	   //�������� �ۼ��� �ڵ带 �׽�Ʈ �� ��, ���Ǹ� ���ؼ� input.txt�� �Է��� ������ ��,
	   freopen �Լ��� �̿��ϸ� ���� cin �� ������ �� ǥ�� �Է� ��� ���Ϸκ��� �Է��� �޾ƿ� �� �ֽ��ϴ�.
	   ���� �׽�Ʈ�� ������ ������ �Ʒ� �ּ��� ����� �� �Լ��� ����ϼŵ� �����ϴ�.
	   freopen �Լ��� ����ϱ� ���ؼ��� #include <cstdio>, Ȥ�� #include <stdio.h> �� �ʿ��մϴ�.
	   ��, ä���� ���� �ڵ带 �����Ͻ� ������ �ݵ�� freopen �Լ��� ����ų� �ּ� ó�� �ϼž� �մϴ�.
	*/
	//freopen("input.txt", "r", stdin);
	cin >> T;
	/*
	   ���� ���� �׽�Ʈ ���̽��� �־����Ƿ�, ������ ó���մϴ�.
	*/
	for (test_case = 1; test_case <= T; ++test_case)
	{

		/////////////////////////////////////////////////////////////////////////////////////////////

		cin >> N;

		cout << '#' + to_string(test_case) + ' ';
		if (N > 50) {
			printFiles(50);
		}
		else {
			printFiles(N);
		}

		 /////////////////////////////////////////////////////////////////////////////////////////////


	}
	return 0;//��������� �ݵ�� 0�� �����ؾ��մϴ�.
}

void printFiles(int num) {
	setFileName(num);
	for (int i = 0; i < num; i++) {
		cout << fileName[i];
		if (i < num - 1) {
			cout << ' ';
		}
		else {
			cout << '\n';
		}
	}
}

void setFileName(int num) {
	int count = 0;
	int fileNum = 1;
	while (count < num) {
		fileName[count] = to_string(fileNum) + ".png";
		if (fileNum * 10 <= N) {
			fileNum *= 10;
		}
		else if(fileNum + 1 <= N) {
			string fileNumString0 = to_string(fileNum);
			string fileNumString1 = to_string(fileNum + 1);
			string finalFileNumString = "";
			for (int i = 0; i < (int)fileNumString0.length(); i++) {
				finalFileNumString += fileNumString1[i];
				if (fileNumString0[i] != fileNumString1[i]) {
					break;
				}
			}
			fileNum = stoi(finalFileNumString);
		}
		else {
			fileNum /= 10;
			fileNum += 1;
		}
		
		count++;
	}
}