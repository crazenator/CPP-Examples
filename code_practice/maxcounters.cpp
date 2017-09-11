#include "maxcounters.h"


using namespace std;


MaxCounters::MaxCounters() {}

void MaxCounters::increment(int & counter, int & counters_max)
{
    counter++;
    if (counter > counters_max)
    {
        counters_max = counter;
    }
}

void MaxCounters::maxcounter(vector<int> & counters, int & counters_max)
{
    for (unsigned int i = 0; i < counters.size(); i++)
    {
        counters.at(i) = counters_max;
    }
}

vector<int> MaxCounters::Test(int N, vector<int> & A)
{
    int counters_max = 0;
    vector<int> counters;

    if (N <= 0) { return {}; }

    for (int i = 0; i < N; i++)
    {
        counters.insert(counters.begin() + i, 0);
    }

    for (int i = 0; i < (int)A.size(); i++)
    {
        if (A.at(i) > N)
        {
            maxcounter(counters, counters_max);
        }
        else if ( (A.at(i) > 0) && (A.at(i) <= (int)counters.size()) )
        {
            increment(counters.at( A.at(i)-1 ), counters_max);
        }
    }

    return counters;
}
