#include <iostream>
#include <vector>

#define NAME_MAXLEN 6
#define PATH_MAXLEN 1999

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

int nameToInt(string path) {
	//cout << "nameToIntStart" << '\n';
	int ret = 0;
	for (int i = 0; i < (int)path.length(); i++) {
		ret += (path[i] - 'a' + 1) << (5 * (5 - i));
	}
	//cout << "nameToIntEnd" << 'n';
	return ret;
}

class TreeNode {
public:
	int name = 0;
	TreeNode* parent = NULL;
	vector<TreeNode*> childs;
	int subNum = 0;

	TreeNode() {}
	TreeNode(int _name, TreeNode* _parent) {
		name = _name;
		parent = _parent;
	}

	void addChild(TreeNode* child) {
		if (childs.size() == 0) {
			childs.push_back(child);
			/*for (int i = 0; i < childs.size(); i++) {
				cout << childs[i]->name << ' ';
			}
			cout << '\n';*/
			return;
		}

		for (vector<TreeNode*>::iterator iter = childs.begin(); iter != childs.end(); iter++) {
			if (child->name < (*iter)->name) {
				childs.insert(iter, child);
				/*for (int i = 0; i < childs.size(); i++) {
					cout << childs[i]->name << ' ';
				}
				cout << '\n';*/
				return;
			}
		}
		childs.push_back(child);

		/*for (int i = 0; i < childs.size(); i++) {
			cout << childs[i]->name << ' ';
		}
		cout << '\n';*/
	}

	int removeBelow() {
		childs.clear();
	}
};

TreeNode root;
TreeNode nodePool[50000];
int nodeNum = 0;

TreeNode* findTreeNode(string path) {
	//cout << "findTreeNodeStart" << '\n';
	TreeNode* ret = &root;
	string newPath = path;
	size_t idx;
	int start, end, mid, target;
	if (path.compare("/") != 0) {
		newPath = newPath.substr(1);
		while ((idx = newPath.find('/')) != string::npos) {
			start = 0;
			end = ret->childs.size() - 1;
			target = nameToInt(newPath.substr(0, idx));
			//cout << "Target: " << target << '\n';
			while (start <= end) {
				mid = (start + end) / 2;
				if (target == ret->childs[mid]->name) {
					ret = ret->childs[mid];
					newPath = newPath.substr(idx + 1);
					break;
				}
				else if (target < ret->childs[mid]->name) {
					end = mid - 1;
				}
				else if (target > ret->childs[mid]->name) {
					start = mid + 1;
				}
			}
		}
	}
	//cout << "findTreeNodeEnd" << '\n';
	return ret;
}
TreeNode* addChild(TreeNode* src, int _name) {
	//cout << "addChildStart" << '\n';
	nodePool[nodeNum] = TreeNode(_name, src);
	TreeNode* newChild = &nodePool[nodeNum++], * parentPtr = src;
	src->addChild(newChild);
	while (parentPtr != NULL) {
		parentPtr->subNum++;
		parentPtr = parentPtr->parent;
	}
	//cout << "addChildEnd" << '\n';
	return newChild;
}

void preorder(TreeNode* src, TreeNode* dst) {
	//cout << "preorderStart" << '\n';
	TreeNode* child = addChild(dst, src->name);
	for (vector<TreeNode*>::iterator iter = src->childs.begin(); iter != src->childs.end(); iter++) {
		preorder(*iter, child);
	}
	//cout << "preorderEnd" << '\n';
}

void init(int n) {
	//cout << "initStart" << '\n';
	nodeNum = 0;
	nodePool[nodeNum] = TreeNode(27, NULL);
	root = nodePool[nodeNum++];
	//cout << "initEnd" << '\n';
}

void cmd_mkdir(char path[PATH_MAXLEN + 1], char name[NAME_MAXLEN + 1]) {
	//cout << "mkdirStart" << '\n';
	TreeNode* cur = findTreeNode(path);
	addChild(cur, nameToInt(name));
	//cout << "mkdirEnd" << '\n';
}

void cmd_rm(char path[PATH_MAXLEN + 1]) {
	//cout << "rmStart" << '\n';
	TreeNode* cur = findTreeNode(path), * parent = cur->parent;
	int start, end, mid, target;

	start = 0;
	end = parent->childs.size() - 1;
	target = cur->name;
	while (start <= end) {
		mid = (start + end) / 2;
		if (target == parent->childs[mid]->name) {
			break;
		}
		else if (target < parent->childs[mid]->name) {
			end = mid - 1;
		}
		else if (target > parent->childs[mid]->name) {
			start = mid + 1;
		}
	}
	parent->childs.erase(parent->childs.begin() + mid);

	while (parent != NULL) {
		parent->subNum -= (cur->subNum + 1);
		parent = parent->parent;
	}
	//cout << "rmEnd" << '\n';
}

void cmd_cp(char srcPath[PATH_MAXLEN + 1], char dstPath[PATH_MAXLEN + 1]) {
	//cout << "cpStart" << '\n';
	TreeNode* src = findTreeNode(srcPath), * dst = findTreeNode(dstPath);
	preorder(src, dst);
	//cout << "cpEnd" << '\n';
}

void cmd_mv(char srcPath[PATH_MAXLEN + 1], char dstPath[PATH_MAXLEN + 1]) {
	//cout << "mvStart" << '\n';
	TreeNode* src = findTreeNode(srcPath), * dst = findTreeNode(dstPath), * parentPtr = src->parent;
	int subNum = src->subNum + 1;
	int start, end, mid, target;

	start = 0;
	end = src->parent->childs.size() - 1;
	target = src->name;
	while (start <= end) {
		mid = (start + end) / 2;
		if (target == src->parent->childs[mid]->name) {
			break;
		}
		else if (target < src->parent->childs[mid]->name) {
			end = mid - 1;
		}
		else if (target > src->parent->childs[mid]->name) {
			start = mid + 1;
		}
	}
	src->parent->childs.erase(src->parent->childs.begin() + mid);

	src->parent = dst;
	dst->addChild(src);
	while (parentPtr != NULL) {
		parentPtr->subNum -= subNum;
		parentPtr = parentPtr->parent;
	}

	parentPtr = dst;
	while (parentPtr != NULL) {
		parentPtr->subNum += subNum;
		parentPtr = parentPtr->parent;
	}
	//cout << "mvEnd" << '\n';
}

int cmd_find(char path[PATH_MAXLEN + 1]) {
	//cout << "findStart" << '\n';
	TreeNode* cur = findTreeNode(path);
	//cout << "findEnd" << '\n';
	return cur->subNum;
}