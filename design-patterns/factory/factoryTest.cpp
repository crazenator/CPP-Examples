#include <iostream>

#include "widgetFactory.h"

void testWidgetFactory()
{
    std::cout << std::endl
              << "===== Factory Pattern Test ====="
              << std::endl;

    auto button = createWidget<Button>();
    auto slider = createWidget<Slider>();

    button->draw();
    slider->draw();
}

int main()
{
    testWidgetFactory();
}
