#include <unordered_map>
#include <tuple>
#include <string>
#include <queue>
#include <map>
#include <utility>
#include <iostream>

using namespace std;

using i2 = pair<int, int>;
using i3 = tuple<int, int, int>;

unordered_map<int, i3> hashMap;
priority_queue<i2> minHeap[3][2], maxHeap[3][2];
map<int, priority_queue<int>> scoreMap[3][2];

void init() {
	hashMap.clear();
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 2; j++) {
			minHeap[i][j] = priority_queue<i2>();
			maxHeap[i][j] = priority_queue<i2>();
			scoreMap[i][j].clear();
		}
	}
}

int add(int mId, int mGrade, char mGender[7], int mScore) {
	//cout << "addStart\n";
	int grade = mGrade - 1;
	int gender = mGender[0] == 'f';
	hashMap[mId] = i3(grade, gender, mScore);
	maxHeap[grade][gender].push(i2(mScore, mId));
	minHeap[grade][gender].push(i2(-mScore, -mId));
	if (!scoreMap[grade][gender].count(mScore)) {
		scoreMap[grade][gender][mScore] = priority_queue<int>();
		//cout << grade << ' ' << gender << ' ' << mScore << '\n';
	}
	scoreMap[grade][gender][mScore].push(-mId);
	//cout << scoreMap[grade][gender][mScore].size() << '\n';
	
	while (true) {
		if (!hashMap.count(maxHeap[grade][gender].top().second)) {
			maxHeap[grade][gender].pop();
		}
		else if (hashMap[maxHeap[grade][gender].top().second]
			!= i3(grade, gender, maxHeap[grade][gender].top().first)) {
			maxHeap[grade][gender].pop();
		}
		else {
			break;
		}
	}
	//cout << "addEnd\n";
	//cout << maxHeap[grade][gender].top().second << '\n';
	return maxHeap[grade][gender].top().second;
}

int remove(int mId) {
	//cout << "removeStart\n";
	if (!hashMap.count(mId)) {
		return 0;
	}
	int grade, gender, score;
	tie(grade, gender, score) = hashMap[mId];
	hashMap.erase(mId);
	while (!minHeap[grade][gender].empty()) {
		if (!hashMap.count(-minHeap[grade][gender].top().second)) {
			minHeap[grade][gender].pop();
		}
		else if (hashMap[-minHeap[grade][gender].top().second]
			!= i3(grade, gender, -minHeap[grade][gender].top().first)) {
			minHeap[grade][gender].pop();
		}
		else {
			break;
		}
	}
	//cout << "removeEnd\n";
	if (minHeap[grade][gender].empty()) {
		//cout << 0 << '\n';
		return 0;
	}
	else {
		//cout << -minHeap[grade][gender].top().second << '\n';
		return -minHeap[grade][gender].top().second;
	}
}

int query(int mGradeCnt, int mGrade[], int mGenderCnt, char mGender[][7], int mScore) {
	//cout << "queryStart\n";
	int grade, gender, minScore = 300001, minID = 1000000001;
	bool created = false;
	for (int i = 0; i < mGradeCnt; i++) {
		for (int j = 0; j < mGenderCnt; j++) {
			grade = mGrade[i] - 1;
			gender = mGender[j][0] == 'f';
			created = false;
			if (!scoreMap[grade][gender].count(mScore)) {
				scoreMap[grade][gender][mScore] = priority_queue<int>();
				created = true;
			}
			auto iter = scoreMap[grade][gender].find(mScore);

			while (iter != scoreMap[grade][gender].end()) {
				//cout << grade << ' ' << gender << ' ' << (*iter).first << '\n';
				if (minScore < (*iter).first) {
					break;
				}
				while (!(*iter).second.empty()) {
					//cout << -(*iter).second.top() << '\n';
					if (!hashMap.count(-(*iter).second.top())) {
						(*iter).second.pop();
					}
					else if(hashMap[-(*iter).second.top()] != i3(grade, gender, (*iter).first)){
						(*iter).second.pop();
					}
					else {
						if (minScore > (*iter).first) {
							minScore = (*iter).first;
							minID = -(*iter).second.top();
						}
						else {
							if (minID > -(*iter).second.top()) {
								minID = -(*iter).second.top();
							}
						}
						iter = scoreMap[grade][gender].end();
						iter--;
						break;
					}
				}
				iter++;
			}
			if (created) {
				scoreMap[grade][gender].erase(mScore);
			}
		}
	}
	//cout << "queryEnd\n";
	if (minID == 1000000001) {
		//cout << 0 << '\n';
		return 0;
	}
	else {
		//cout << minID << '\n';
		return minID;
	}
}