#include <algorithm>
#include <iostream>
#include <limits>

#include "maxproduct3.h"

using namespace std;


MaxProduct3::MaxProduct3() {}

int MaxProduct3::Test(vector<int> & A)
{
    int maxProduct = numeric_limits<int>::min();

    stable_sort(A.begin(), A.end());

    if ( ( (abs(A.at(0)) * abs(A.at(1))) > (abs(A.at(A.size()-3)) * abs(A.at(A.size()-2))) ) &&
           (A.at(A.size()-1) > 0) )
    {
        maxProduct = A.at(0) * A.at(1) * A.at(A.size()-1);
    }
    else
    {
        maxProduct = A.at(A.size()-3) * A.at(A.size()-2) * A.at(A.size()-1);
    }

    return maxProduct;
}
