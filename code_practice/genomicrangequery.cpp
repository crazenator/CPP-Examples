#include "genomicrangequery.h"

using namespace std;


GenomicRangeQuery::GenomicRangeQuery() {}

vector<int> GenomicRangeQuery::Test(string & s, vector<int> & p, vector<int> & q)
{
    vector<int> queryRsp;

    if ( (p.size() != q.size()) ) { return {}; }

    for (unsigned int i = 0; i < p.size(); i++)
    {
        int len = (q.at(i) - p.at(i));
        if (len == 0) { len++; }

        auto sub_s = s.substr(p.at(i), len);
        if (sub_s.find("A") != string::npos)
        {
            queryRsp.insert( queryRsp.begin() + i, 1 );
        }
        else if (sub_s.find("C") != string::npos)
        {
            queryRsp.insert( queryRsp.begin() + i, 2 );
        }
        else if (sub_s.find("G") != string::npos)
        {
            queryRsp.insert( queryRsp.begin() + i, 3 );
        }
        else if (sub_s.find("T") != string::npos)
        {
            queryRsp.insert( queryRsp.begin() + i, 4 );
        }
    }

    return queryRsp;
}
