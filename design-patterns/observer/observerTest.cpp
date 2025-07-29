#include <iostream>
#include <random>

#include "observer.h"
#include "observerA.h"
#include "observerB.h"

std::vector<int> getRandomValues(const int limit)
{
    std::random_device seedSource;
    std::mt19937 engine(seedSource());
    std::uniform_int_distribution<> uniformDistribution(1, 10);

    std::vector<int> randomValues(limit);
    for (auto &randomValue : randomValues)
    {
        randomValue = uniformDistribution(engine);
    }

    return randomValues;
}

void testObserverPatter()
{
    constexpr int EVENTS_LIMIT = 30;

    std::cout << std::endl
              << "===== Observer Pattern Test ====="
              << std::endl;

    /* Define type of event - return nothing, input int */
    Event<void, const int &> event;

    /* Define observers */
    ObserverA observerA;
    ObserverB observerB;

    /* Subscribe to events for notification */
    event.subscribe(observerA);
    event.subscribe(observerB);

    /* Trigger events and observe notification */
    for (auto value : getRandomValues(EVENTS_LIMIT))
    {
        event.notify(value);
    }
}

int main()
{
    testObserverPatter();
}
