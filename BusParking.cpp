#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class Interval
{
public:
    int start;
    int end;
    vector<Interval> intervals;
    Interval(int start = 0, int end = 0)
    {
        this->start = start;
        this->end = end;
    }
};
class BusParking
{
};
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