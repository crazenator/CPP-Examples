#include <cmath>

#include "frogjump.h"


using namespace std;

FrogJump::FrogJump() {}

int FrogJump::Test(int x, int y, int d)
{
    if (d == 0) { return 0; }

    return (int)ceil( abs( x - y ) / (double)d );
}
