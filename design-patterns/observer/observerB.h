#ifndef __OBERVER_B_H__
#define __OBERVER_B_H__

#include <iostream>
#include <map>

#include "observer.h"

class ObserverB // Counter Utility
{
private:
    /* data */
    std::map<int, int> counter;

public:
    /* Allows to use class as callable method */
    void operator()(const int &value)
    {
        counter[value]++;

        std::cout << "[Priority Counter]: " << counter[value] << std::endl;
    }
};

#endif // __OBERVER_B_H__
