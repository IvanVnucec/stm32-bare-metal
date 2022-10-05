#pragma once

#include "gpio.hpp"
#include "led.hpp"

namespace bsp {
    using led_green = led<inverted<output_pin<gpio_c, 13>>>;

    void init() {
        led_green::init();
    }
};
