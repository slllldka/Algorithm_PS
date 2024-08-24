#include <vector>
#include <queue>
#include <iostream>

using namespace std;

struct i4 {
	bool down1000;
	int timestamp, like, pID;
	i4() {
		down1000 = false;
		timestamp = 0;
		like = 0;
		pID = 0;
	}
	i4(bool down1000, int timestamp, int like, int pID) {
		this->down1000 = down1000;
		this->timestamp = timestamp;
		this->like = like;
		this->pID = pID;
	}
};

struct comp {
	bool operator()(const i4& ref1, const i4& ref2) {
		if (!ref1.down1000 && !ref2.down1000) {
			return ref1.timestamp < ref2.timestamp;
		}
		else if (!ref1.down1000 && ref2.down1000) {
			return true;
		}
		else if (ref1.down1000 && !ref2.down1000) {
			return false;
		}
		else {
			if (ref1.like == ref2.like) {
				return ref1.timestamp < ref2.timestamp;
			}
			else {
				return ref1.like < ref2.like;
			}
		}
	}
};

struct tenPosts {
	comp compare;
	i4 arr[10];
	int size;
	tenPosts() {
		size = 0;
	}

	void push(i4 post) {
		int idx = -1;
		for (int i = 0; i < size; i++) {
			if (post.timestamp > arr[i].timestamp) {
				idx = i;
				break;
			}
		}

		if (idx == -1) {
			if (size == 10) {
				return;
			}
			else {
				arr[size++] = post;
				return;
			}
		}

		for (int i = (size < 10 ? (size - 1) : 8); i >= idx; i--) {
			arr[i + 1] = arr[i];
		}
		arr[idx] = post;
		if (size != 10) {
			size++;
		}
	}
	i4 top() {
		return arr[0];
	}
	void pop() {
		for (int i = 1; i < size; i++) {
			arr[i - 1] = arr[i];
		}
		size--;
	}
};

int N;
vector<int> followList[1001];
i4 posts[100001];
int postUID[100001];
priority_queue<i4, vector<i4>, comp> pq1000[1001];
tenPosts pq1001[1001];

void init(int n)
{
	N = n;
	for (int i = 1; i <= N; i++) {
		followList[i].clear();
		followList[i].push_back(i);
		pq1000[i] = priority_queue<i4, vector<i4>, comp>();
		pq1001[i] = tenPosts();
	}
	//cout << "initDone\n";
}

void follow(int uID1, int uID2, int timestamp)
{
	//cout << "followStart\n";
	followList[uID1].push_back(uID2);
	//cout << "followDone\n";
}

void makePost(int uID, int pID, int timestamp)
{
	//cout << "makePostStart " << pID << ' ' << uID << ' ' << timestamp << '\n';
	posts[pID] = i4(true, timestamp, 0, pID);
	postUID[pID] = uID;
	pq1000[uID].push(posts[pID]);
	//cout << "makePostDone\n";
}

void like(int pID, int timestamp)
{
	//cout << "likeStart " <<pID << '\n';
	if (posts[pID].down1000) {
		if (timestamp - posts[pID].timestamp > 1000) {
			posts[pID].down1000 = false;
			pq1001[postUID[pID]].push(posts[pID]);
		}
		else {
			posts[pID].like++;
			pq1000[postUID[pID]].push(posts[pID]);
		}
	}
	//cout << "likeDone\n";
}

void getFeed(int uID, int timestamp, int pIDList[])
{
	//cout << "getFeedStart " << timestamp << '\n';
	priority_queue<i4, vector<i4>, comp> finalPQ;
	vector<int> poppedPID;
	for (int fUID : followList[uID]) {
		while (true) {
			if (pq1000[fUID].empty()) {
				break;
			}
			if (timestamp - pq1000[fUID].top().timestamp > 1000) {
				if (posts[pq1000[fUID].top().pID].down1000) {
					posts[pq1000[fUID].top().pID].down1000 = false;
					pq1001[fUID].push(posts[pq1000[fUID].top().pID]);
				}
				pq1000[fUID].pop();
			}
			else if (posts[pq1000[fUID].top().pID].like
				!= pq1000[fUID].top().like) {
				pq1000[fUID].pop();
			}
			else {
				break;
			}
		}
		if (!pq1000[fUID].empty()) {
			poppedPID.push_back(pq1000[fUID].top().pID);
			finalPQ.push(pq1000[fUID].top());
			pq1000[fUID].pop();
		}
		else {
			if (pq1001[fUID].size > 0) {
				poppedPID.push_back(pq1001[fUID].top().pID);
				finalPQ.push(pq1001[fUID].top());
				pq1001[fUID].pop();
			}
		}
	}

	for (int i = 0; (i < 10 && !finalPQ.empty()); i++) {
		int pid = finalPQ.top().pID;
		int uid = postUID[pid];
		pIDList[i] = pid;
		finalPQ.pop();
		while (true) {
			if (pq1000[uid].empty()) {
				break;
			}
			if (timestamp - pq1000[uid].top().timestamp > 1000) {
				if (posts[pq1000[uid].top().pID].down1000) {
					posts[pq1000[uid].top().pID].down1000 = false;
					pq1001[uid].push(posts[pq1000[uid].top().pID]);
				}
				pq1000[uid].pop();
			}
			else if (posts[pq1000[uid].top().pID].like
				!= pq1000[uid].top().like) {
				pq1000[uid].pop();
			}
			else {
				break;
			}
		}
		if (!pq1000[uid].empty()) {
			poppedPID.push_back(pq1000[uid].top().pID);
			finalPQ.push(pq1000[uid].top());
			pq1000[uid].pop();
		}
		else {
			if (pq1001[uid].size > 0) {
				poppedPID.push_back(pq1001[uid].top().pID);
				finalPQ.push(pq1001[uid].top());
				pq1001[uid].pop();
			}
		}
	}

	for (int pid : poppedPID) {
		if (posts[pid].down1000) {
			pq1000[postUID[pid]].push(posts[pid]);
		}
		else {
			pq1001[postUID[pid]].push(posts[pid]);
		}
	}
	//cout << "getFeedDone\n";
}