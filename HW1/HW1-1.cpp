#include <iostream>
#include <string>
#include <vector>
using namespace std;
int dir[5] = {0, 1, 0, -1, 0};
char dir_name[4] = {'E', 'S', 'W', 'N'};
bool rec(vector<vector<int>> &table, int x, int y, string &ans)
{
    if (x < 0 || x >= table.size() || y < 0 || y >= table.size() || !table[x][y])
        return false;
    if (x == table.size() - 1 && y == table.size() - 1)
        return true;
    table[x][y] = 0;
    for (int i = 0; i < 4; i++)
    {
        ans.push_back(dir_name[i]);
        if (rec(table, x + dir[i], y + dir[i + 1], ans))
            return true;
        ans.pop_back();
    }
    return false;
}
int main(int argc, char **argv)
{
    int m;
    cin >> m;
    vector<vector<int>> table(m, vector<int>(m));
    for (vector<int> &v : table)
        for (int &i : v)
            cin >> i;
    string ans("");
    rec(table, 0, 0, ans);
    cout << ans;
    return 0;
}