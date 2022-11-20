#include <iostream>
#include <string>
using namespace std;
struct Node
{
	int val;
	int height = 1;
	Node *left = nullptr;
	Node *right = nullptr;
	Node(int _val) : val(_val) {}
};
class AVL
{
private:
	Node *root = nullptr;
	bool first = false;
	Node *insert(Node *curr, int &val);
	Node *deleteNode(Node *curr, int &val);
	void inorder(Node *curr);

	Node *leftRotate(Node *curr);
	Node *rightRotate(Node *curr);
	inline void updateHeight(Node *&node) { node->height = 1 + max(getHeight(node->left), getHeight(node->right)); }
	inline int getHeight(Node *node) { return !node ? 0 : node->height; }
	// BF = balance factor
	inline int getBF(Node *node) { return !node ? 0 : (getHeight(node->left) - getHeight(node->right)); }

	Node *rightMost(Node *curr);
	const char *delete_ops[3] = {"R-1", "R0", "R1"};
	inline void writeLog(const char *op) { rotateLog += (rotateCounts++ ? "," + string(op) : op); }

public:
	int rotateCounts = 0;
	string rotateLog = "";
	void insert(int &val) { root = insert(root, val); }
	void inorder() { inorder(root); }
	void deleteNode(int &val) { root = deleteNode(root, val); }
};
Node *AVL::leftRotate(Node *curr)
{
	Node *mid = curr->right;
	Node *mid_child = mid->left;

	mid->left = curr;
	curr->right = mid_child;

	updateHeight(curr);
	updateHeight(mid);

	return mid;
}
Node *AVL::rightRotate(Node *curr)
{
	Node *mid = curr->left;
	Node *mid_child = mid->right;

	mid->right = curr;
	curr->left = mid_child;

	updateHeight(curr);
	updateHeight(mid);

	return mid;
}
Node *AVL::insert(Node *curr, int &val)
{
	if (!curr)
		return new Node(val);

	if (val > curr->val)
		curr->right = insert(curr->right, val);
	else if (val < curr->val)
		curr->left = insert(curr->left, val);
	else
		return curr;

	updateHeight(curr);
	int BF = getBF(curr);
	if (BF > 1)
	{
		if (val > curr->left->val)
		{
			writeLog("LR");
			curr->left = leftRotate(curr->left);
		}
		else
			writeLog("LL");
		return rightRotate(curr);
	}
	else if (BF < -1)
	{
		if (val < curr->right->val)
		{
			writeLog("RL");
			curr->right = rightRotate(curr->right);
		}
		else
			writeLog("RR");
		return leftRotate(curr);
	}
	return curr;
}
Node *AVL::rightMost(Node *curr)
{
	while (curr->right)
		curr = curr->right;
	return curr;
}
Node *AVL::deleteNode(Node *curr, int &val)
{
	if (!curr)
		return nullptr;

	if (val > curr->val)
		curr->right = deleteNode(curr->right, val);
	else if (val < curr->val)
		curr->left = deleteNode(curr->left, val);
	else
	{
		if (!curr->left || !curr->right)
		{
			Node *temp = curr->left ? curr->left : curr->right;
			if (!temp) // no child
			{
				delete curr;
				return nullptr;
			}
			*curr = *temp;
			delete temp;
		}
		else
		{
			Node *temp = rightMost(curr->left);
			curr->val = temp->val;
			curr->left = deleteNode(curr->left, temp->val);
		}
	}
	updateHeight(curr);
	int BF = getBF(curr);
	if (BF > 1)
	{
		BF = getBF(curr->left);
		writeLog(delete_ops[BF + 1]);
		if (BF < 0) // LR
			curr->left = leftRotate(curr->left);
		return rightRotate(curr);
	}
	else if (BF < -1)
	{
		BF = getBF(curr->right);
		writeLog(delete_ops[BF + 1]);
		if (BF > 0) // RL
			curr->right = rightRotate(curr->right);
		return leftRotate(curr);
	}
	return curr;
}
void AVL::inorder(Node *curr)
{
	if (!curr)
		return;
	inorder(curr->left);
	if (first)
		cout << ' ';
	cout << curr->val;
	first = true;
	inorder(curr->right);
}
int main(int argv, char **argc)
{
	AVL tree;
	int input;
	char chr;
	do
	{
		cin >> input;
		tree.insert(input);
		chr = getchar();
	} while (chr != '\n');
	while (cin >> chr >> input)
	{
		switch (chr)
		{
		case 'D':
			tree.deleteNode(input);
			break;
		case 'I':
			tree.insert(input);
			break;
		}
	}
	tree.inorder();
	cout << '\n'
		 << tree.rotateCounts << '\n'
		 << tree.rotateLog;
	return 0;
}