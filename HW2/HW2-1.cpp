#include <iostream>
using namespace std;
struct Node
{
	int val;
	Node *left = nullptr;
	Node *right = nullptr;
	Node(int _val) : val(_val) {}
};
class BST
{
private:
	Node *root = nullptr;
	bool first = false;
	Node *insert(Node *curr, int &val);
	void preorder(Node *curr);
	void inorder(Node *curr);
	void postorder(Node *curr);

public:
	void insert(int &val) { root = insert(root, val); }
	void preorder()
	{
		preorder(root);
		first = false;
	}
	void inorder()
	{
		inorder(root);
		first = false;
	}
	void postorder()
	{
		postorder(root);
		first = false;
	}
};
Node *BST::insert(Node *curr, int &val)
{
	if (!curr)
		return new Node(val);
		
	if (val > curr->val)
		curr->right = insert(curr->right, val);
	else if (val < curr->val)
		curr->left= insert(curr->left, val);
	return curr;
}
void BST::preorder(Node *curr)
{
	if (!curr)
		return;
	if (first)
		cout << ' ';
	cout << curr->val;
	first = true;
	preorder(curr->left);
	preorder(curr->right);
}
void BST::inorder(Node *curr)
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
void BST::postorder(Node *curr)
{
	if (!curr)
		return;
	postorder(curr->left);
	postorder(curr->right);
	if (first)
		cout << ' ';
	cout << curr->val;
	first = true;
}
int main(int argv, char **argc)
{
	BST tree;
	for (int input; cin >> input;)
		tree.insert(input);
	tree.inorder();
	cout << '\n';
	tree.preorder();
	cout << '\n';
	tree.postorder();
	return 0;
}