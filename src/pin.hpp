#pragma once

#include "gpio.hpp"

enum class output_type {
    push_pull,
    open_drain
};

enum class output_speed {
    mhz_10,
    mhz_2,
    mhz_50
};

template<typename gpio, int pin_n, output_type _type, output_speed _speed>
struct output {
    static_assert(pin_n < gpio::max_num_pins, "STM32 has only 16 GPIO pins indexed from 0 to 15.");

    static constexpr std::uint32_t get_cr() {
        std::uint32_t cr = 0b0000;

        if constexpr (_type == output_type::push_pull)
            cr |= 0b0000;
        else
            cr |= 0b0100;

        if constexpr (_speed == output_speed::mhz_10)
            cr |= 0b0001;
        else if constexpr (_speed == output_speed::mhz_2)
            cr |= 0b0010;
        else
            cr |= 0b0011;

        return cr;
    }

    static void init() {
        // general purpose output push pull
        constexpr std::uint32_t val = get_cr();

        if constexpr (pin_n < gpio::max_num_pins/2) {
            gpio::crl::template mask<val << (pin_n * 4)>();
        } else {
            gpio::crh::template mask<val << ((pin_n - gpio::max_num_pins/2) * 4)>();
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
        // input pin
        constexpr std::uint32_t val = 0b1000;

        if constexpr (pin_n < gpio::max_num_pins/2) {
            gpio::crl::template mask<val << (pin_n * 4)>();
        } else {
            gpio::crh::template mask<val << ((pin_n - gpio::max_num_pins/2) * 4)>();
        }

        // enable pull-down
        gpio::odr::template set_bit<pin_n>();
    }

    static bool get_state() {
        return gpio::idr::template read_bit<pin_n>();
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
