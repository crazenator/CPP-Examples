#include <algorithm>
#include <iostream>

#include "triangle.h"

using namespace std;


Triangle::Triangle() {}

int Triangle::Test(vector<int> & A)
{
    unsigned int i;

    stable_sort(A.begin(), A.end());

    for (i = 0; i < (A.size() - 2); i++)
    {
        if (A.at(i) + A.at(i+1) > A.at(i+2))
        {
            return 1;
        }
    }

    return 0;
}
