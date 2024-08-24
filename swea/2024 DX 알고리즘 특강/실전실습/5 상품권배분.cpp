#include <unordered_map>
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

struct Dept {
	int ID, num, parentID, totalNum;
	vector<int> childDept;
	Dept() {
		ID = -1;
		num = 0;
		parentID = -1;
		totalNum = 0;
		childDept.clear();
	}
	Dept(int ID, int num, int parentID) {
		this->ID = ID;
		this->num = num;
		this->parentID = parentID;
		totalNum = num;
		childDept.clear();
	}
};

int groupNum = 0;
int deptNum = 0;
unordered_map<int, int> idMap;
Dept depts[20000];
int totalTotalNum = 0;

void init(int N, int mId[], int mNum[]) {
	idMap.clear();
	groupNum = N;
	deptNum = 0;
	totalTotalNum = 0;
	for (int i = 0; i < N; i++) {
		idMap[mId[i]] = deptNum;
		depts[i] = Dept(deptNum++, mNum[i], -1);
		totalTotalNum += mNum[i];
	}
	return;
}

int add(int mId, int mNum, int mParent) {
	int parentID = idMap[mParent];
	int childSize = depts[parentID].childDept.size();
	int ret = 0;
	if (childSize == 3) {
		return -1;
	}
	idMap[mId] = deptNum;
	depts[deptNum] = Dept(deptNum, mNum, parentID);
	depts[parentID].childDept.push_back(deptNum++);
	totalTotalNum += mNum;
	ret = depts[parentID].totalNum + mNum;

	//��� �θ����� TotalNum ����
	while (parentID != -1) {
		depts[parentID].totalNum += mNum;
		parentID = depts[parentID].parentID;
	}
	//cout << ret << '\n';
	return ret;
}

int remove(int mId) {
	if (!idMap.count(mId)) {
		return -1;
	}
	int id = idMap[mId];
	int parentID = depts[id].parentID;
	if (depts[id].ID == -1) {
		return -1;
	}
	int totalNum = depts[id].totalNum;
	totalTotalNum -= totalNum;

	//�����ϴ� ����� �θ� ����� �ڽĺ��Ϳ��� �����ϴ� ��� ����
	for (int i = 0; i < (int)depts[parentID].childDept.size(); i++) {
		if (depts[parentID].childDept[i] == id) {
			depts[parentID].childDept.erase(depts[parentID].childDept.begin() + i);
		}
	}

	//�����ϴ� ����� ��� ���� ��带 BFS�� ����
	queue<int> q;
	q.push(id);
	while (!q.empty()) {
		int cur = q.front();
		q.pop();
		for (int i : depts[cur].childDept) {
			q.push(i);
		}
		depts[cur] = Dept();
	}

	//��� �θ����� TotalNum ����
	while (parentID != -1) {
		depts[parentID].totalNum -= totalNum;
		parentID = depts[parentID].parentID;
	}
	//cout << totalNum << '\n';
	return totalNum;
}

int distribute(int K) {
	int groupTotalNum[1000] = { 0 };
	int cumSum[1000] = { 0 };
	for (int i = 0; i < groupNum; i++) {
		groupTotalNum[i] = depts[i].totalNum;
	}
	//�μ��� �ο����� �������� ����
	sort(groupTotalNum, groupTotalNum + groupNum);
	cumSum[0] = groupTotalNum[0];
	for (int i = 1; i < groupNum; i++) {
		cumSum[i] = cumSum[i - 1] + groupTotalNum[i];
	}

	//�ο������� ��ǰ���� ���� ���
	if (totalTotalNum <= K) {
		return groupTotalNum[groupNum - 1];
	}

	//parametric search�� ���Ѽ� ���ϱ�
	int start = 0, end = K, val = 0;
	while (start <= end) {
		int mid = (start + end) / 2;
		int newStart = 0, newEnd = groupNum - 1, idx = 0;
		//�̺�Ž������ ���Ѽ� ���� �ο��� ���� �ε��� ���ϱ�
		while (newStart <= newEnd) {
			int newMid = (newStart + newEnd) / 2;
			if (groupTotalNum[newMid] < mid) {
				idx = newMid;
				newStart = newMid + 1;
			}
			else {
				newEnd = newMid - 1;
			}
		}

		int comp = cumSum[idx] + (groupNum - 1 - idx) * mid;
		if (comp <= K) {
			val = mid;
			start = mid + 1;
		}
		else {
			end = mid - 1;
		}
	}
	//cout << val << '\n';
	return val;
}