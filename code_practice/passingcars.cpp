#include <map>

#include "passingcars.h"

using namespace std;


PassingCars::PassingCars() {}

int PassingCars::Test(vector<int> & A)
{
    int incBy = 0, passingCars = 0;

    for (auto element : A)
    {
        if (element == 0)
        {
            incBy++;
        }
        else if (element == 1)
        {
            passingCars += incBy;
        }
    }

    return passingCars;
}
