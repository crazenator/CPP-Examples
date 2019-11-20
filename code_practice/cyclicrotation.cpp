#include "cyclicrotation.h"


using namespace std;

CyclicRotation::CyclicRotation() {}

vector<int> CyclicRotation::Test(vector<int> &A, int K)
{
    int popIdx, pushIdx;
    vector<int> B;

    K %= A.size();

    pushIdx = 0;
    popIdx = K;

    for (auto element : A)
    {
        B.insert(B.begin() + pushIdx, A.at(popIdx));

        pushIdx++;
        popIdx = (popIdx + 1) % A.size();
    }

    return B;
}
