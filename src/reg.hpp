#pragma once

#include <cstdint>
#include <type_traits>

struct ro {
    template<std::uint32_t addr>
    static std::uint32_t read() { return *reinterpret_cast<volatile std::uint32_t *>(addr); }
};

struct wo {
    template<std::uint32_t addr>
    static void write(const std::uint32_t val) { *reinterpret_cast<volatile std::uint32_t *>(addr) = val; }
};

struct rw : ro, wo {};

template<std::uint32_t base, std::uint32_t offset=0, typename mut=void>
struct reg {
    static_assert(not std::is_same<mut, void>::value, "Register mutability not defined.");
    static constexpr std::uint32_t addr = base + offset;

    static std::uint32_t read() { return mut::template read<addr>(); }

    static void write(const std::uint32_t val) { mut::template write<addr>(val); }

    template<std::uint32_t val>
    static void mask() { write(val | read()); }

    template<std::uint32_t val>
    static void clear() { write(~val & read()); }

    template<std::uint32_t val>
    static void toggle() { write(val ^ read()); } 

    template<int bit_n>
    static bool read_bit() {
        static_assert(bit_n < 32);
        return (read() & (1 << bit_n));
    }

    template<int bit_n>
    static void set_bit() {
        static_assert(bit_n < 32);
        mask<1 << bit_n>();
    }

    template<int bit_n>
    static void clear_bit() {
        static_assert(bit_n < 32);
        clear<1 << bit_n>();
    }

    template<int bit_n>
    static void toggle_bit() {
        static_assert(bit_n < 32);
        toggle<1 << bit_n>();
    }
};
