#pragma once

#include "gpio.hpp"
#include "led.hpp"
#include "button.hpp"

namespace bsp {
    using led_green_pin = inverted<pin<output<gpio_c, 13, output_type::push_pull, output_speed::mhz_50>>>;
    using led_green = led<led_green_pin>;

    using button_pin = pin<input<gpio_a, 0>>;
    using pushbutton = button<button_pin>;

    void init() {
        led_green_pin::init();
        led_green::turn_on();

        button_pin::init();
    }
}
