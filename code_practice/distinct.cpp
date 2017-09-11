#include <set>

#include "distinct.h"

using namespace std;


Distinct::Distinct() {}

#include <algorithm>
int Distinct::Test(vector<int> & A)
{
    set<int> dSet;

    for (auto element : A)
    {
        if (dSet.insert(element).second == false)
        {
            dSet.erase(element);
        }
    }

    return (dSet.empty()) ? -1 : *dSet.begin();
}
