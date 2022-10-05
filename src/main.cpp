#include "led.hpp"

int main()
{
    led_green::init();

    while (1)
    {
        led_green::turn_on();
        for (volatile int i = 0; i < 100000; i++);
        led_green::turn_off();
        for (volatile int i = 0; i < 100000; i++);
    }

    return 0;
}
