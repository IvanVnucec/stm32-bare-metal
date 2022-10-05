#pragma once

#include "gpio.hpp"

template<typename out_pin>
struct led {
    static void init()     { out_pin::init(); }
    static void turn_on()  { out_pin::set_state(true); }
    static void turn_off() { out_pin::set_state(false); }
};
