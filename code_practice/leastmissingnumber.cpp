#include <map>

#include "leastmissingnumber.h"

using namespace std;


LeastMissingNumber::LeastMissingNumber() {}

int LeastMissingNumber::Test(vector<int> & A)
{
    int missingNum = 1;
    map<int, bool> dataMap;

    for (auto element : A)
    {
        dataMap.insert( {element, true} );

        while (dataMap.find(missingNum) != dataMap.end())
        {
            missingNum++;
        }
    }

    return missingNum;
}
