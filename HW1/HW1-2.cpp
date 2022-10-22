#include <iostream>
#include <vector>
#include <string>
using namespace std;
struct person
{
    string name;
    int time;
    person() : name(""), time(0) {}
    person(string _name, int _time) : name(_name), time(_time) {}
    friend ostream &operator<<(ostream &os, const person &p)
    {
        os << p.name << ' ' << p.time;
        return os;
    }
};
class mqueue
{
public:
    vector<person> datas;
    int index = 0;

    int size() { return datas.size() - index; }
    void push(const person &p) { datas.push_back(p); }
    void pop() { index++; }
    person front() { return !size() ? person() : datas[index]; }
};
int minReach(vector<mqueue> &q)
{
    int ret(2e9);
    for (mqueue &mq : q)
        if (mq.size())
            ret = ret > mq.front().time ? mq.front().time : ret;
    return ret;
}
void process(vector<mqueue> &queues, int i, int reach)
{
    while (queues[i].size() && queues[i].front().time <= reach)
    {
        cout << queues[i].front() << ' ' << i << "\n";
        queues[i].pop();
    }
}
int main(int argc, char **argv)
{
    int n;
    cin >> n;
    vector<mqueue> queues(n);
    string name;
    int reach, duration;
    for (int next(0); cin >> name >> reach >> duration;)
    {
        for (int i = 0, size(2e9); i < queues.size(); i++)
        {
            for (int r = minReach(queues); r < reach; r = minReach(queues))
                for (int i = 0; i < queues.size(); i++)
                    process(queues, i, r);
            process(queues, i, reach);

            if (size > queues[i].size())
            {
                size = queues[i].size();
                next = i;
            }
        }
        reach = reach < queues[next].front().time ? queues[next].front().time : reach;
        queues[next].push(person(name, reach + duration));
    }
    for (reach = minReach(queues); reach != 2e9; reach = minReach(queues))
        for (int i = 0; i < queues.size(); i++)
            process(queues, i, reach);
    return 0;
}