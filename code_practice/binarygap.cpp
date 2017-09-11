#include "binarygap.h"


#define m_NIBLE_SZ  4

BinaryGap::BinaryGap() {}

int BinaryGap::_stripLeadZeros(int & num)
{
    int idx;
    int loopCount = sizeof(int) << 4;

    if (num == 0) { return 0; }

    for (idx = 0; idx < loopCount; idx++)
    {
        if (num & (1 << idx)) { break; }
    }

    num >>= idx;
    return idx;
}

int BinaryGap::Test(int num)
{
    int binaryGap, binaryGap_max;

    if (num == 0) { return 0; }

    /* Initialize binary gap length and maximum gap length */
    binaryGap = binaryGap_max = 0;

    /* Mask leading zeroes */
    _stripLeadZeros(num);

    /* Skip 'one' on right side */
    num >>= 1;

    while (num)
    {
        /* Mask leading zeroes */
        binaryGap = _stripLeadZeros(num);
        if (binaryGap > binaryGap_max)
        {
            binaryGap_max = binaryGap;
        }

        /* Skip 'one' on right side */
        num >>= 1;
    }

    return binaryGap_max;
}
