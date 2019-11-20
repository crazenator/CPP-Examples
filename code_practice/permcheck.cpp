#include <vector>

#include "permcheck.h"

using namespace std;


PermCheck::PermCheck() {}

int PermCheck::TestSolution1(vector<int> & A)
{
    // Assuming the permutation will start from 1
    int missingNum = 1;
    map<int, bool> dataMap;

    for (auto element : A)
    {
        if (dataMap.insert( {element, true} ).second == false)
        {
            return 0;
        }

        while (dataMap.find(missingNum) != dataMap.end())
        {
            missingNum++;
        }
    }

    return (missingNum <= (int)A.size()) ? 0 : 1;
}

int PermCheck::TestSolution2(vector<int> & A)
{
    // Generic solution; no assumption on the start of A
    int i = 0;
    sort(A.begin(), A.end());
    for (auto element : A)
    {
        if (element != (i + A.at(0)))
        {
            return 0;
        }
        i++;
    }
    return 1;
}
