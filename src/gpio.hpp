#pragma once

#include <cstdint>
#include "reg.hpp"
#include "periph.hpp"

template<std::uint32_t base>
struct gpio : periph<base> {
    static constexpr int max_num_pins = 16;

    struct crl  : reg<base, 0x00, rw> {};
    struct crh  : reg<base, 0x04, rw> {};
    struct idr  : reg<base, 0x08, rw> {};
    struct odr  : reg<base, 0x0C, rw> {};
    struct bsrr : reg<base, 0x10, rw> {};
    struct brr  : reg<base, 0x14, rw> {};
    struct lckr : reg<base, 0x18, rw> {};
};

using gpio_c = gpio<0x40011000>;
