#pragma once

#include "rcc.hpp"

namespace mcu {
    void init() {
        // init gpioc clock for led
        rcc::apb2enr::write(1 << 4);
    }
}
