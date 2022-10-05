#pragma once

#include <cstdint>
#include "reg.hpp"
#include "periph.hpp"
#include "rcc.hpp"

template<std::uint32_t base>
struct gpio : periph<base> {
    using crl  = reg<gpio::base, 0x00>;
    using crh  = reg<base, 0x04>;
    using idr  = reg<base, 0x08>;
    using odr  = reg<base, 0x0C>;
    using bsrr = reg<base, 0x10>;
    using brr  = reg<base, 0x14>;
    using lckr = reg<base, 0x18>;
};

using gpio_c = gpio<0x40011000>;

template<typename gpio, int pin_n>
struct output_pin {
    static_assert(pin_n < 32);

    static void init() {
        // init gpioc clock
        rcc::apb2enr::write(1 << 4);
        // general purpose output push pull 
        gpio::crh::write(0b0011 << 20);
    }
    static void set_state(const bool state) {
        if (state == true)
            gpio::bsrr::write(1 << 13);
        else 
            gpio::bsrr::write(1 << 29);
    }
};
