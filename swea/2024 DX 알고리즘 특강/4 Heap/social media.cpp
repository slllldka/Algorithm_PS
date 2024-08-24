#include <iostream>
#include <vector>
#include <queue>
#define min(a, b) (((a) < (b)) ? (a) : (b))
using namespace std;

class i4 {
public:
	int pID, uID, like, timestamp;	//uID, like, timestamp
	i4() :pID(0), uID(0), like(0), timestamp(0) {}
	i4(int _first, int _second, int _third, int _fourth)
		:pID(_first), uID(_second), like(_third), timestamp(_fourth) {}

	bool operator<(const i4& ref) {
		if (ref.like > like) {
			return true;
		}
		else if (ref.like == like) {
			if (ref.timestamp > timestamp) {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}
	bool operator>(const i4& ref) {
		if (like > ref.like) {
			return true;
		}
		else if (like == ref.like) {
			if (timestamp > ref.timestamp) {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}
};

class over1000 {
public:
	i4 data[10];
	int size;
	over1000() {
		size = 0;
	}
	void push(i4 item) {
		if (size == 0) {
			data[0] = item;
		}
		else {
			for (int i = 0; i < size; i++) {
				if (item > data[i]) {
					for (int j = min(size - 1, 8); j >= i; j--) {
						data[j + 1] = data[j];
					}
					data[i] = item;
					break;
				}

				if (size < 10 && i == (size - 1)) {
					data[size] = item;
				}
			}
		}

		if (size < 10) {
			size++;
		}
	}
	void pop() {
		for (int i = 1; i < size; i++) {
			data[i - 1] = data[i];
		}
		size--;
	}
	bool empty() {
		return size == 0;
	}
	i4 top() {
		return data[0];
	}
};

struct compare {
	bool operator()(i4& ref1, i4& ref2) {
		return ref1 < ref2;
	}
};

int N = 0;
int totalPosts = 0;
i4 posts[100001];
vector<int> graph[1001];
priority_queue<i4, vector<i4>, compare> userPosts[1001];
over1000 userPostsOver1000[1001];


void init(int n)
{
	//cout << "initStart\n";
	N = n;
	totalPosts = 0;
	for (int i = 1; i <= N; i++) {
		graph[i].clear();
		graph[i].push_back(i);
		userPosts[i] = priority_queue<i4, vector<i4>, compare>();
		userPostsOver1000[i] = over1000();
	}
	//cout << "initEnd\n";
}

void follow(int uID1, int uID2, int timestamp)
{
	//cout << "followStart\n";
	graph[uID1].push_back(uID2);
	//cout << uID1 << " follows " << uID2 << '\n';
	//cout << "followEnd\n";
}

void makePost(int uID, int pID, int timestamp)
{
	//cout << "makePostStart\n";
	totalPosts = pID;
	posts[pID] = i4(pID, uID, 0, timestamp);
	userPosts[uID].push(posts[pID]);
	//cout << uID << " makePost " << pID << '\n';
	//cout << "makePostEnd\n";
}

void like(int pID, int timestamp)
{
	//cout << "likeStart\n";
	if (timestamp - posts[pID].timestamp > 1000) {
		if (posts[pID].like >= 0) {
			posts[pID].like = -1000000000;
			userPostsOver1000[posts[pID].uID].push(posts[pID]);
		}
	}
	else {
		posts[pID].like++;
		userPosts[posts[pID].uID].push(posts[pID]);
	}
	//cout << "likeEnd\n";
}

void getFeed(int uID, int timestamp, int pIDList[])
{
	//cout << "getFeedStart\n";
	priority_queue<i4, vector<i4>, compare> top10;
	i4 data;
	int selecteduID, count = 0;
	bool selected = false;
	for (int i : graph[uID]) {
		selected = false;
		while (!userPosts[i].empty()) {
			data = userPosts[i].top();
			userPosts[i].pop();
			if (data.like == posts[data.pID].like) {
				if (timestamp - data.timestamp > 1000) {
					if (posts[data.pID].like >= 0) {
						posts[data.pID].like = -1000000000;
						userPostsOver1000[i].push(posts[data.pID]);
						continue;
					}
				}
				top10.push(data);
				selected = true;
				break;
			}
		}
		if (!selected) {
			while (!userPostsOver1000[i].empty()) {
				data = userPostsOver1000[i].top();
				userPostsOver1000[i].pop();
				if (data.like == posts[data.pID].like) {
					if (timestamp - data.timestamp > 1000) {
						if (posts[data.pID].like >= 0) {
							posts[data.pID].like = -1000000000;
							userPostsOver1000[i].push(posts[data.pID]);
							continue;
						}
					}
					top10.push(data);
					break;
				}
			}
		}
	}

	for (int i = 0; i < 10; i++) {
		selected = false;
		if (!top10.empty()) {
			data = top10.top();
			top10.pop();
			pIDList[i] = data.pID;
			count++;

			selecteduID = data.uID;
			while (!userPosts[selecteduID].empty()) {
				data = userPosts[selecteduID].top();
				userPosts[selecteduID].pop();
				if (data.like == posts[data.pID].like) {
					if (timestamp - data.timestamp > 1000) {
						if (posts[data.pID].like >= 0) {
							posts[data.pID].like = -1000000000;
							userPostsOver1000[selecteduID].push(posts[data.pID]);
							continue;
						}
					}
					top10.push(data);
					selected = true;
					break;
				}
			}
			if (!selected) {
				while (!userPostsOver1000[selecteduID].empty()) {
					data = userPostsOver1000[selecteduID].top();
					userPostsOver1000[selecteduID].pop();
					if (data.like == posts[data.pID].like) {
						if (timestamp - data.timestamp > 1000) {
							if (posts[data.pID].like >= 0) {
								posts[data.pID].like = -1000000000;
								userPostsOver1000[selecteduID].push(posts[data.pID]);
								continue;
							}
						}
						top10.push(data);
						break;
					}
				}
			}
		}
		else {
			break;
		}
	}

	for (int i = 0; i < count; i++) {
		//cout << pIDList[i] << ' ';
		if (posts[pIDList[i]].like >= 0) {
			userPosts[posts[pIDList[i]].uID].push(posts[pIDList[i]]);
		}
		else {
			userPostsOver1000[posts[pIDList[i]].uID].push(posts[pIDList[i]]);
		}
	}
	//cout << '\n';

	while (!top10.empty()) {
		data = top10.top();
		top10.pop();
		if (data.like >= 0) {
			userPosts[data.uID].push(data);
		}
		else {
			userPostsOver1000[data.uID].push(data);
		}
	}
	//cout << "getFeedEnd\n";
}