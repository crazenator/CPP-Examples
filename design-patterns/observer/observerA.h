#ifndef __OBERVER_A_H__
#define __OBERVER_A_H__

#include <iostream>

#include "observer.h"

class ObserverA // Moving Average Utility
{
private:
    /* data */
    double sum = 0;
    int count = 0;

public:
    /* Allows to use class as callable method */
    void operator()(const int &value)
    {
        sum += value;
        ++count;

        std::cout << "[Moving Average]: " << (sum / count) << std::endl;
    }
};

#endif // __OBERVER_A_H__
