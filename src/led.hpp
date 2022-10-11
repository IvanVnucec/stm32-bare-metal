#pragma once

#include "pin.hpp"

template<typename out_pin>
struct led {
    static void turn_on()  { out_pin::template set_state<true>(); }
    static void turn_off() { out_pin::template set_state<false>(); }
    static void toggle()   { out_pin::toggle_state(); }
};
