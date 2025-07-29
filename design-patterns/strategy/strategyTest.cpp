#include <iostream>

#include "strategy.h"

void testStrategyPattern()
{
    std::cout << std::endl
              << "===== Strategy Pattern Test ====="
              << std::endl;

    auto add = [](int a, int b)
    {
        std::cout << a << " + " << b << " = " << (a + b) << std::endl;
        return (a + b);
    };
    auto subtract = [](int a, int b)
    {
        std::cout << a << " - " << b << " = " << (a - b) << std::endl;
        return (a - b);
    };
    auto multiply = [](int a, int b)
    {
        std::cout << a << " * " << b << " = " << (a * b) << std::endl;
        return (a * b);
    };

    Strategy s;

    s.setStrategy(add);
    s.execute(5, 2);

    s.setStrategy(subtract);
    s.execute(5, 2);

    s.setStrategy(multiply);
    s.execute(5, 2);
}

int main()
{
    testStrategyPattern();
}
