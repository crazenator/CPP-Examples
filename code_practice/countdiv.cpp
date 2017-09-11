#include <cmath>

#include "countdiv.h"


using namespace std;

CountDiv::CountDiv() {}

int CountDiv::Test(int x, int y, int d)
{
    int count = 0;

    if (d == 0) { return 0; }

    if ( (y - x) > d ) { count = (y - x)/d; }
    count += x/d; count += y/d;

    return count;
}
