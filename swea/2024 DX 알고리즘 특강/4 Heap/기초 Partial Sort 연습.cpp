//#include<iostream>
class IncomeID {
public:
	int income;
	int id;
	IncomeID(): income(0), id(0) {}
	IncomeID(int _income, int _id) : income(_income), id(_id) {}
	bool operator>(IncomeID& ref) {
		if (income > ref.income) {
			return true;
		}
		else if (income == ref.income) {
			if (id < ref.id) {
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

class maxHeap {
public:
	IncomeID data[100001];
	int size = 0;
	maxHeap() {
		for (int i = 0; i < 100001; i++) {
			data[i] = IncomeID();
		}
		size = 0;
	}

	void push(IncomeID item) {
		int idx;
		IncomeID temp;
		data[++size] = item;
		idx = size;
		while (idx > 1) {
			if (data[idx] > data[idx / 2]) {
				temp = data[idx];
				data[idx] = data[idx / 2];
				data[idx / 2] = temp;
				idx /= 2;
			}
			else {
				break;
			}
		}
	}
	IncomeID top() {
		return data[1];
	}
	void pop() {
		int idx = 1;
		IncomeID temp;
		data[1] = data[size--];
		while (idx <= (size / 2)) {
			if (data[idx] > data[idx * 2]) {
				if (idx * 2 + 1 <= size) {
					if (data[idx] > data[idx * 2 + 1]) {
						break;
					}
					else {
						temp = data[idx];
						data[idx] = data[idx * 2 + 1];
						data[idx * 2 + 1] = temp;
						idx *= 2;
						idx++;
					}
				}
				else {
					break;
				}
			}
			else {
				if (idx * 2 + 1 <= size) {
					if (data[idx * 2] > data[idx * 2 + 1]) {
						temp = data[idx];
						data[idx] = data[idx * 2];
						data[idx * 2] = temp;
						idx *= 2;
					}
					else {
						temp = data[idx];
						data[idx] = data[idx * 2 + 1];
						data[idx * 2 + 1] = temp;
						idx *= 2;
						idx++;
					}
				}
				else {
					temp = data[idx];
					data[idx] = data[idx * 2];
					data[idx * 2] = temp;
					idx *= 2;
				}
			}
		}
	}
	bool empty() {
		return size == 0;
	}
};

maxHeap pq;

void init() {
	pq = maxHeap();
}
void addUser(int uID, int income) {
	pq.push(IncomeID(income, uID));
}

int getTop10(int result[10]) {
	int count = 0;
	IncomeID arr[10] = {};
	while (!pq.empty() && count < 10) {
		//std::cout << pq.top().income << ' ' << pq.top().id << '\n';
		result[count] = pq.top().id;
		arr[count] = pq.top();
		pq.pop();
		count++;
	}

	for (int i = 0; i < count; i++) {
		pq.push(arr[i]);
	}

	return count;
}