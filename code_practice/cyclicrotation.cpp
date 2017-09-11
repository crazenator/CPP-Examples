#include "cyclicrotation.h"


using namespace std;

CyclicRotation::CyclicRotation() {}

vector<int> CyclicRotation::Test(vector<int> &A, int K)
{
    int popIdx, pushIdx;
    vector<int> B;

    K %= A.size();

    pushIdx = 0;
    popIdx = A.size() - K;

    for (auto element : A)
    {
        B.insert(B.begin() + pushIdx, element);

        pushIdx++;
        popIdx = (popIdx + 1) % A.size();
    }

    return B;
}
