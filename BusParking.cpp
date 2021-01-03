// Interval tree
// Segment tree
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
// Test
class Interval
{
public:
    int start;
    int end;
    Interval(int start = 0, int end = 0)
    {
        this->start = start;
        this->end = end;
    }
};
class BusParking
{
public:
    class Node
    {
        int height;
        int max;
        Node *pLeft;
        Node *pRight;
        Interval interval;
        friend class BusParking;

    public:
        Node(Interval _interval) : interval(_interval), pLeft(NULL), pRight(NULL), height(1), max(_interval.end) {}
        ~Node() {}
    };
    void insert(int s, int t)
    {
        Interval new_interval(s, t);
        insert(this->root, new_interval);
    }
    BusParking()
    {
        minPark = 0;
        root = nullptr;
    }
    ~BusParking()
    {
        clear(this->root);
    }

private:
    int minPark;
    Node *root;
    void insert(Node *_root, Interval &value);
    void clear(Node *_root)
    {
        if (_root)
        {
            clear(_root->pLeft);
            clear(_root->pRight);
            delete _root;
        }
    }
    int BalanceFactor(Node *);
    int Height(Node *);
    int getMinBus(Interval temp);
};
int BusParking::Height(Node *_root)
{
    if (_root == nullptr)
        return 0;
    else
    {
        return _root->height;
    }
}
int BusParking::BalanceFactor(Node *_root)
{
    if (_root)
    {
        return Height(_root->pLeft) - Height(_root->pRight);
    }
    return 0;
}
void BusParking::insert(Node *_root, Interval &value)
{
    if (_root == nullptr)
    {
        Node *temp = new Node(value);
        _root = temp;
        return;
    }
    else
    {
        if (_root->max < value.end)
        {
            _root->max = value.end;
        }
        if (value.start < _root->interval.start)
        {
            insert(_root->pLeft, value);
        }
        else
        {
            insert(_root->pRight, value);
        }
    }
}
int minPark(vector<Interval> lInterval)
{
    int i = 0, j = 1;
    int bus_in = 1, max_bus = 1;
    int _size = lInterval.size();
    int *start = new int[_size];
    int *end = new int[_size];
    for (int i = 0; i < _size; i++)
    {
        start[i] = lInterval[i].start;
        end[i] = lInterval[i].end;
    }
    sort(start, start + _size);
    sort(end, end + _size);
    while (i < _size && j < _size)
    {
        if (start[j] > end[i])
        // The bus has returned
        {
            bus_in--;
            i++;
        }
        else
        {
            bus_in++;
            if (bus_in > max_bus)
            {
                max_bus = bus_in;
            }
            j++;
        }
    }
    delete[] start;
    delete[] end;
    return max_bus;
}
int main()
{
    vector<Interval> intervals;
    intervals.push_back(Interval(3, 6));
    intervals.push_back(Interval(1, 8));
    intervals.push_back(Interval(2, 5));
    intervals.push_back(Interval(5, 6));
    intervals.push_back(Interval(3, 7));
    intervals.push_back(Interval(2, 4));
    cout << minPark(intervals);
    return 0;
}