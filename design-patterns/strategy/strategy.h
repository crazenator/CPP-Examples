#ifndef __STRATEGY_H__
#define __STRATEGY_H__

#include <functional>

class Strategy
{
private:
    std::function<int(int, int)> feature;

public:
    Strategy() = default;

    void setStrategy(std::function<int(int, int)> feature)
    {
        this->feature = feature;
    }

    int execute(int a, int b)
    {
        return feature(a, b);
    }
};

#endif // __STRATEGY_H__
