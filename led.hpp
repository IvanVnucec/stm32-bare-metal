#pragma once

#include <cstdint>
#include "gpio.hpp"

template<typename gpio, const std::uint32_t pin>
struct led {
    led() {
        gpio::ddr::template write<0x01>();
        gpio::ggr::template write<0x00>(); 
    }
    void turn_on() { gpio::ggr::template write<0x01>(); }
    void turn_off() { gpio::ggr::template write<0x00>(); }
};
