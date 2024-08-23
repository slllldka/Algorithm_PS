#include <iostream>
#include <stack>
#include <list>
#include <algorithm>

#define max(a, b) (((a) > (b)) ? (a) : (b))

using namespace std;

int N, opNum, selectNum = 0, maxResult;

list<int> combinationList;

string input;
string addedVer;

int calculate();

int main() {
	ios_base::sync_with_stdio(false);
	cin >> N;
	cin >> input;

	addedVer = input;
	maxResult = calculate();
	
	opNum = N / 2;
	while (selectNum < opNum / 2) {
		combinationList.clear();
		selectNum++;
		for (int i = 0; i < opNum; i++) {
			if (i < opNum - selectNum) {
				combinationList.push_back(0);
			}
			else {
				combinationList.push_back(1);
			}
		}

		do {
			bool isConsecutive = false;
			int recent = -1;
			int idx = 1;
			int selectIdx = 0;
			
			addedVer = input;
			for (int e : combinationList) {
				if (e == 0) {
					recent = 0;
				}
				else if (e == 1) {
					if (recent == 1) {
						isConsecutive = true;
						break;
					}
					else {
						addedVer.insert(2 * idx + 2 * selectIdx - 2, "(");
						addedVer.insert(2 * idx + 2 * selectIdx + 2, ")");

						recent = 1;
						selectIdx++;
					}
				}
				idx++;
			}

			if (!isConsecutive) {
				maxResult = max(maxResult, calculate());
			}
		} while (next_permutation(combinationList.begin(), combinationList.end()));
	}
	
	cout << maxResult;

	return 0;
}

int calculate() {
	list<char> postfix;
	stack<int> stackNum;
	stack<char> stackOp;
	for (char c : addedVer) {
		if (c >= '0' && c <= '9') {
			postfix.push_back(c);
		}
		else {
			if (c == '+' || c == '-' || c == '*') {
				if (!stackOp.empty()) {
					if (stackOp.top() != '(') {
						postfix.push_back(stackOp.top());
						stackOp.pop();
						stackOp.push(c);
					}
					else {
						stackOp.push(c);
					}
				}
				else {
					stackOp.push(c);
				}
			}
			else if (c == '(') {
				stackOp.push(c);
			}
			else if (c == ')') {
				while (stackOp.top() != '(') {
					postfix.push_back(stackOp.top());
					stackOp.pop();
				}
				stackOp.pop();
			}
		}
	}

	while (!stackOp.empty()) {
		postfix.push_back(stackOp.top());
		stackOp.pop();
	}

	for (char c : postfix) {
		if (c >= '0' && c <= '9') {
			stackNum.push(c - '0');
		}
		else {
			int n1, n2, result = 0;
			n2 = stackNum.top();
			stackNum.pop();
			n1 = stackNum.top();
			stackNum.pop();
			if (c == '+') {
				result = n1 + n2;
			}
			else if (c == '-') {
				result = n1 - n2;
			}
			else if (c == '*') {
				result = n1 * n2;
			}
			stackNum.push(result);
		}
	}
	
	return stackNum.top();
}