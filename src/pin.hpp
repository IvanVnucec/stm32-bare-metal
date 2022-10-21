#pragma once

#include "gpio.hpp"

template<typename gpio, int pin_n>
struct output {
    static_assert(pin_n < gpio::max_num_pins, "STM32 has only 16 GPIO pins indexed from 0 to 15.");

    static void init() {
        // general purpose output push pull
        if constexpr (pin_n < gpio::max_num_pins/2) {
            gpio::crl::write(0b0011 << (pin_n * 4));
        } else {
            gpio::crh::write(0b0011 << ((pin_n - gpio::max_num_pins/2) * 4));
        }
    }

    template<bool state>
    static void set_state() {
        if constexpr (state == true)
            gpio::bsrr::write(1 << pin_n);
        else
            gpio::bsrr::write(1 << (gpio::max_num_pins + pin_n));
    }

    static bool get_state() {
        return gpio::idr::template read_bit<pin_n>();
    }

    static void toggle_state() {
        gpio::odr::template toggle_bit<pin_n>(); 
    }
};

template<typename gpio, int pin_n>
struct input {
    static_assert(pin_n < gpio::max_num_pins, "STM32 has only 16 GPIO pins indexed from 0 to 15.");

    static void init() {
        // TODO
        if constexpr (pin_n < gpio::max_num_pins/2) {
        } else {
        }
    }

    static bool get_state() {
        // TODO
        return false;
    }
};

template<typename mut>
struct pin {
    static void init() { mut::init(); }
    template<bool state>
    static void set_state() { mut::template set_state<state>(); }
    static bool get_state() { return mut::get_state(); }
    static void toggle_state() { mut::toggle_state(); }
};

template<typename pin>
struct inverted {
    static void init() { pin::init(); }
    template<bool state>
    static void set_state() { pin::template set_state<not state>(); }
    static bool get_state() { return not pin::get_state(); }
    static void toggle_state() { pin::toggle_state(); }
};
