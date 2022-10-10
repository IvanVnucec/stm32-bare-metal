#pragma once

#include <cstdint>
#include "reg.hpp"
#include "periph.hpp"
#include "rcc.hpp"

template<std::uint32_t base>
struct gpio : periph<base> {
    struct crl  : reg<base, 0x00, rw> {};
    struct crh  : reg<base, 0x04, rw> {};
    struct idr  : reg<base, 0x08, rw> {};
    struct odr  : reg<base, 0x0C, rw> {};
    struct bsrr : reg<base, 0x10, rw> {};
    struct brr  : reg<base, 0x14, rw> {};
    struct lckr : reg<base, 0x18, rw> {};
};

using gpio_c = gpio<0x40011000>;

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
};

template<typename output_pin>
struct inverted {
    static void init() { output_pin::init(); }

    template<bool state>
    static void set_state() { output_pin::template set_state<not state>(); }
};
