#include <map>

#include "permcheck.h"

using namespace std;


PermCheck::PermCheck() {}

int PermCheck::Test(vector<int> & A)
{
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
