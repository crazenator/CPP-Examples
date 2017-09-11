#ifndef MAXCOUNTERS_H
#define MAXCOUNTERS_H


#include <vector>


class MaxCounters
{
    void increment(int &, int &);
    void maxcounter(std::vector<int> &, int &);
public:
    MaxCounters();
    std::vector<int> Test(int, std::vector<int> &);
};

#endif // MAXCOUNTERS_H
