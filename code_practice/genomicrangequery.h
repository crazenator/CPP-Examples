#ifndef GENOMICRANGEQUERY_H
#define GENOMICRANGEQUERY_H


#include <string>
#include <vector>


class GenomicRangeQuery
{
public:
    GenomicRangeQuery();
    std::vector<int> Test(std::string &, std::vector<int> &, std::vector<int> &);
};

#endif // GENOMICRANGEQUERY_H
