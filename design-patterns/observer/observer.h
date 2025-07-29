#ifndef __OBSERVER_H__
#define __OBSERVER_H__

#include <functional>
#include <vector>

template <typename Ret, typename... Args>
class Event
{
private:
    using Callback = std::function<Ret(Args...)>;
    std::vector<Callback> observers;

public:
    void subscribe(Callback callback)
    {
        observers.push_back(std::move(callback));
    }

    void notify(Args... args)
    {
        for (auto &observer : observers)
        {
            observer(args...);
        }
    }
};

#endif // __OBSERVER_H__
