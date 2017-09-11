#include <algorithm>
#include <iostream>

#include "triangle.h"

using namespace std;


Triangle::Triangle() {}

int Triangle::Test(vector<int> & A)
{
    unsigned int i;
    unsigned int p, q, r;

    vector<int> sA = A;
    stable_sort(sA.begin(), sA.end());

    for (i = 0; i < (sA.size() - 1); i++)
    {
        if (sA.at(i) + sA.at(i+1) > sA.at(i+3))
        {
            p = find(A.begin(), A.end(), A.at(i)) - A.begin();

            if (sA.at(i) == sA.at(i+1))
            {
                q = find(A.begin()+p, A.end(), A.at(i+1)) - A.begin();
            }
            else
            {
                q = find(A.begin(), A.end(), A.at(i+1)) - A.begin();
            }

            if (sA.at(i+1) == sA.at(i+2))
            {
                r = find(A.begin()+q, A.end(), A.at(i+2)) - A.begin();
            }
            else
            {
                r = find(A.begin(), A.end(), A.at(i+2)) - A.begin();
            }
        }
    }

    return 0;
}
