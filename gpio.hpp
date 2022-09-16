#pragma once

#include "reg.hpp"
#include <cstdint>

template<const std::uint32_t addr>
struct gpio {
    static struct ccr : reg<addr, 0x00> { } ccr;
    static struct ddr : reg<addr, 0x04> { } ddr;
    static struct bbr : reg<addr, 0x0C> { } bbr;
    static struct ggr : reg<addr, 0x10> { } ggr;
};

using gpio_a = gpio<0x8000000>;
using gpio_b = gpio<0x8004000>;
using gpio_c = gpio<0x800C000>;
using gpio_d = gpio<0x8010000>;
