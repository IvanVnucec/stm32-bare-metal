#pragma once

#include "rcc.hpp"

namespace mcu {
    void init() {
        // init gpioc clock for led
        rcc::apb2enr::set_bit<4>();

        // init gpioa clock for led
        rcc::apb2enr::set_bit<2>();
    }
}
