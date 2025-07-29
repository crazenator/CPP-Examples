#ifndef __SINGLETON_H__
#define __SINGLETON_H__

class Singleton
{
private:
    /* Default constructor is made private and removed Move/Copy constructor to avoid multiple instantiations */
    Singleton() = default;
    Singleton(const Singleton &) = delete;
    Singleton &operator=(const Singleton &) = delete;

public:
    /* Helper method to get singleton object */
    static Singleton &getInstance()
    {
        /* Lifetime of the process */
        static Singleton instance;
        return instance;
    }

    /* Utility Functions */
};

#endif // __SINGLETON_H__
