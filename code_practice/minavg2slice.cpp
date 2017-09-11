#include <limits>

#include "minavg2slice.h"

using namespace std;


MinAvg2Slice::MinAvg2Slice() {}

int MinAvg2Slice::Test(vector<int> & A)
{
    int avg_mi = 0;
    float avg_2 = 0, avg_3 = 0;
    float avg_m = numeric_limits<float>::max();

    for (unsigned int i = 0; i < (A.size() - 1); i++)
    {
        avg_2 = (A.at(i) + A.at(i+1))/2.0f;
        if (avg_2 < avg_m) { avg_mi = i; }

        if ( (i + 2) < A.size() )
        {
            avg_3 = (A.at(i) + A.at(i+1) + A.at(i+2))/3.0f;
            if (avg_3 < avg_m) { avg_mi = i; }
        }
    }

    return avg_mi;
}
