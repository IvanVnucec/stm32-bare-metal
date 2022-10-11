#pragma once

#include "gpio.hpp"

template<typename gpio, int pin_n>
struct output_pin {
    static constexpr int max_num_pins = 16;
    static_assert(pin_n < max_num_pins, "STM32 has only 16 GPIO pins indexed from 0 to 15.");

    static void init() {
        // general purpose output push pull
        if constexpr (pin_n < max_num_pins/2) {
            gpio::crl::write(0b0011 << (pin_n * 4));
        } else {
            gpio::crh::write(0b0011 << ((pin_n - max_num_pins/2) * 4));
        }
    }

    template<bool state>
    static void set_state() {
        if constexpr (state == true)
            gpio::bsrr::write(1 << pin_n);
        else
            gpio::bsrr::write(1 << (max_num_pins + pin_n));
    }

    static void toggle_state() {
        gpio::odr::template toggle<1 << pin_n>(); 
    }
};

template<typename output_pin>
struct inverted {
    static void init() { output_pin::init(); }

    template<bool state>
    static void set_state() { output_pin::template set_state<not state>(); }

    static void toggle_state() { output_pin::toggle_state(); }
};
