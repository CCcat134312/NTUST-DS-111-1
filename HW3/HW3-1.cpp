#include <iostream>
#include <vector>
using namespace std;
struct Node
{
	int val;
	bool color = true; // true -> red, false -> black
	Node *left = nullptr;
	Node *right = nullptr;
	Node(int _val) : val(_val) {}
};
class RBT
{
private:
	Node *root = nullptr;
	int size = 0;

	Node *insert(Node *curr, int &val);
	Node *change_color(Node *curr, int &val);
	Node *check(Node *curr, int &val);

	Node *leftRotate(Node *curr);
	Node *rightRotate(Node *curr);

public:
	void split_team(vector<int> &red, vector<int> &black);
	void insert(int &val)
	{
		root = change_color(root, val);
		root = check(root, val);
		root = insert(root, val);
		root = check(root, val);
		root->color = false;
		size++;
	}
};
void RBT::split_team(vector<int> &red, vector<int> &black)
{
	if (!root)
		return;
	vector<Node *> queue(1, root);
	for (Node *now; queue.size(); queue.erase(queue.begin()))
	{
		now = *queue.begin();
		if (now->color)
			red.push_back(now->val);
		else
			black.push_back(now->val);

		if (now->left)
			queue.push_back(now->left);
		if (now->right)
			queue.push_back(now->right);
	}
}
Node *RBT::leftRotate(Node *curr)
{
	Node *mid = curr->right;
	Node *mid_child = mid->left;

	mid->left = curr;
	curr->right = mid_child;

	return mid;
}
Node *RBT::rightRotate(Node *curr)
{
	Node *mid = curr->left;
	Node *mid_child = mid->right;

	mid->right = curr;
	curr->left = mid_child;

	return mid;
}
Node *RBT::change_color(Node *curr, int &val)
{
	if (!curr)
		return curr;

	if (curr->left && curr->right && curr->left->color && curr->right->color)
	{
		curr->color = true;
		curr->left->color = curr->right->color = false;
		return curr;
	}
	if (val > curr->val)
		curr->right = change_color(curr->right, val);
	else if (val < curr->val)
		curr->left = change_color(curr->left, val);
	return curr;
}
Node *RBT::check(Node *curr, int &val)
{
	if (!curr)
		return curr;

	Node *child = val > curr->val ? curr->right : curr->left;
	if (!child)
		return curr;
	Node *grand = val > child->val ? child->right : child->left;
	if (!grand)
		return curr;

	if (!child->color || !grand->color)
	{
		if (val > curr->val)
			curr->right = check(curr->right, val);
		else if (val < curr->val)
			curr->left = check(curr->left, val);
	}
	else
	{
		if (curr->left == child) // L
		{
			if (child->right == grand) // LR
				curr->left = leftRotate(curr->left);
			curr = rightRotate(curr); // LL
		}
		else // R
		{
			if (child->left == grand) // RL
				curr->right = rightRotate(curr->right);
			curr = leftRotate(curr); // RR
		}
		curr->color = false;
		curr->left->color = curr->right->color = true;
	}
	return curr;
}
Node *RBT::insert(Node *curr, int &val)
{
	if (!curr)
		return new Node(val);

	if (val > curr->val)
		curr->right = insert(curr->right, val);
	else if (val < curr->val)
		curr->left = insert(curr->left, val);
	return curr;
}
ostream &operator<<(ostream &os, vector<int> &arr)
{
	for (int &i : arr)
		cout << i << (&i == &arr.back() ? "" : ",");
	return os;
}
void sort(vector<int> &arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		int temp = arr[i], j = i - 1;
		for (; j >= 0 && temp <= arr[j]; j--)
			arr[j + 1] = arr[j];
		arr[j + 1] = temp;
	}
}
void print_team(vector<int> &arr)
{
	int size = arr.size();
	vector<int> outfield(3);
	for (int i = 0, j = size - 3; i < 3; i++, j++)
		outfield[i] = arr[j];
	int jump = arr[0];

	sort(arr, size);
	sort(outfield, outfield.size());
	cout << arr << '\n';
	cout << "outfield: " << outfield << '\n';
	cout << "jump ball: " << jump;
}
int main(int argv, char **argc)
{
	RBT tree;
	for (int input; cin >> input;)
		tree.insert(input);

	vector<int> red, black;
	tree.split_team(red, black);
	if (red.size() >= 4 && black.size() >= 4)
	{
		cout << "Red team: ";
		print_team(red);
		cout << "\nBlack team: ";
		print_team(black);
	}
	else
		cout << "No game";
	return 0;
}