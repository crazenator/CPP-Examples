#include "oddoccurrence.h"

using namespace std;


OddOccurrence::OddOccurrence() {}

int OddOccurrence::Test(vector<int> &A)
{
    int unpairedNum = 0;

    if ( (A.size() % 2) == 0 )
    {
        return 0;
    }

    for (auto element : A)
    {
        unpairedNum ^= element;
    }

    return unpairedNum;
}
