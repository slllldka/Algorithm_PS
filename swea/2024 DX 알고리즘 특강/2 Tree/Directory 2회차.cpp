#define NAME_MAXLEN 6
#define PATH_MAXLEN 1999

#include <vector>
#include <iostream>

using namespace std;

// The below commented functions are for your reference. If you want 
// to use it, uncomment these functions.
/*
int mstrcmp(const char *a, const char *b)
{
	int i;
	for (i = 0; a[i] != '\0'; i++)
	{
		if (a[i] != b[i])
			return a[i] - b[i];
	}
	return a[i] - b[i];
}

int mstrncmp(const char *a, const char *b, int len)
{
	for (int i = 0; i < len; i++)
	{
		if (a[i] != b[i])
			return a[i] - b[i];
	}
	return 0;
}

int mstrlen(const char *a)
{
	int len = 0;

	while (a[len] != '\0')
		len++;

	return len;
}

void mstrcpy(char *dest, const char *src)
{
	int i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = src[i];
}

void mstrncpy(char *dest, const char *src, int len)
{
	for (int i = 0; i<len; i++)
	{
		dest[i] = src[i];
	}
	dest[len] = '\0';
}
*/

constexpr int root = 0;

class TreeNode {
public:
	int name;
	int parent;
	vector<int> childs;
	int subNum;

	TreeNode() {
		name = 0;
		parent = -1;
		childs = vector<int>();
		subNum = 0;
	}

	void reset(int name, int parent) {
		this->name = name;
		this->parent = parent;
		childs.clear();
		subNum = 0;
	}

	void addChild(int idx);
	int findChild(int name);
	void removeChild(int idx);
};

TreeNode nodes[50000];

void TreeNode::addChild(int idx) {
	auto iter = childs.begin();
	for (; iter != childs.end(); iter++) {
		if (nodes[*iter].name > nodes[idx].name) {
			break;
		}
	}
	childs.insert(iter, idx);
	subNum += (1 + nodes[idx].subNum);

	int parent = this->parent;
	while (parent != -1) {
		nodes[parent].subNum += (1 + nodes[idx].subNum);
		parent = nodes[parent].parent;
	}
}
int TreeNode::findChild(int name) {
	int start = 0, end = childs.size() - 1;
	while (start <= end) {
		int mid = (start + end) / 2;
		if (nodes[childs[mid]].name == name) {
			return mid;
		}
		else if (nodes[childs[mid]].name < name) {
			start = mid + 1;
		}
		else {
			end = mid - 1;
		}
	}
	return -1;
}
void TreeNode::removeChild(int idx) {
	subNum -= (1 + nodes[idx].subNum);
	int parent = this->parent;
	while (parent != -1) {
		nodes[parent].subNum -= (1 + nodes[idx].subNum);
		parent = nodes[parent].parent;
	}
	childs.erase(childs.begin() + findChild(nodes[idx].name));
}

int nodeNum = 0;
char temp[7];

int stringHash(const char str[]) {
	int ret = 0;
	int idx = 0;
	while (str[idx]) {
		ret += (str[idx] - 'a' + 1) * (1 << ((5 - idx) * 5));
		idx++;
	}
	return ret;
}

int findIdx(const char path[]) {
	if (path[1] == 0) {
		return root;
	}
	int idx = 1;
	int parent = root;
	while (path[idx]) {
		int i = 0;
		for (; path[i + idx] != '/'; i++) {
			temp[i] = path[i + idx];
		}
		temp[i] = 0;

		int hash = stringHash(temp);
		parent = nodes[parent].childs[nodes[parent].findChild(hash)];
		idx += i;
		idx++;
	}
	return parent;
}

void dfs(int srcIdx, int dstIdx) {
	int childIdx = nodeNum++;
	nodes[childIdx].reset(nodes[srcIdx].name, dstIdx);
	nodes[dstIdx].addChild(childIdx);
	for (int idx : nodes[srcIdx].childs) {
		dfs(idx, childIdx);
	}
}

void init(int n) {
	nodeNum = 0;
	nodes[nodeNum++].reset(0, -1);
}

void cmd_mkdir(char path[PATH_MAXLEN + 1], char name[NAME_MAXLEN + 1]) {
	int idx = findIdx(path);
	//cout << idx << ' ' << nodeNum << '\n';
	nodes[nodeNum].reset(stringHash(name), idx);
	nodes[idx].addChild(nodeNum++);
}

void cmd_rm(char path[PATH_MAXLEN + 1]) {
	int idx = findIdx(path);
	nodes[nodes[idx].parent].removeChild(idx);
}

void cmd_cp(char srcPath[PATH_MAXLEN + 1], char dstPath[PATH_MAXLEN + 1]) {
	int srcIdx = findIdx(srcPath), dstIdx = findIdx(dstPath);
	dfs(srcIdx, dstIdx);
}

void cmd_mv(char srcPath[PATH_MAXLEN + 1], char dstPath[PATH_MAXLEN + 1]) {
	int srcIdx = findIdx(srcPath), dstIdx = findIdx(dstPath);
	//cout << srcIdx << ' ' << dstIdx << '\n';
	nodes[nodes[srcIdx].parent].removeChild(srcIdx);
	nodes[srcIdx].parent = dstIdx;
	nodes[dstIdx].addChild(srcIdx);
}

int cmd_find(char path[PATH_MAXLEN + 1]) {
	int idx = findIdx(path);
	return nodes[idx].subNum;
}