#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

using i3 = tuple<int, int, int>;

class bfInterpreter {
public:
	static const int maxInt = 255, minInt = 0;
	int arr[100000];
	int arrPointer, codePointer;
	string code;
	string input;
	int s_m, s_c, s_i;

	bool isInLoop;
	i3 loopInfo[2100];
	int currentLoopIdx, saveCurrentLoopIdx;
	int minLoopPtr = 100000, maxLoopPtr = 0;
	int operationNum;

	bfInterpreter() {
		arrPointer = 0;
		codePointer = 0;
		code = "";
		input = "";
		s_m = 0;
		s_c = 0;
		s_i = 0;

		isInLoop = false;
		currentLoopIdx = -1;
		operationNum = 0;
	}

	void initialize(int s_m, int s_c, int s_i) {
		this->s_m = s_m;
		this->s_c = s_c;
		this->s_i = s_i;
		cin >> code;
		cin >> input;

		for (int i = 0; i < s_m; i++) {
			arr[i] = 0;
		}

		arrPointer = 0;
		codePointer = 0;

		isInLoop = false;
		currentLoopIdx = -1;
		operationNum = 0;
	}

	void startOperation(bool retry) {
		operationNum = 0;
		minLoopPtr = 100000;
		maxLoopPtr = 0;
		if (retry) {
			saveCurrentLoopIdx = currentLoopIdx;
		}
		while (codePointer < s_c && operationNum < 50000000) {
			switch (code[codePointer]) {
			case '-':
				operationMinus();
				break;
			case '+':
				operationPlus();
				break;
			case '<':
				operationShiftLeft();
				break;
			case '>':
				operationshiftRight();
				break;
			case '[':
				operationLoopLeft();
				break;
			case ']':
				operationLoopRight();
				break;
			case '.':
				operationPrint();
				break;
			case ',':
				operationSave();
				break;
			default:
				break;
			}

			operationNum++;
			if (retry) {
				if (saveCurrentLoopIdx > currentLoopIdx) {
					saveCurrentLoopIdx--;
				}
			}
		}

		if (operationNum == 50000000) {
			if (!retry) {
				//cout << "50m\n";
				if (isInLoop) {
					int i = 0;
					for (i = currentLoopIdx; i >= 0; i--) {
						if (get<0>(loopInfo[i]) > 0) {
							//cout << codePointer << ' ' << currentLoopIdx << '\n';
							//cout << get<0>(loopInfo[i]) << '\n';
							startOperation(true);
							return;
						}
					}
				}
				else {
					cout << "Terminates" << '\n';
				}
			}
			else {
				if (isInLoop) {
					cout << "Loops" << ' ' << minLoopPtr << ' ' << maxLoopPtr << '\n';
				}
				else {
					cout << "Terminates" << '\n';
				}
			}
		}
		else if (codePointer == s_c) {
			cout << "Terminates" << '\n';
		}
		else {
			cout << s_c << ' ' << operationNum;
			cout << "?";
		}
	}
	void operationMinus() {
		arr[arrPointer]--;
		if (arr[arrPointer] < minInt) {
			arr[arrPointer] = maxInt;
		}
		codePointer++;
	}
	void operationPlus() {
		arr[arrPointer]++;
		if (arr[arrPointer] > maxInt) {
			arr[arrPointer] = minInt;
		}
		codePointer++;
	}
	void operationShiftLeft() {
		arrPointer--;
		if (arrPointer < 0) {
			arrPointer = s_m - 1;
		}
		codePointer++;
	}
	void operationshiftRight() {
		arrPointer++;
		if (arrPointer >= s_m) {
			arrPointer = 0;
		}
		codePointer++;
	}
	void operationLoopLeft() {
		if (arr[arrPointer] == 0) {
			int leftNum = 1, rightNum = 0;
			for (int i = codePointer+1;; i++) {
				if (code[i] == '[') {
					leftNum++;
				}
				else if (code[i] == ']') {
					rightNum++;
				}

				if (leftNum == rightNum) {
					codePointer = i + 1;
					break;
				}
			}
		}
		else {
			loopStart();
			codePointer++;
		}
	}
	void operationLoopRight() {
		if (arr[arrPointer] != 0) {
			int leftNum = 0, rightNum = 1;
			for (int i = codePointer - 1;; i--) {
				if (code[i] == '[') {
					leftNum++;
				}
				else if (code[i] == ']') {
					rightNum++;
				}

				if (leftNum == rightNum) {
					minLoopPtr = minLoopPtr < i ? minLoopPtr : i;
					maxLoopPtr = maxLoopPtr > codePointer ? maxLoopPtr : codePointer;

					get<0>(loopInfo[currentLoopIdx])++;
					get<1>(loopInfo[currentLoopIdx]) = i;
					get<2>(loopInfo[currentLoopIdx]) = codePointer;
					codePointer = i + 1;

					break;
				}
			}
		}
		else {
			if (isInLoop) {
				loopEnd();
			}
			codePointer++;
		}
	}
	void operationPrint() {
		codePointer++;
	}
	void operationSave() {
		if (input.length() == 0) {
			arr[arrPointer] = 255;
		}
		else {
			arr[arrPointer] = input[0];
			input = input.substr(1);
		}
		codePointer++;
	}

	void loopStart() {
		isInLoop = true;
		currentLoopIdx++;
		loopInfo[currentLoopIdx] = i3(0, 0, 0);
	}
	void loopEnd() {
		loopInfo[currentLoopIdx] = i3(0, 0, 0);
		currentLoopIdx--;
		if (currentLoopIdx == -1) {
			isInLoop = false;
		}
	}
};

int main() {
	int t;
	int s_m, s_c, s_i;
	bfInterpreter interpreter = bfInterpreter();
	cin >> t;
	for (int i = 0; i < t; i++) {
		cin >> s_m >> s_c >> s_i;
		interpreter.initialize(s_m, s_c, s_i);
		interpreter.startOperation(false);
	}
}