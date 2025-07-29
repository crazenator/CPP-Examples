#ifndef __WIDGET_FACTORY_H__
#define __WIDGET_FACTORY_H__

#include <iostream>
#include <memory>

/* Create Interface */
class IWidget
{
public:
    /* Pure virtual function, mandate all sub-classes to provide implementation */
    virtual void draw() const = 0;
    virtual ~IWidget() = default;
};

/* Define Button Widget */
class Button : public IWidget
{
public:
    void draw() const override
    {
        std::cout << "Button Widget Implementation" << std::endl;
    }
};

/* Define Slider Widget */
class Slider : public IWidget
{
public:
    void draw() const override
    {
        std::cout << "Slider Widget Implementation" << std::endl;
    }
};

/* Helper to defer the static_assert */
template <typename>
inline constexpr bool always_false = false;

/* Define factory pattern orchestrator */
template <typename T>
std::unique_ptr<IWidget> createWidget()
{
    if constexpr (std::is_same_v<T, Button>)
        return std::make_unique<Button>();
    else if constexpr (std::is_same_v<T, Slider>)
        return std::make_unique<Slider>();
    else
    {
        static_assert(always_false<T>, "Unknown widget type!");
        return nullptr;
    }
}

#endif // __WIDGET_FACTORY_H__
