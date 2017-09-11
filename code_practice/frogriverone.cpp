#include <map>

#include "frogriverone.h"

using namespace std;


FrogRiverOne::FrogRiverOne() {}

int FrogRiverOne::Test(int x, vector<int> & A)
{
    int i = 0, missingNum = 1;
    map<int, bool> dataMap;

    for (auto element : A)
    {
        dataMap.insert( {element, true} );

        while (dataMap.find(missingNum) != dataMap.end())
        {
            if (missingNum == x) { return i; }
            missingNum++;
        }

        i++;
    }

    return -1;
}
