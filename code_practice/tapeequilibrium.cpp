#include <cmath>

#include "tapeequilibrium.h"


using namespace std;

TapeEquilibrium::TapeEquilibrium() {}

int TapeEquilibrium::Test(std::vector<int> &A)
{
    int sum_m, sum_l, sum_r;

    if (A.size() < 2) { return 0; }

    sum_l = sum_r = 0;

    for (auto element : A) { sum_r += element; }
    sum_m = sum_r;

    for (auto element : A)
    {
        sum_l += element;
        sum_r -= element;
        if ( abs(sum_r - sum_l) < sum_m )
        {
            sum_m = abs(sum_r - sum_l);
        }
    }

    return sum_m;
}
