#include "mcu.hpp"
#include "bsp.hpp"

int main()
{
    mcu::init();
    bsp::init();

    while (true)
    {
        bsp::led_green::toggle();
        for (volatile int i = 0; i < 100000; i++);
    }

    return 0;
}
