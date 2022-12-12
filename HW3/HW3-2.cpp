#include <iostream>
#include <vector>
using namespace std;
ostream &operator<<(ostream &os, vector<int> &arr)
{
	for (int &i : arr)
		cout << i << (&i == &arr.back() ? "" : " ");
	return os;
}
void bubble(vector<int> arr, int times)
{
	int size = arr.size(), cnt = 0;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size - i - 1; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				cnt++;
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
				if (cnt >= times)
				{
					cout << arr[j] << ", " << arr[j + 1] << "; " << arr << '\n';
					return;
				}
			}
		}
	}
}
void insert(vector<int> arr, int times)
{
	int size = arr.size();
	for (int i = 0; i < size && i < times; i++)
	{
		int temp = arr[i], j = i - 1;
		for (; j >= 0 && temp <= arr[j]; j--)
			arr[j + 1] = arr[j];
		arr[j + 1] = temp;
	}
	cout << arr << '\n';
}
void select(vector<int> arr, int times)
{
	int size = arr.size();
	for (int i = 0; i < size && i < times; i++)
	{
		int small = arr[i], index = i;
		for (int j = i + 1; j < size; j++)
		{
			if (small > arr[j])
			{
				small = arr[j];
				index = j;
			}
		}
		int temp = arr[i];
		arr[i] = small;
		arr[index] = temp;
	}
	cout << arr[times - 1] << "; " << arr << '\n';
}
int main(int argc, char **argv)
{
	// 21 24 28 15 20 19 30 41 20 28 13 12 33 25 7
	int times = 5;
	vector<int> arr;
	for (int input; cin >> input;)
		arr.push_back(input);

	cout << "Bubble: ";
	bubble(arr, times);
	cout << "Insertion: ";
	insert(arr, times);
	cout << "Selection: ";
	select(arr, times);
	insert(arr, arr.size());
	return 0;
}