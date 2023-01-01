#include <iostream>
#include <vector>
using namespace std;
struct edge
{
    char from;
    char to;
    int weight;
};
class union_set
{
private:
    vector<int> data;

public:
    union_set()
    {
        data = vector<int>(128);
        for (int i = 0; i < data.size(); i++)
            data[i] = i;
    }

    int find(char x)
    {
        while (data[x] != x)
            x = data[x];
        return x;
    }

    inline void connect(char x, char y) { data[find(y)] = find(x); }
};
void sort(vector<edge> &edges)
{
    int size = edges.size();
    auto cmp = [](const edge &a, const edge &b) -> bool
    {
        if (a.weight != b.weight)
            return a.weight > b.weight;
        if (a.from != b.from)
            return a.from > b.from;
        return a.to > b.to;
    };
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            if (cmp(edges[j], edges[j + 1]))
            {
                edge temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;
            }
        }
    }
}
int main(int argc, char **argv)
{
    int node, conn;
    cin >> node >> conn;
    vector<edge> edges(conn);
    for (edge &e : edges)
    {
        cin >> e.from >> e.to >> e.weight;
        if (e.from > e.to)
        {
            char temp = e.to;
            e.to = e.from;
            e.from = temp;
        }
    }
    sort(edges);
    union_set uni;
    vector<edge> MST;
    int total_weight(0);
    for (edge &e : edges)
    {
        int x = uni.find(e.from),
            y = uni.find(e.to);
        if (x != y)
        {
            total_weight += e.weight;
            MST.push_back(e);
            uni.connect(e.from, e.to);
        }
    }

    cout << total_weight << '\n';
    for (edge &e : MST)
        cout << e.from << ' ' << e.to << ' ' << e.weight << (&e == &MST.back() ? "" : "\n");

    return 0;
}