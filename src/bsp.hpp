#pragma once

#include "gpio.hpp"
#include "led.hpp"

namespace bsp {
    using led_green_pin = inverted<output_pin<gpio_c, 13>>;
    using led_green = led<led_green_pin>;

    void init() {
        led_green_pin::init();
        led_green_pin::set_state<false>();
    }
}
