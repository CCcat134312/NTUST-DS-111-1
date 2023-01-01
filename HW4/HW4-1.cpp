// #include <functional>
#include <iostream>
#include <vector>
using namespace std;
void dfs(vector<vector<bool>> &table,
         vector<vector<bool>> &visited,
         int &size, bool &flag, int from, int next)
{
    if (flag || visited[from][next])
    {
        flag = true;
        return;
    }
    visited[from][next] = true;
    for (int i = 0; i < size; i++)
    {
        if (!table[next][i])
            continue;
        dfs(table, visited, size, flag, next, i);
    }
}

void reset(vector<vector<bool>> &visited, int &size)
{
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            visited[i][j] = false;
}

int main(int argc, char **argv)
{
    int size;
    cin >> size;
    vector<vector<bool>> table(size, vector<bool>(size, false));
    for (int input1, input2; cin >> input1 >> input2;)
        table[input1][input2] = true;

    vector<vector<bool>> visited(size, vector<bool>(size, false));
    bool flag = false;

    // function<void(int, int)> dfs;
    // dfs = [&](int from, int next)
    // {
    //     if (flag || visited[from][next])
    //     {
    //         flag = true;
    //         return;
    //     }
    //     visited[from][next] = true;
    //     for (int i = 0; i < size; i++)
    //     {
    //         if (!table[next][i])
    //             continue;
    //         dfs(next, i);
    //     }
    // };

    // function<void()> reset;
    // reset = [&]()
    // {
    //     for (int i = 0; i < size; i++)
    //         for (int j = 0; j < size; j++)
    //             visited[i][j] = false;
    // };

    for (int i = 0; !flag && i < size; i++)
    {
        for (int j = 0; !flag && j < size; j++)
        {
            if (!table[i][j])
                continue;
            dfs(table, visited, size, flag, i, j);
            reset(visited, size);
        }
    }

    if (flag)
        cout << "Cycle";
    else
        cout << "No Cycle";
    return 0;
}